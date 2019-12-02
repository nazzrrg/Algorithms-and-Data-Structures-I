from random import randint

import runner

cmds = ['insert', 'delete', 'exists', 'prev', 'next']
max_value = 2  # максимальное значение ключа по модулю
max_n = 25  # максимальное кол-во команд в тесте

SOLUTION_1 = './lab1'  # путь к предварительно скомпилированному бинарнику
SOLUTION_2 = ''  # путь к предварительно скомпилированному бинарнику
INPUT_FILE = 'bstsimple.in'
OUTPUT_FILE = 'bstsimple.out'


def gen_test():
    test = []

    n = randint(5, max_n)

    for i in range(n):
        test.append((cmds[randint(0, len(cmds) - 1)], randint(-max_value, max_value)))

    return test


# корректное решение
def solution(test):
    arr = []
    answer = []
    for cmd in test:
        if cmd[0] == 'insert':
            if not cmd[1] in arr:
                arr.append(cmd[1])
        elif cmd[0] == 'delete':
            if cmd[1] in arr:
                arr.remove(cmd[1])
        elif cmd[0] == 'exists':
            answer.append("true" if cmd[1] in arr else "false")
        elif cmd[0] == 'prev':
            kek = [el for el in arr if el < cmd[1]]
            answer.append(max(kek) if kek else "none")
        elif cmd[0] == 'next':
            kek = [el for el in arr if el > cmd[1]]
            answer.append(min(kek) if kek else "none")
    return answer


def compare_ans(ans1, ans2):
    if len(ans1) != len(ans2):
        return True, "Dif len\n" + str(zip(ans1, ans2))
    verdict = []
    error = False
    for i in range(len(ans1)):
        res = ""
        if str(ans1[i]) != str(ans2[i]):
            res = ">> "
            error = True
        res += "{} {}".format(ans1[i], ans2[i])
        verdict.append(res)
    return error, verdict


while True:
    test = gen_test()
    runner.set_input("\n".join(map(lambda x: str.join(" ", map(str, x)), test)), INPUT_FILE)
    print("Running solution1...")
    answer1 = solution(test)
    # можно раскоментировать и запустить второе решение из бинарника
    # runner.run_solution(SOLUTION_2)
    # answer1 = runner.read_output(OUTPUT_FILE).split()
    print("Running solution2...")
    runner.run_solution(SOLUTION_1)
    answer2 = runner.read_output(OUTPUT_FILE).split()

    verdict = compare_ans(answer1, answer2)
    if verdict[0]:
        print("\n".join(verdict[1]))
        break

# Vadim Gavrilov
