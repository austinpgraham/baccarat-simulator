import os
import sys
from collections import defaultdict
from pathlib import Path
import matplotlib.pyplot as plt


if len(sys.argv) < 2:
    raise ValueError("Must provider folder path to process.")


full_path = os.path.abspath(sys.argv[1])
if not os.path.exists(full_path):
    raise ValueError(f"Path {full_path} does not exist.")
if not os.path.isdir(full_path):
    raise ValueError(f"Path {full_path} is not a directory.")


def get_processable_paths():
    files = os.listdir(full_path)
    return [os.path.join(full_path, file) for file in files if file.endswith(".txt")]


def parse_file_contents(file_paths):
    result = defaultdict(list)
    for file in file_paths:
        file_name = Path(file).stem
        with open(file, "r") as _file:
            pot_lines = [
                line
                for line in _file.readlines()
                if line.startswith("POT")
            ]
            result[file_name] = [
                line.split()[-1]
                for line in pot_lines
            ]
    return result


def graph_results():
    file_paths = get_processable_paths()
    result_dict = parse_file_contents(file_paths)
    for name, y_values in result_dict.items():
        x_values = [i + 1 for i in range(len(y_values))]
        y_values = [int(j) for j in y_values]
        plt.plot(x_values, y_values, label=name)
    plt.legend()
    plt.xlabel("Hand Increment")
    plt.ylabel("Player Pot")
    plt.title("Betting Strategy Comparisons")
    plt.show()


if __name__ == '__main__':
    graph_results()
