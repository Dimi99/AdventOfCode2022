def compare(i1, i2):
    if type(i1) == type(i2) == int:
        if i1 < i2:
            return True, True
        elif i1 == i2:
            return True, False
        return False, False
    elif i1 == i2 == []:
        return True, False
    elif i1 == []:
        return True, True
    elif i2 == []:
        return False, False
    elif type(i1) == type(i2) == list:
        for i in range(min(len(i1), len(i2))):
            res = compare(i1[i], i2[i])
            if res[1] or not res[0]:
                return res
        return len(i1)<=len(i2), len(i1)<len(i2)
    elif type(i1) == int:
        return compare([i1], i2)
    else:
        return compare(i1, [i2])


with open('input.txt') as f:
    c = 0
    pairs = [list(map(eval, pairs.strip().split('\n'))) for pairs in f.read().split('\n\n') if pairs]
    for i, pair in enumerate(pairs, 1):
        c += i
        if len(pair[0]) > len(pair[1]):
            pair[1].append([-1]*(len(pair[0])-len(pair[1])))
        for item1, item2 in zip(pair[0], pair[1]):
            res = compare(item1, item2)
            if not res[0]:
                c -= i
                break
            elif res == (True, True):
                break
    print(c)