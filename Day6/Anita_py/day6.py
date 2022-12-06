with open('input.txt') as f:
    line = f.readline()
    print([i+1 for i, char in enumerate(line, 13) if len(set(line[i-13:i+1])) == 14][0])
