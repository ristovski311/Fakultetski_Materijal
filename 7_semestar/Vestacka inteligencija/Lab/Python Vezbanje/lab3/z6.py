import queue

graph1_heur = {
    'A': (9,['B', 'C']),
    'B': (6,['D', 'E']),
    'C': (7,['F', 'G']),
    'D': (4,['H']),
    'E': (8,['G', 'I']),
    'F': (3,['J']),
    'G': (4,['J']),
    'H': (4,[]),
    'I': (3,['J']),
    "J":(0,[])
}

def best_first_stablo(graph, start):
    priority = queue.PriorityQueue(len(graph))
    visited = set()
    parents = dict()
    children = {x : [] for x in graph.keys()}
    
    priority.put((graph[start][0],start))
    visited.add(start)
    parents[start] = None
    
    while not priority.empty():
        current = priority.get()
        current_node = current[1]
        for node in graph[current_node][1]:
            if node not in visited:
                parents[node] = current_node
                children[current_node].append(node)
                visited.add(node)
                priority.put((graph[node][0], node))
    
    return children

print(f"Prvi:\n {best_first_stablo(graph1_heur, 'A')}")