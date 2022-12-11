import re
from collections import defaultdict, Counter

with open('input.txt') as f:
    items = defaultdict(list)
    operations = defaultdict()
    divide_by = defaultdict(int)
    true_throw_to = defaultdict(int)
    false_throw_to = defaultdict(int)
    inspected_items = Counter()
    monkeys = [[line.strip() for line in monkey.split('\n')] for monkey in f.read().split('\n\n') if monkey]
    for monkey in monkeys:
        monkey_n = int(re.findall(r'\d+', monkey[0])[0])
        items[monkey_n] = list(map(int, re.findall(r'\d+', monkey[1])))
        operation = re.findall(r'old (.*)', monkey[2])[0]
        oper, num = operation[0], operation[2:]
        operations[monkey_n] = (oper, num)
        last_three_lines = ' '.join(monkey[3:6])
        divide_by[monkey_n], true_throw_to[monkey_n], false_throw_to[monkey_n] =\
            map(int, re.findall(r'\d+', last_three_lines))
    for r in range(20):
        for m in range(8):
            inspected_items[m] += len(items[m])
            for item in items[m]:
                oper, num = operations[m]
                num = item if num == 'old' else int(num)
                new_i = item * num if oper == '*' else item + num
                items[true_throw_to[m]].append(new_i) if new_i % divide_by[m] == 0\
                    else items[false_throw_to[m]].append(new_i)
            items[m] = []
    print(inspected_items.most_common(2)[0][1] * inspected_items.most_common(2)[1][1])


