from collections import defaultdict
scores = {'A': 1, 'X': 1, 'B': 2, 'Y': 2, 'C': 3, 'Z': 3}
outcomes = defaultdict(int)
outcomes.update({0: 3, 1: 6, -2: 6})
with open('input.txt') as f:
    print(sum([scores[line.split()[1]] + outcomes[(scores[line.split()[1]] - scores[line.split()[0]])] for line in f]))

# part 2
loses = {'A': 'C', 'B': 'A', 'C': 'B'}
wins = {'A': 'B', 'B': 'C', 'C': 'A'}

with open('input.txt') as f:
    res = 0
    for line in f:
        plr1, plr2 = line.split()
        res += scores[loses[plr1]] if plr2 == 'X' else scores[wins[plr1]]+6 if plr2 == 'Z' else scores[plr1]+3
    print(res)
