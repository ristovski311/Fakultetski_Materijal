import queue

def modifier_a_star(graph, start):
    
    open_set = set()
    closed_set = set()
    g = dict()
    parents = dict()
    
    g[start] = 0
    parents[start] = None
    open_set.add(start)
    
    while len(open_set) > 0:
        current = min(open_set, key = lambda x: g[x])
        for node in graph[current]:
            if node not in open_set and node not in closed_set:
                g[node] = g[current] + 1
                parents[node] = current
                open_set.add(node)
            else:
                if g[node] > g[current] + 1:
                    g[node] = g[current] + 1
                    parents[node] = current
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        closed_set.add(current)
        open_set.remove(current)
    
    return [(node,g[node]) for node in g.keys()]
        
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
    'F': ['J', 'K', 'L'],
    'G': ['K'],
    'H': [],
    'I': [],
    'J': ['L'],
    'K': ['L'],
    'L': []
}

print(f"Prvi:\n {modifier_a_star(graph1, 'A')}\n")
print(f"Drugi:\n {modifier_a_star(graph2, 'F')}\n")