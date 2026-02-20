import queue

def a_star_modified(graph, start):
    open_set = set()
    closed_set = set()
    heur = dict()
    
    open_set.add(start)
    heur[start] = 0
    while len(open_set) > 0:
        current = min(open_set, key=lambda x: heur[x])
        for (node, price) in graph[current]:
            if node not in closed_set and node not in open_set:
                open_set.add(node)
                heur[node] = heur[current] + price
            else:
                if heur[node] > heur[current] + price:
                    heur[node] = heur[current] + price
                    if node in closed_set:
                        open_set.add(node)
                        closed_set.remove(node)
        open_set.remove(current)
        closed_set.add(current)
    return {
        x : (heur[x], graph[x]) if x in heur else (float('inf') , graph[x]) for x in graph.keys()
    }
    
def zadatak20(graph, g1, g2):
    res1 = a_star_modified(graph, g1)
    res2 = a_star_modified(graph, g2)
    print(res1)
    print("\n")
    print(res2)
    return {
        x : (min(res1[x][0],res2[x][0]), graph[x]) for x in graph.keys()
    }
    
graph = {
    'A': [('B', 2), ('C', 5)],
    'B': [('A', 2), ('D', 4), ('E', 1)],
    'C': [('A', 5), ('E', 3)],
    'D': [('B', 4), ('F', 2)],
    'E': [('B', 1), ('C', 3), ('F', 2)],
    'F': [('D', 2), ('E', 2)]
}
    
print(f"\nPrvi:\n{zadatak20(graph, 'B', 'F')}\n")