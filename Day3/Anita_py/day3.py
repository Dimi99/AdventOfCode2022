with open('input.txt') as f:
    # split each line in half and get the intersection between them which is a char, put it in the list of chars
    chars = [char for line in f for char in set(line[:len(line)//2]).intersection(set(line[len(line)//2:]))]
    # for every char get its corresponding integer and sum them up
    print(sum([ord(char)-96 if char.islower() else ord(char)-38 for char in chars]))

# part 2
with open('input.txt') as f:
    # get the list of all lines
    lines = [line.strip() for line in f]
    # get every three lines and find the intersection between them
    chars = [char for i in range(0, len(lines), 3)
             for char in set(lines[i]).intersection(set(lines[i+1]).intersection(lines[i+2]))]
    # calculate the sum like in part 1
    print(sum([ord(char) - 96 if char.islower() else ord(char) - 38 for char in chars]))
