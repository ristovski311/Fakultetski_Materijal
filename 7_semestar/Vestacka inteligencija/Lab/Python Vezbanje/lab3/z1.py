import queue


def visina_stabla_trazenja(graph, start):
    q = queue.Queue(len(graph))
    visited = set()
    level = dict()
    
    level[start] = 1
    visited.add(start)
    q.put(start)
    
    while not q.empty():
        current = q.get()
        for node in reversed(graph[current]):
            if node not in visited:
                visited.add(node)
                level[node] = level[current] + 1
                q.put(node)
    max_level = max(level, key = level.get)
    return (max_level, level[max_level])

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
    'B': ['E', 'F'],
    'C': ['G'],
    'D': ['H', 'I'],
    'E': ['J'],
    'F': ['J', 'K'],
    'G': ['K'],
    'H': [],
    'I': [],
    'J': ['L'],
    'K': ['L'],
    'L': []
}

print(f"Visina prvog: {visina_stabla_trazenja(graph1, 'A')}")
print(f"Visina drugog: {visina_stabla_trazenja(graph2, 'A')}")