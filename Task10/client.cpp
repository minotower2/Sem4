#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctime>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <netdb.h>
// Определимся с портом, адресом сервера и другими константами.
// В данном случае берем произвольный порт и адрес обратной связи
// (тестируем на одной машине).
#define BUFLEN 512
// Две вспомогательные функции для чтения/записи (см. ниже)
void writeToServer (int fd, int *working);
int readFromServer (int fd);

int main (int argc, char ** argv) {
  int err;
  int sock;
  struct sockaddr_in server_addr;
  struct hostent *hostinfo;
  int port = 5555;
  char *name = nullptr;

  if (!((argc == 3) &&
    (sscanf(argv[2], "%d", &port) == 1)))
  {
    printf("Usage %s ip port\n", argv[0]);
    return -1;
  }
  name = argv[1];
  // Получаем информацию о сервере по его DNS имени
  // или точечной нотации IP адреса.
  hostinfo = gethostbyname (name);
  if (hostinfo == NULL) {
    fprintf (stderr, "Unknown host %s.\n", name);
    exit (EXIT_FAILURE);
  }
  // Заполняем адресную структуру для последующего
  // использования при установлении соединения
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons (port);
  server_addr.sin_addr = *(struct in_addr *) hostinfo->h_addr;
  // Создаем TCP сокет.
  sock = socket (PF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    perror ("Client: socket was not created");
    exit (EXIT_FAILURE);
  }
  // Устанавливаем соединение с сервером
  err = connect (sock, (struct sockaddr *) &server_addr, sizeof (server_addr));
  if (err < 0) {
    perror ("Client: connect failure");
    exit (EXIT_FAILURE);
  }
  fprintf (stdout, "Connection is ready\n");
  // Обмениваемся данными
  int working = 1;
  int count = 0;
  double t = clock();
  while (working == 1) {
    writeToServer (sock, &working);
    if (working == 1) readFromServer (sock);
    else if (working == 2) {
      while (readFromServer(sock) == 1) count++;
    }
    if (working == 2) working = 1;
  }
  t = (clock() - t)/CLOCKS_PER_SEC;
  // Закрываем socket
  printf ("%s : Result = %d Elapsed = %.2f\n", argv[0], count, t);
  close (sock);
  exit(EXIT_SUCCESS);
}

void writeToServer (int fd, int *working) {
  int nbytes, len, i;
  char buf[BUFLEN];
  fgets (buf, BUFLEN, stdin);
  // Удаляем завершающий символ ’\n’ (если есть)
  for (len = 0; buf[len]; len++)  {
    if (buf[len] == '\n') {
      buf[len] = 0;
      break;
    }
  }

  // Длина сообщения
  len++;
  // Пересылаем длину сообщения
  if (write (fd, &len, sizeof (int)) != (int) sizeof (int)) {
    perror ("write length");
    exit (EXIT_FAILURE);
  }
  // Пересылаем len байт
  for (i = 0; len > 0; i += nbytes, len -= nbytes) {
    nbytes = write (fd, buf + i, len);
    if (nbytes < 0) {
      perror ("write");
      exit (EXIT_FAILURE);
    }
    else if (nbytes == 0) {
      perror ("write truncated");
      exit (EXIT_FAILURE);
    }
  }
  char *s = strtok(buf, " \t\n();");
  if (strcmp(s, "quit") == 0) *working = 0;
  if (strcmp(s, "stop") == 0) *working = 0;
  if (strcmp(s, "select") == 0) *working = 2;
}

int readFromServer (int fd) {
  int nbytes, len, i;
  char buf[BUFLEN];
  // Получаем длину сообщения
  if (read (fd, &len, sizeof (int)) != (int) sizeof (int)) {
    // ошибка чтения
    perror ("read length");
    exit (EXIT_FAILURE);
  }
  // Получаем len байт
  for (i = 0; len > 0; i += nbytes, len -= nbytes) {
    nbytes = read (fd, buf + i, len);
    if (nbytes < 0) {
      perror ("read");
      exit (EXIT_FAILURE);
    }
    else if (nbytes == 0) {
      perror ("read truncated");
      exit (EXIT_FAILURE);
    }
  }
  // Длина находится в i
  if (i == 0) {
    // нет данных
    fprintf (stderr, "Client: no message\n");
  }
  else {
    // ответ успешно прочитан
    if (strcmp(buf, "EMPTY") != 0) {
      if (strcmp(buf, "SUCCESS") != 0) fprintf (stdout, "%s\n", buf);
      else fprintf (stdout, "\n");
    }
  }
  if (strcmp(buf, "SUCCESS") == 0) return 0;
  return 1;
}
