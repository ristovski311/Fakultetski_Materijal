import queue

def bfs(graph, start, end, forbidden):
    q = queue.Queue()
    visited = set()
    parents = dict()
    found_end = False
    
    q.put(start)
    visited.add(start)
    parents[start] = None
    
    while not found_end and not q.empty():
        current = q.get()
        for node in graph[current]:
            if node in forbidden:
                continue
            if node not in visited:
                visited.add(node)
                q.put(node)
                parents[node] = current
                if node == end:
                    found_end = True
                    break
    path = []
    if found_end:
        cur = end
        while cur is not None:
            path.append(cur)
            cur = parents[cur]
        path.reverse()
    return path

def zadatak16(graph, s, m, g):
    forbidden = []
    res = bfs(graph, s, m, forbidden)
    if len(res) == 0:
        return []
    forbidden = forbidden + res
    res2 = bfs(graph, m, g, forbidden)
    if len(res2) == 0:
        return []
    res2.remove(m)
    res_final = res + res2
    return res_final

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

print(f"Prvi:\n{zadatak16(graph1, 'A', 'H', 'J')}\n")
print(f"Drugi:\n{zadatak16(graph2, 'A', 'F', 'L')}\n")
