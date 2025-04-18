#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "command.h"
#include "lists.h"
#include <libgen.h>
#include <string.h>
#include "config.h"
#include <memory>

#define BUFLEN 512

// Две вспомогательные функции для чтения/записи (см. ниже)

int readFromClient (int fd, char *buf);
int writeToClient (int fd, const char *buf);

int main (int argc, char ** argv) {
  int i, err, opt = 1;
  int sock, new_sock;
  int port = 5555;
  fd_set active_set, read_set;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  char buf[BUFLEN];
  socklen_t size;
  if (!((argc == 3) &&
    (sscanf(argv[2], "%d", &port) == 1)))
  {
    printf("Usage %s filename port\n", argv[0]);
    return -1;
  }
  char *filename = argv[1];

  FILE * fp = fopen(filename, "r");
  if (!fp) {
    printf("Can't open file %s\n", filename);
    return -2;
  }

  const char * config_name = "config.txt";
  std::unique_ptr<char []> exe_path = std::make_unique<char []> (strlen (argv[0]) + 1);
  strcpy (exe_path.get (), argv[0]); // make a copy, "dirname" modifies argument
  char *dir = dirname (exe_path.get ()); // get directory with executable
  printf ("Executable dir = %s\n", dir);
  size_t path_len = strlen (dir) + 1 + strlen (config_name) + 1;
  std::unique_ptr<char []> config_path = std::make_unique<char []> (path_len);
  snprintf (config_path.get (), path_len, "%s/%s", dir, config_name);
  printf ("Config path = %s\n", config_path.get ());

  FILE *fc = fopen(config_path.get(), "r");
  if (!fc) {
    printf("Can't open config file\n");
    return -3;
  }
  config con;
  if (con.parse(fc) == false) {
    printf("Couldn't read config file\n");
    return -4;
  }
  fclose (fc);

  list birch;
  birch.read_list(fp, con);
  fclose (fp);

  // Создаем TCP сокет для приема запросов на соединение
  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror ("Server: cannot create socket");
    exit (EXIT_FAILURE);
  }

  setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, (char *) &opt, sizeof (opt));
  // Заполняем адресную структуру и
  // связываем сокет с любым адресом
  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  addr.sin_addr.s_addr = htonl (INADDR_ANY);
  err = bind (sock, (struct sockaddr *) &addr, sizeof (addr));
  if (err < 0) {
    perror ("Server: cannot bind socket");
    exit (EXIT_FAILURE);
  }
  // Создаем очередь на 30 входящих запроса соединения
  err = listen (sock, 30);
  if (err < 0) {
    perror ("Server: listen queue failure");
    exit (EXIT_FAILURE);
  }
  // Подготавливаем множества дескрипторов каналов ввода-вывода.
  // Для простоты не вычисляем максимальное значение дескриптора,
  // а далее будем проверять все дескрипторы вплоть до максимально
  // возможного значения FD_SETSIZE.
  FD_ZERO (&active_set);
  FD_SET (sock, &active_set);
  // Основной бесконечный цикл проверки состояния сокетов
  while (1) {
    // Проверим, не появились ли данные в каком-либо сокете.
    // В нашем варианте ждем до фактического появления данных.
    read_set = active_set;
    if (select (FD_SETSIZE, &read_set, NULL, NULL, NULL) < 0) {
      perror ("Server: select failure");
      exit (EXIT_FAILURE);
    }
    // Данные появились. Проверим в каком сокете.
    for (i = 0; i < FD_SETSIZE; i++) {
      if (FD_ISSET (i, &read_set)) {
        if (i == sock) {
          // пришел запрос на новое соединение
          size = sizeof (client);
          new_sock = accept (sock, (struct sockaddr *) &client, &size);
          if (new_sock < 0) {
            perror ("accept");
            exit (EXIT_FAILURE);
          }
          fprintf (stdout, "Server: connect from host %s, port %d.\n", inet_ntoa (client.sin_addr), (unsigned int) ntohs (client.sin_port));
          FD_SET (new_sock, &active_set);
        }
        else {
          // пришли данные в уже существующем соединени
          err = readFromClient (i, buf);
          if (err < 0) {
          // ошибка или конец данных
            close (i);
            FD_CLR (i, &active_set);
          }
          else {
            // данные прочитаны нормально
            command cmd;
            ordering order[3] = {ordering::none};
            command_type check = cmd.check_type(buf);
            int res, flag = 0;
            switch(check) {
              case command_type::select:
                if (cmd.parse(buf, order) == false) {writeToClient(i, "incorrect format\n"); flag = 1; break;}
                res += birch.check(cmd, order, con, i);
                flag = 1;
                break;
              case command_type::quit:
                flag = 1;
                break;
              case command_type::insert:
                birch.parse_insert(buf, con);
                break;
              case command_type::del:
                birch.delete_parse(buf, con);
                break;
              case command_type::incorrect:
                writeToClient(i, "incorrect command\n");
                flag = 1;
                break;
              case command_type::stop:
                close(sock);
                return 0;
            }
            if (flag != 1) writeToClient (i, "EMPTY");
          }
        }
      }
    }
  }
}

int readFromClient (int fd, char *buf) {
  int nbytes, len, i;
  // Получаем длину сообщения
  if (read (fd, &len, sizeof (int)) != (int) sizeof (int)) {
    // ошибка чтения
    perror ("read length");
    return -1;
  }
  // Здесь неплохо бы проверить размер буфера
  // Получаем len байт
  for (i = 0; len > 0; i += nbytes, len -= nbytes) {
    nbytes = read (fd, buf + i, len);
    if (nbytes < 0) {
      perror ("read");
      return -1;
    }
    else if (nbytes == 0) {
      perror ("read truncated");
      return -1;
    }
  }
  // Длина находится в i
  if (i == 0) {
    // нет данных
    fprintf (stderr, "Server: no message\n");
    return -1;
  }
  else {
    // есть данные
    fprintf (stdout, "Server got %d bytes of message: %s\n", i, buf);
    return 0;
  }
}

int writeToClient (int fd, const char *buf) {
  int nbytes, len, i;
  len = strlen(buf);
  // Длина сообщения
  len++;
  // Пересылаем длину сообщения
  if (write (fd, &len, sizeof (int)) != (int) sizeof (int)) {
    perror ("write length");
    return -1;
  }
  // Пересылаем len байт
  for (i = 0; len > 0; i += nbytes, len -= nbytes) {
    nbytes = send (fd, buf + i, len, MSG_NOSIGNAL);
    if (nbytes < 0) {
      perror ("write");
      return -1;
    }
    else if (nbytes == 0) {
      perror ("write truncated");
      return -1;
    }
  }
  // Длина находится в i
  fprintf (stdout, "Write back: %s\nnbytes=%d\n", buf, i);
  return 0;
}
