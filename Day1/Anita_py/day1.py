with open('input.txt') as f:
    # split by double newline, turn every line inside one elf into an integer and sum these numbers up
    # get max for part 1 and sort and get the sum for the first 3 for part 2
    print(sum(sorted([sum(map(int, elf.split('\n'))) for elf in f.read().split('\n\n') if elf], reverse=True)[:3]))
