import queue

def zadatak12(graph, start,end, length):
    paths = []
    q = queue.Queue()
    
    q.put([start])
    
    while not q.empty():
        current_path = q.get()
        current_node = current_path[-1] #Poslednji u putu
        
        if current_node == end and len(current_path) - 1 == length: # ako je broj cvorova n, broj grana je n-1,
            paths.append(current_path) # pa je duzina puta n-1, i ako je bas jednaka length to je nadjen put
            continue
        elif len(current_path) - 1 >= length: #ako current_node nije end, a duzina nam je veca ili jednaka od length, kraj!!!
            continue
        else:
            for node in graph[current_node]:
                if node not in current_path:
                    new_path = current_path.copy()
                    new_path.append(node)
                    q.put(new_path)
    return paths

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

print(f"Prvi:\n{zadatak12(graph1_undirected, 'A', 'J', 3)}")
print(f"Drugi:\n{zadatak12(graph2_undirected, 'A', 'L', 6)}")