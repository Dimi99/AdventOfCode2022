import numpy as np
import re

with open('input.txt') as f:
    input = np.empty((9, 8), dtype=str)
    for i in range(8):
        line = f.readline().replace('    ', '[X] ').replace(' ', '')
        input[:, i] = line[1:-2].split('][')
    stacks = [''.join(row).replace('X', '') for row in input]
    print(stacks)

    f.readline(), f.readline()
    for line in f:
        move, frm, to = map(int, re.findall(r'\d+', line))
        frm -= 1
        to -= 1
        # part 1
        # for i in range(move):
        #     stacks[to] = stacks[frm][0] + stacks[to]
        #     stacks[frm] = stacks[frm][1:]

        # part 2
        stacks[to] = stacks[frm][:move] + stacks[to]
        stacks[frm] = stacks[frm][move:]
    print(''.join(stack[0] for stack in stacks))
