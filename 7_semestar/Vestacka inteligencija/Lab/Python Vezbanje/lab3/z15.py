import queue

def zadatak15(graph):

    num_of_edges = sum([len(graph[x]) for x in graph.keys()])
    
    for start in graph.keys():  
        q = queue.Queue()
        q.put(([start], [])) #(put, grane_puta)
        
        while not q.empty():
            current = q.get()
            current_path = current[0]
            current_edges = current[1]
            current_node = current_path[-1]
            
            if len(current_edges) == num_of_edges:
                return current_path
            
            for node in graph[current_node]:
                if (current_node,node) not in current_edges:
                    new_path = current_path + [node]
                    new_edges = current_edges + [(current_node, node)]
                    q.put((new_path, new_edges))
                    
        return False

graph_euler = {
    'A': ['B', 'C'],   
    'B': ['D'],       
    'C': ['B'],       
    'D': ['E'],        
    'E': ['A']         
}

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

graph_euler_big = {
    'A': ['B', 'C'],
    'B': ['D'],
    'C': ['E'],
    'D': ['F', 'G'],
    'E': ['D'],
    'F': ['H'],
    'G': ['H'],
    'H': ['I'],
    'I': ['J'],
    'J': ['A']
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


print(f"Prvi:\n{zadatak15(graph_euler)}\n")
print(f"Drugi:\n{zadatak15(graph1)}\n")
print(f"Treci:\n{zadatak15(graph_euler_big)}\n")
print(f"Cetvrti:\n{zadatak15(graph2_undirected)}\n")