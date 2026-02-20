import queue 

def depth_first_search(graph, start, end):
    if start == end:
        return [start]
    stack = queue.LifoQueue(len(graph))
    visited = set()
    parents = dict()
    found_end = False
    
    visited.add(start)
    parents[start] = None
    stack.put(start)
    
    while (not found_end) and (not stack.empty()):
        current = stack.get()
        for node in graph[current]:
            if (node not in visited):
                visited.add(node)
                stack.put(node)
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

def broj_disj_puteva(graph, node1, node2):
    
    num_of_paths = 0
    par_graph = graph.copy()
    res = depth_first_search(graph,node1,node2)
    while len(res) > 0:
        num_of_paths += 1
        res_minus_nodes = res.copy()
        res_minus_nodes.remove(node1)
        res_minus_nodes.remove(node2)
        par_graph = {x : [node for node in par_graph[x] if node not in res_minus_nodes] for x in par_graph.keys() if x not in res_minus_nodes}
        res = depth_first_search(par_graph, node1, node2)
    return num_of_paths

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
    'I': ['L'],
    'J': ['L'],
    'K': ['L'],
    'L': []
}

print(f"Broj disj u prvom: {broj_disj_puteva(graph1, 'A', 'J')}")
print(f"Broj disj u drugom: {broj_disj_puteva(graph2, 'A', 'L')}")