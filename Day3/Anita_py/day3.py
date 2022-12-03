with open('input.txt') as f:
    chars = [char for line in f for char in set(line[:len(line)//2]).intersection(set(line[len(line)//2:]))]
    print(sum([ord(char)-96 if char.islower() else ord(char)-38 for char in chars]))

with open('input.txt') as f:
    lines = [line.strip() for line in f]
    chars = [char for i in range(0, len(lines), 3)
             for char in set(lines[i]).intersection(set(lines[i+1]).intersection(lines[i+2]))]
    print(sum([ord(char) - 96 if char.islower() else ord(char) - 38 for char in chars]))
