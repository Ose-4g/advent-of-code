import re
import math

def inst(lines):
    i = 0
    while True:
        yield lines[i]

        if i+1 == len(lines):
            i = 0
        else:
            i += 1


def part_1(text=""):
    lines = text.split("\n")
    instructions = inst(lines[0])

    steps = lines[2:]

    nodes = {}
    for step in steps:
        node = step.split(" ")[0]
        left = step.split("(")[1].split(",")[0]
        right = step.split(", ")[1][:-1]

        nodes[node] = (left, right)

    count = 0
    curr = nodes["AAA"]
    while True:
        count += 1

        instruction = next(instructions)
        next_key = curr[0] if instruction == "L" else curr[1]

        if next_key == "ZZZ":
            break

        curr = nodes[next_key]

    return count


def get_steps(nodes, start, line):
    instructions = inst(line)

    count = 0
    curr = start
    # print("from ", curr, end = "")
    while True:
        count += 1

        instruction = next(instructions)
        next_key = curr[0] if instruction == "L" else curr[1]

        if next_key[2] == "Z":
            print(next_key)
            break
        else:
            print(next_key)

        curr = nodes[next_key]
    # print("to ",curr, "in ", count, "steps\n\n")

    return count

# @lib.timer
# #@lib.aoc_sample
# @lib.aoc_input
def part_2(text=""):
    # log.debug("Running part_2")

    lines = text.split("\n")

    steps = lines[2:]

    nodes = {}
    for step in steps:
        node = step.split(" ")[0]
        left = step.split("(")[1].split(",")[0]
        right = step.split(", ")[1][:-1]

        nodes[node] = (left, right)

    counts = []
    start_nodes = [node for node in nodes if node[2] == "A"]
    print(start_nodes)
    for start in start_nodes:
        counts.append(get_steps(nodes, nodes[start], lines[0]))
        break

    # log.debug(counts)
    print(counts)

    # return lcm(*counts)


def main():
    # p1 = part_1()
    # print(f"Day 8 - Part 1 result: {p1}")
    with open("test/day8input4.txt") as file:
        data = file.read()
        # print(data)
        p2 = part_2(data)
        print(f"Day 8 - Part 2 result: {p2}")

    print()



main()
