import queue

# def zadatak9(graph, start, duzina):
#     open_set = set()
#     closed_set = set()
#     depth = dict()
#     parents = dict()
    
#     parents[start] = None
#     open_set.add(start)
#     depth[start] = 0
    
#     while len(open_set) > 0:
#         current = min(open_set, key=lambda x: depth[x])
#         if depth[current] >= duzina:
#             break
#         for node in graph[current]:
#             if node not in open_set and node not in closed_set:
#                 open_set.add(node)
#                 depth[node] = depth[current] + 1
#                 parents[node] = current
#             else:
#                 if (depth[node] < depth[current] + 1) and (node != parents[current]) :
#                     depth[node] = depth[current] + 1
#                     if node in closed_set:
#                         closed_set.remove(node)
#                         open_set.add(node)
#         closed_set.add(current)
#         open_set.remove(current)


def zadatak9(graph, start, duzina):
    visited = set()
    q = queue.LifoQueue(len(graph))
    depth = dict()
    
    q.put(start)
    visited.add(start)
    depth[start] = 0
    
    while not q.empty():
        current = q.get()
        if depth[current] == duzina:
            continue
        for node in graph[current]:
            if node not in visited:
                depth[node] = depth[current] + 1
                visited.add(node)
                q.put(node)
    return (len([x for x in depth.keys() if depth[x] == duzina]),[x for x in depth.keys() if depth[x] == duzina])

graph1 = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': ['H'],
    'E': ['G', 'I'],
    'F': ['J'],
    'G': ['J'],
    'H': [],
    'I': ['J'],
    "J":[]
}

graph2 = {
    'A': ['B', 'C', 'D'],
    'B': ['A', 'E', 'F'],
    'C': ['A', 'G', 'F'],
    'D': ['A', 'H', 'I'],
    'E': ['B', 'J'],
    'F': ['B', 'J', 'K', 'C'],
    'G': ['C', 'K'],
    'H': ['D'],
    'I': ['D', 'L'],
    'J': ['E', 'F', 'L'],
    'K': ['F', 'G', 'L'],
    'L': ['J', 'K', 'I']
}

print(f"Prvi:\n {zadatak9(graph1, 'A', 4)}")
print(f"Drugi:\n {zadatak9(graph2, 'A', 4)}")
                