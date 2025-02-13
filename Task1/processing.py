import subprocess
from tree import Tree

def create_command(valgrind_status: bool, prec: int, file_name: str, k: int = 1) -> list:
    command = []
    
    if valgrind_status:
        command += ["valgrind"]
    
    command += [f"./a.out"]
    command += [str(prec), str(k), file_name]

    return command

def process_test(task_count: int, valgrind_status: bool, 
                    precision: int, file_name: str, k: int = 0):
    command = create_command(valgrind_status, precision, file_name, k)
    output = subprocess.run(command, capture_output=True)

    err = output.stderr.decode("utf-8")
    if err == "":
        memory_status = ""
    elif ("no leaks are possible" in err):
        memory_status = "Good!"
    else:
        memory_status = "Bad!"

    out = output.stdout.decode("utf-8")
    out_data = out.split()
    if not("Result" in out_data):
        return [output, memory_status, [], []]
    
    pos = -1
    st_answers = []
    for i in range(task_count):
        pos = out_data.index("Result", pos + 1)
        st_answers += [int(out_data[pos + 2])]

    return [output, memory_status, st_answers]
    
def check(task_count, file_name, processing, k : int = 0, print_tree = False,
          reference_answers = [], reference_check = False):
    result = "OK"

    tr = Tree()
    tr.read_from_file(file_name)

    if print_tree:
        tr.print_tree()

    st_correct_answer = tr.summary(k)

    if st_correct_answer == processing[2] and \
        (not(reference_check) or st_correct_answer == reference_answers):
        result = "OK"
    else:
        result = "Wrong Ans"

    return [result, st_correct_answer]
    
