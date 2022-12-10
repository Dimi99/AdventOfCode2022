# # part 1
# with open('input.txt') as f:
#     register_x = 1
#     signal_strength = 0
#     cycles = [cycle for line in f for cycle in line.strip().split()]
#     for i, cycle in enumerate(cycles, 1):
#         if i in (20, 60, 100, 140, 180, 220):
#             signal_strength += register_x * i
#         if cycle.isdigit() or cycle[1:].isdigit():
#             register_x += int(cycle)
#     print(signal_strength)

# part 2
with open('input.txt') as f:
    sprite = '###' + '.' * 40
    crt = ''
    cycles = [cycle for line in f for cycle in line.strip().split()]
    smaller_cycles = [cycles[i*40:(i+1)*40] for i in range((len(cycles) + 40 - 1) // 40)]
    for sm_cycle in smaller_cycles:
        for i, cycle in enumerate(sm_cycle, 1):
            crt += '#' if sprite[i-1] == '#' else '.'
            if cycle.isdigit():
                num_hash = sprite.count('#')
                sprite = '#' * (3 - num_hash) + sprite
                sprite = '.' * (int(cycle) - 3 + num_hash) + sprite
            elif cycle[1:].isdigit():
                sprite = sprite[abs(int(cycle)):]
        with open('res.txt', 'a') as f1:
            f1.write(crt)
            f1.write('\n')
        crt = ''
