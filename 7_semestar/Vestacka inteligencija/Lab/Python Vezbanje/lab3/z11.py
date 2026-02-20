import queue

def zadatak11(graph):
    #uzmemo bilo koji cvor za startni, recimo prvi sto da ne
    start = list(graph.keys())[0]
    q = queue.Queue(len(graph))
    visited = set()
    parents = dict()
    
    q.put(start)
    visited.add(start)
    parents[start] = None
    
    while not q.empty():
        current = q.get()
        for node in graph[current]:
            if node not in visited:
                visited.add(node)
                parents[node] = current
                q.put(node)
    
    grane_grafa = [(x,y) for x in graph.keys() for y in graph[x]]
    grane_spanning_stabla = [(parents[x],x) for x in parents.keys() if parents[x] is not None]
    smemo_izbaciti_grane = [(x,y) for (x,y) in grane_grafa if ((x,y) not in grane_spanning_stabla) and ((y,x) not in grane_spanning_stabla)]
    return smemo_izbaciti_grane
    
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
    'I': ['D', 'L'],
    'J': ['E', 'F', 'L'],
    'K': ['F', 'G', 'L'],
    'L': ['J', 'K', 'I']
}

print(f"Prvi:\n{zadatak11(graph1_undirected)}\n")
print(f"Drugi:\n{zadatak11(graph2_undirected)}\n")