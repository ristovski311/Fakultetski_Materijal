import queue

def bfs(graph, start):
    q = queue.Queue(len(graph))
    visited = set()
    
    q.put(start)
    visited.add(start)
    
    while not q.empty():
        current = q.get()
        for node in graph[current]:
            if node not in visited:
                visited.add(node)
                q.put(node)
    
    return visited

def broj_disjunktnih(graph:dict):
    nodes = set(graph.keys())
    num_disjoint = 0
    while len(nodes) > 0:
        print(nodes)
        num_disjoint += 1
        res = bfs(graph, nodes.pop())
        nodes.difference_update(res)
    return num_disjoint
        
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

graph_disjoint_1 = {
    'A': ['B'],
    'B': ['A', 'C'],
    'C': ['B'],
    'D': ['E'],
    'E': ['D'],
    'F': ['G', 'H'],
    'G': ['F', 'I'],
    'H': ['F'],
    'I': ['G']
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

print(f"Prvi: {broj_disjunktnih(graph1_undirected)}")
print(f"Drugi: {broj_disjunktnih(graph2_undirected)}")
print(f"Disj 1: {broj_disjunktnih(graph_disjoint_1)}")
print(f"Disj 2: {broj_disjunktnih(graph_disjoint_2)}")