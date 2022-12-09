with open('input.txt') as f:
    visited = {(0, 0)}
    h = t = (0, 0)
    drct = {'R': lambda x: (x[0] + 1, x[1]), 'L': lambda x: (x[0] - 1, x[1]),
            'U': lambda x: (x[0], x[1] + 1), 'D': lambda x: (x[0], x[1] - 1)}
    for line in f:
        drc, n = line.strip().split()
        for i in range(int(n)):
            h = drct[drc](h)
            if abs(h[0] - t[0]) > 1 or abs(h[1] - t[1]) > 1:
                if h[0] == t[0] or h[1] == t[1]:
                    t = drct[drc](t)
                else:
                    t = (t[0]+((h[0] - t[0]) // abs(h[0] - t[0])), t[1]+((h[1] - t[1]) // abs(h[1] - t[1])))
            visited.add(t)
    print(len(visited))
