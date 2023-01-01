import re
from itertools import chain
from z3 import Ints, Solver, If, sat


def manh_dist(x1, y1, x2, y2):
    return abs(x1 - x2) + abs(y1 - y2)


with open('input.txt') as f:
    coords = [list(map(int, re.findall(r'-?\d+', line.strip()))) for line in f]
    coord_dist = {(line[0], line[1]): manh_dist(*line) for line in coords}


    # col_n = list(chain.from_iterable([[line[0], line[2]] for line in coords]))
    # min_x, max_x = min(col_n), max(col_n)
    # beamers = [(line[2], line[3]) for line in coords]
    # poss_beacons = {(i, 2000000) for i in range(min_x-2000000, max_x+2000001)}
    # poss_beacons.difference_update(beamers)
    # imposs_beacons = set()
    # for coord in coord_dist:
    #     min_dist = coord_dist[coord]
    #     for beac in poss_beacons:
    #         if manh_dist(*coord, *beac) <= min_dist:
    #             imposs_beacons.add(beac)
    #     poss_beacons.difference_update(imposs_beacons)
    # print(len(imposs_beacons))

    # solution inspired by @fmardini from Reddit
    def manh_dist_z3():
        x, y = Ints('x y')
        s = Solver()
        s.add(x >= 0, y >= 0, x <= 4000000, y <= 4000000)
        for coord, dist in coord_dist.items():
            c_x, c_y = coord
            dx = If(x < c_x, c_x - x, x - c_x)
            dy = If(y < c_y, c_y - y, y - c_y)
            s.add(dx + dy > dist)
        s.check()
        m = s.model()
        return m[x], m[y], m[x].as_long() * 4000000 + m[y].as_long()


    print(manh_dist_z3())
