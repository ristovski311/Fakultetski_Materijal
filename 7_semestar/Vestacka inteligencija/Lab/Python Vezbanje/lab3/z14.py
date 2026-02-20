import queue

def zadatak14(graph):
    inv_graph = {x : [y for y in graph.keys() if x in graph[y]] for x in graph.keys()}
    start = list(graph.keys())[0]
    
    visited_reg = set()
    visited_inv = set()
    
    q_reg = queue.Queue()
    q_inv = queue.Queue()
    
    visited_reg.add(start)
    visited_inv.add(start)
    
    q_reg.put(start)
    q_inv.put(start)
    
    while not q_reg.empty():
        current_reg = q_reg.get()
        for node in graph[current_reg]:
            if node not in visited_reg:
                visited_reg.add(node)
                q_reg.put(node)
    print(visited_reg)
    if len([x for x in graph.keys() if x not in visited_reg]) > 0:
        return False
    
    while not q_inv.empty():
        current_inv = q_inv.get()
        for node in inv_graph[current_inv]:
            if node not in visited_inv:
                visited_inv.add(node)
                q_inv.put(node)
    print(f"Invertovano: {visited_inv}")
    if len([x for x in graph.keys() if x not in visited_inv]) > 0:
        return False
    else:
        return True
            
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

graph1_strong = {
    'A': ['B', 'C', 'J'],  
    'B': ['D', 'E', 'A'], 
    'C': ['F', 'G', 'A'], 
    'D': ['H', 'B'],     
    'E': ['G', 'I', 'B'], 
    'F': ['J', 'C'],      
    'G': ['J', 'C'],     
    'H': ['D', 'A'],      
    'I': ['J', 'B'],       
    'J': ['A']             
}

print(f"Prvi:\n{zadatak14(graph1)}")
print(f"Drugi:\n{zadatak14(graph1_strong)}")