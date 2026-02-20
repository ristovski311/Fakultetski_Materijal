import queue

# identican kao zadatak 11, samo moram po komponentama da uradim izbacivanje grana!

def spanning_tree(graph, start):
    visited = set()
    q = queue.Queue()
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
        
    return ([(parents[x], x) for x in parents if x != start], visited) # Ovo vraca grane tipa (roditelj, dete) koje cine sprezno stablo

def zadatak13(graph):
    start = list(graph.keys())[0]
    
    sve_grane_grafa = [(x, y) for x in graph.keys() for y in graph[x]]
    grane_za_brisanje = sve_grane_grafa.copy()
    obradjeni_cvorovi = []
    
    res, visited = spanning_tree(graph, start)
    while len(res) > 0:
        grane_za_brisanje = [edge for edge in grane_za_brisanje if edge not in res]
        obradjeni_cvorovi += visited
        neobradjeni_cvorovi = [x for x in graph.keys() if x not in obradjeni_cvorovi]
        if len(neobradjeni_cvorovi) == 0:
            break
        next_start = neobradjeni_cvorovi[0]
        res, visited = spanning_tree(graph, next_start)
    return(grane_za_brisanje)

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

graph3 = {
    # Komponenta 1
    'A': ['B'],
    'B': ['C'],
    'C': ['A', 'D'],   # ciklus A → B → C → A
    'D': [],

    # Komponenta 2
    'E': ['F'],
    'F': ['G'],
    'G': ['E', 'H'],   # ciklus E → F → G → E
    'H': []
}

print(f"Prvi:\n {zadatak13(graph1)}\n")
print(f"Drugi:\n {zadatak13(graph2)}\n")
print(f"Treci:\n {zadatak13(graph3)}\n")