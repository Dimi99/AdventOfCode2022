with open('input.txt') as f:
    visited = {(0, 0)}
    # # part 1
    # h = t = (0, 0)
    # part 2
    nodes = [(0, 0)] * 10
    drct = {'R': lambda x: (x[0] + 1, x[1]), 'L': lambda x: (x[0] - 1, x[1]),
            'U': lambda x: (x[0], x[1] + 1), 'D': lambda x: (x[0], x[1] - 1)}
    # part 2
    new_drc = {(2, 0): 'R', (-2, 0): 'L', (0, 2): 'U', (0, -2): 'D'}
    for line in f:
        drc, n = line.strip().split()
        for i in range(int(n)):
            # # part 1
            # h = drct[drc](h)
            nodes[0] = drct[drc](nodes[0])
            for j in range(1, len(nodes)):
                h, t = nodes[j-1], nodes[j]
                if abs(h[0] - t[0]) > 1 or abs(h[1] - t[1]) > 1:
                    if h[0] == t[0] or h[1] == t[1]:
                        t = drct[new_drc[(h[0]-t[0], h[1]-t[1])]](t)
                        # # part 1
                        # t = drct[drc](t)
                    else:
                        t = (t[0]+((h[0] - t[0]) // abs(h[0] - t[0])), t[1]+((h[1] - t[1]) // abs(h[1] - t[1])))
                if t == nodes[j]:
                    break
                nodes[j] = t
                if j == 9:
                    visited.add(t)
    print(len(visited))
