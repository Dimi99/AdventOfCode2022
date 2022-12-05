from collections import defaultdict
# corresponds to the score each number gives
scores = {'A': 1, 'X': 1, 'B': 2, 'Y': 2, 'C': 3, 'Z': 3}
outcomes = defaultdict(int)
# the outcome is 3 if it's draw when the difference between scores is 0, 6 if the difference is -2 or 1,
# and 0 in all the other cases
outcomes.update({0: 3, 1: 6, -2: 6})
# get the score of each number plus the difference between the scores
with open('input.txt') as f:
    print(sum([scores[line.split()[1]] + outcomes[(scores[line.split()[1]] - scores[line.split()[0]])] for line in f]))

# part 2
# get the correspondence of the outcomes when player2 loses and wins
loses = {'A': 'C', 'B': 'A', 'C': 'B'}
wins = {'A': 'B', 'B': 'C', 'C': 'A'}

with open('input.txt') as f:
    res = 0
    for line in f:
        plr1, plr2 = line.split()
        # get the corresponding letter from wins and loses dicts and their scores from scores dict
        res += scores[loses[plr1]] if plr2 == 'X' else scores[wins[plr1]]+6 if plr2 == 'Z' else scores[plr1]+3
    print(res)
