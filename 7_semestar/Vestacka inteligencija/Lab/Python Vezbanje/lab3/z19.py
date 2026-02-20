import queue

def a_star(graph, start, end, forbidden):
    if start == end:
        return [start]
    open_set = set()
    closed_set = set()
    parents = dict()
    found_end = False
    g = dict()
    
    parents[start] = None
    open_set.add(start)
    g[start] = 0
    
    while not found_end and len(open_set) > 0:
        current = min(open_set, key = lambda x: g[x])
        if current == end:
            found_end = True
            break
        for node in graph[current]:
            if node in forbidden:
                continue
            if node not in open_set and node not in closed_set:
                parents[node] = current
                g[node] = g[current] + 1
                open_set.add(node)
            else:
                if g[node] > g[current] + 1:
                    g[node] = g[current] + 1
                    parents[node] = current
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        open_set.remove(current)
        closed_set.add(current)

    path = []
    if found_end:
        cur = end
        while cur is not None:
            path.append(cur)
            cur = parents[cur]
        path.reverse()
    return path

def zadatak19(graph, s, m):
    res = a_star(graph, s, m, [])
    if len(res) == 0:
        return []
    res2 = a_star(graph, m, s, [x for x in res if x != s])
    if len(res2) == 0:
        return [] 
    return res + res2

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

graph1_undirected = {
    'A': ['B', 'C'],
    'B': ['A', 'D', 'E'],
    'C': ['A', 'F', 'G'],
    'D': ['B', 'H'],
    'E': ['B', 'G', 'I'],
    'F': ['C', 'J'],
    'G': ['C', 'E', 'J'],
    'H': ['D'],
    'I': ['E', 'J'],
    'J': ['F', 'G', 'I']
}

graph2_undirected = {
    'A': ['B', 'C', 'D'],
    'B': ['A', 'E', 'F'],
    'C': ['A', 'G'],
    'D': ['A', 'H', 'I'],
    'E': ['B', 'J'],
    'F': ['B', 'J', 'K'],
    'G': ['C', 'K'],
    'H': ['D'],
    'I': ['D'],
    'J': ['E', 'F', 'L'],
    'K': ['F', 'G', 'L'],
    'L': ['J', 'K']
}

# ISTI KAO 16

print(f"Prvi:\n{zadatak19(graph1, 'A', 'C')}")
print(f"Drugi:\n{zadatak19(graph2_undirected, 'A', 'G')}")