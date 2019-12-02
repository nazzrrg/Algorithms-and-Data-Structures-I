import subprocess


def run_solution(path):
    subprocess.call(path.split())


def set_input(data, file):
    with open(file, 'w') as f:
        f.write(data)


def read_output(file):
    with open(file, 'r') as f:
        return f.read()

