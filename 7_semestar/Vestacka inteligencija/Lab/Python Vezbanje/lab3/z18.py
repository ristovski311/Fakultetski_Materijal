import queue

def zadatak18(graph, S):
    open_set = set()
    closed_set = set()
    h = dict()
    
    open_set.add(S)
    h[S] = 0
    while len(open_set) > 0:
        current = min(open_set, key = lambda x: h[x])
        for node in graph[current]:
            if node not in open_set and node not in closed_set:
                h[node] = h[current] + 1
                open_set.add(node)
            else:
                if h[node] > h[current] + 1:
                    h[node] = h[current] + 1
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        closed_set.add(current)
        open_set.remove(current)
    
    max_udaljenost = max(h.values())
    return [x for x in h.keys() if h[x] == max_udaljenost]

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
    'I': ['D'],
    'J': ['E', 'F', 'L'],
    'K': ['F', 'G', 'L'],
    'L': ['J', 'K']
}

print(f"Prvi:\n {zadatak18(graph1, 'A')}")
print(f"Drugi:\n {zadatak18(graph2, 'A')}")