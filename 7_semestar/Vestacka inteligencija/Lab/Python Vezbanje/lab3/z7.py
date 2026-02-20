import queue

def napravi_heur(graph, start):
    open_set = set()
    closed_set = set()
    parents = dict()
    h = dict()
    
    h[start] = 0
    open_set.add(start)
    parents[start] = None
    
    while len(open_set) > 0:
        current = min(open_set, key = lambda x: h[x])
        for node in graph[current]:
            if node not in open_set and node not in closed_set:
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
    return {node : (h[node], graph[node]) if node in h else (float('inf'), graph[node]) for node in graph.keys()}

def heur_izmedju_2_cvora(graph, G1, G2):
    heur1 = napravi_heur(graph, G1)
    print(f"Prvi:\n {heur1} \n")
    
    heur2 = napravi_heur(graph, G2)
    print(f"Drugi:\n {heur2} \n")
    
    heur_final = {x: min(heur1[x], heur2[x], key=lambda a: a[0]) for x in graph.keys()}
    return heur_final
    
graph2 = {
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
    'L': ['J', 'K'],
    'S': []
}
    
print(f"Konacno:\n {heur_izmedju_2_cvora(graph2, 'B', 'D')}")