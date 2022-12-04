import re

with open('input.txt') as f:
    n_contains = 0
    for line in f:
        n1, n2, n3, n4 = map(int, re.split(r'[-,]', line.strip()))
        # part 1
        # ins = {n1: 0, n2: 0, n3: 1, n4: 1}
        # if n1 == n3 or n2 == n4 or ins[max(n1, n3)] != ins[max(n2, n4)] and n1 != n4:
        #     n_contains += 1

        # part 2
        if n2 >= n3 >= n1 or n4 >= n1 >= n3:
            n_contains += 1
    print(n_contains)
