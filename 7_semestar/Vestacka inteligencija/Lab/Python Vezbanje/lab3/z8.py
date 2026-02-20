import queue

def bfs_bidirect(graph, start, end):
    if start == end:
        return [start]
    
    q_start = queue.Queue(len(graph))
    q_end = queue.Queue(len(graph))
    visited_start = set()
    visited_end = set()
    parents_start = dict()
    parents_end = dict()
    common = None
    
    q_start.put(start)
    q_end.put(end)
    visited_start.add(start)
    visited_end.add(end)
    parents_start[start] = None
    parents_end[end] = None
    
    while (common is None) and (not q_start.empty()) and (not q_end.empty()):
        current_start = q_start.get()
        current_end = q_end.get()
        for node in graph[current_start]:
            if node not in visited_start:
                visited_start.add(node)
                q_start.put(node)
                parents_start[node] = current_start
                if node in visited_end:
                    common = node
                    break
        if common is not None:
            break
        for node in graph[current_end]:
            if node not in visited_end:
                visited_end.add(node)
                parents_end[node] = current_end
                q_end.put(node)
                if node in visited_start:
                    common = node
                    break
    
    path = []
    if common is not None:
        cur = common
        while cur is not None:
            path.append(cur)
            cur = parents_start[cur]
        path.reverse()
        cur = parents_end[common]
        while cur is not None:
            path.append(cur)
            cur = parents_end[cur]
    return path

graph2_undirected = {
    'A': ['B', 'C', 'D'],
    'B': ['A', 'E', 'F'],
    'C': ['A', 'G'],
    'D': ['A', 'H', 'I'],
    'E': ['B', 'J'],
    'F': ['B', 'J', 'K'],
    'G': ['C', 'K'],
    'H': ['D'],
    'I': ['D', 'L'],
    'J': ['E', 'F'],
    'K': ['F', 'G'],
    'L': ['I']
}

graph_disjoint_2 = {
    1: [2],
    2: [1],
    3: [4],
    4: [3, 5],
    5: [4],
    6: [],
    7: [8, 9],
    8: [7, 10],
    9: [7, 10],
    10: [8, 9]
}

print(f"Rezultat grafa 2:\n {bfs_bidirect(graph2_undirected, 'H', 'E')}\n")
print(f"Rezultat grafa 2 disjoint-a:\n {bfs_bidirect(graph_disjoint_2, 7, 10)}")
    