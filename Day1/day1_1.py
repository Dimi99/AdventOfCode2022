with open('A_day1_input.txt') as f:
    print(sum(sorted([sum(map(int, elf.split('\n'))) for elf in f.read().split('\n\n') if elf], reverse=True)[:3]))
