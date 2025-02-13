import subprocess
from generators import create_test_name
from processing import process_test, check


file_name = "t_cat.txt"
file_basic_name = "gentest"
log_file = "test_log.txt"

# -----------------------
# --------Запуск---------
# -----------------------

def check_test(test_number: int, tasks_count: int, valgrind_status: bool, 
                    precision: int, file_name: str, size : int, log_file, only_log : bool,
                    k : int = 0, print_tree : bool = False, 
                    reference_answers = [], reference_check : bool = False):
    processing = process_test(tasks_count, valgrind_status, precision, file_name, k)
    result = check(tasks_count, file_name, processing, k, print_tree, 
                    reference_answers, reference_check)

    
    if not(only_log):
        print_checked_result(test_number, tasks_count, size, valgrind_status, 
                             file_name, processing, result, k)
    return log_checked_result(test_number, tasks_count, size, valgrind_status, 
                              file_name, processing, result, k, log_file,
                              reference_answers, reference_check)
    
# ------------------------------------
# --------Печать с проверкой----------
# ------------------------------------

def print_checked_result(test_number, task_number, size, valgrind_status, 
                        file_name, processing, result, k : int):
    print("Test № " + str(test_number).ljust(5) + " ", end = "")
    print(file_name.ljust(26) + " ", end="")
    print("Len: " + str(size).ljust(6) + " ", end="")
    print("k: " + str(k).ljust(3) + " ", end="")

    status = 1
    
    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            print("Memory: Good! ", end="")
        else:
            print("Memory: Leaks or SF! ", end="")
            status = 0

    print("Student: " + result[0])
    if result[0] != "OK":
        status = 0
    if result[1] == []:
        print("Comment: Incorrect file!\n")
    
    return status
    
    
def log_checked_result(test_number, task_number, size, valgrind_status, 
                        file_name, processing, result, k : int, log_file,
                        reference_answers, reference_check):
    log_file.write("Test № " + str(test_number).ljust(5) + " ")
    log_file.write(file_name.ljust(26) + " ")
    log_file.write("Len: " + str(size).ljust(5) + " ")
    log_file.write("k: " + str(k).ljust(3) + " ")

    status = 1

    if valgrind_status:
        memory_status = processing[1]
        if memory_status == "Good!":
            log_file.write("Memory: Good! ")
        else:
            log_file.write("Memory: Leaks or SF! ")
            log_file.write(processing[0].stderr.decode("utf-8"))
            status = 0

    
    log_file.write("Student: " + result[0] + "\n")
    if (result[0] != "OK"):
        status = 0
        log_file.write("Your: " + str(processing[2]) + "\n")
        log_file.write("Auto: " + str(result[1]) + "\n")
        if reference_check:
            log_file.write("Ref: " + str(reference_answers) + "\n")
    if result[1] == []:
        log_file.write("Comment: Incorrect file!\n\n")
    
    return status

# -------------------------------------------------
# ------Массовая автоматическая проверка-----------
# -------------------------------------------------

def check_on_standard_tests(tasks_number, standard_set, valgrind_status, 
                  precision, log_file, only_log):
    if not(only_log):
        print("Standard set tests:")
    log_file.write("Standard set tests:\n")

    full_status = 0

    i = 0
    count = 0
    for unit in standard_set:
        for k in range(len(unit[2])):
            full_status += check_test(i, tasks_number, valgrind_status, precision, 
                 unit[0], unit[1], log_file, only_log, unit[2][k], False, unit[3][k], True)
            count += 1
        i += 1

    if not(only_log):
        print(f"Summary: {full_status} of {count} completed successfully!")
    log_file.write(f" Summary:{full_status} of {count} completed successfully!\n")

def check_on_generated_tests(tasks_number, min_length, max_length, step, k_attempts,
                             file_basic_name, 
                      valgrind_status, precision, log_file, only_log):
    index = 0
    full_status = 0

    print("Generated tests:")
    for i in range(min_length, max_length + 1, step):
        for k in k_attempts:
            #file_name = file_basic_name + str(task_number) + "_" + str(index) + ".txt"
            file_name = create_test_name(file_basic_name, index, k)
            full_status += check_test(index, tasks_number, valgrind_status, 
                    precision, file_name, i, log_file, only_log, k)
            index += 1
    
    if not(only_log):
        print(f"Summary: {full_status} of {index} completed successfully!")
    log_file.write(f"Summary: {full_status} of {index} completed successfully!\n")

def check_single_test(task_number, file_name, valgrind_status, precision, log_file, only_log, k = 1, print_tree = False):
    print("Single test:")
    check_test(0, task_number, valgrind_status, precision, file_name, -1, log_file, only_log, k, print_tree)
