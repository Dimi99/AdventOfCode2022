from collections import defaultdict

with open('input.txt') as f:
    position_char = dict(((i, j), ord(ch)-97) if ch.islower() else ((ch,), (i, j))
                         for i, sent in enumerate(f.readlines()) for j, ch in enumerate(sent.strip()))
    shortest_path = defaultdict(lambda: 10000)
    start, end = position_char.pop(('S',)), position_char.pop(('E',))
    position_char.update({start: 0, end: 25})
    shortest_path[start] = 0

    reachable = [start]
    while len(reachable) != 0:
        node = reachable.pop(0)
        node_x, node_y = node
        neighbours = {(node_x-1, node_y), (node_x+1, node_y), (node_x, node_y-1), (node_x, node_y+1)}\
            .intersection(position_char)
        for neigh in neighbours:
            if position_char[neigh] - position_char[node] <= 1:
                if shortest_path[node]+1 < shortest_path[neigh]:
                    shortest_path[neigh] = shortest_path[node]+1
                    reachable.append(neigh)
    print(shortest_path[end])


    # # part 2
    # for position, char in position_char.items():
    #     if char == 0:
    #         reachable = [position]
    #         shortest_path[position] = 0
    #         while len(reachable) != 0:
    #             node = reachable.pop(0)
    #             node_x, node_y = node
    #             neighbours = {(node_x-1, node_y), (node_x+1, node_y), (node_x, node_y-1), (node_x, node_y+1)}\
    #                 .intersection(position_char)
    #             for neigh in neighbours:
    #                 if position_char[neigh] - position_char[node] <= 1:
    #                     if shortest_path[node]+1 < shortest_path[neigh]:
    #                         shortest_path[neigh] = shortest_path[node]+1
    #                         reachable.append(neigh)
    #         shortest = min(shortest_path[end], shortest)
    #         shortest_path.clear()
    # print(shortest)
