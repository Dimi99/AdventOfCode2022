import re

with open('input.txt') as f:
    n_contains = 0
    for line in f:
        # get all 4 int numbers from each line
        n1, n2, n3, n4 = map(int, re.split(r'[-,]', line.strip()))
        # part 1
        # # create the dictionary corresponding to the position of each number
        # ins = {n1: 0, n2: 0, n3: 1, n4: 1}
        # # one range is inside another one if their starts are the same, if their ends are the same, or if one start is
        # # bigger than another start and at the same time its end is smaller than another end. Also n1 != n4 as for
        # # equal numbers dictionary breaks
        # if n1 == n3 or n2 == n4 or ins[max(n1, n3)] != ins[max(n2, n4)] and n1 != n4:
        #     n_contains += 1

        # part 2
        # if the beginning of one range is smaller than the beginning of another range while its end is smaller
        # than this beginning, the ranges intersect
        if n2 >= n3 >= n1 or n4 >= n1 >= n3:
            n_contains += 1
    print(n_contains)
