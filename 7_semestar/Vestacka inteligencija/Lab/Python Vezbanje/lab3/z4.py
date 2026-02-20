import queue

def formiraj(graph, end):
    start = end # zato sto je neusmeren, mozemo tretirati end kao start i od njega traziti ostale cvorove tj njihovu udaljenost
    
    open_set = set()
    closed_set = set()
    parents = dict() #nije mi potrebno bas
    h = dict()
    
    h[start] = 0
    open_set.add(start)
    parents[start] = None
    
    while len(open_set) > 0:
        current = min(open_set, key= lambda x: h[x])
        for node in graph[current]:
            if (node not in closed_set) and (node not in open_set):
                open_set.add(node)
                h[node] = h[current] + 1
                parents[node] = current
            else:
                if h[node] > h[current] + 1:
                    h[node] = h[current] + 1
                    parents[node] = current
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        open_set.remove(current)
        closed_set.add(current)
    return {
        node: (h[node], graph[node]) for node in graph.keys()
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

print(f"Prvi: {formiraj(graph1_undirected, 'G')}")
print(f"Drugi: {formiraj(graph2_undirected, 'G')}")