import numpy as np
import re

with open('input.txt') as f:
    input = np.empty((9, 8), dtype=str)
    for i in range(8):
        # for each line replace an empty 'cell' with '[X]'
        line = f.readline().replace('    ', '[X] ').replace(' ', '')
        # put all the letters as a column in the matrix
        input[:, i] = line[1:-2].split('][')
    # replace 'X' with an empty string for every row - the result corresponds to one stack
    stacks = [''.join(row).replace('X', '') for row in input]
    print(stacks)

    f.readline(), f.readline()
    for line in f:
        # get how many blocks should be moved and from where to where
        move, frm, to = map(int, re.findall(r'\d+', line))
        frm -= 1
        to -= 1
        # part 1
        # for i in range(move):
        # # "move" blocks one by one, adding them to the beginning of one line and removing from the beginning of the
        # # another one
        #     stacks[to] = stacks[frm][0] + stacks[to]
        #     stacks[frm] = stacks[frm][1:]

        # part 2
        # same as for part 1 but "move" all the blocks at once
        stacks[to] = stacks[frm][:move] + stacks[to]
        stacks[frm] = stacks[frm][move:]
    print(''.join(stack[0] for stack in stacks))
