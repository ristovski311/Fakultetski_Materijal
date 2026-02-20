import queue

def zadatak17(graph, G):
    open_set = set()
    closed_set = set()
    h = dict()
    parents = dict()
    
    start = G
    
    open_set.add(start)
    parents[start] = None
    h[start] = 0
    
    while len(open_set) > 0:
        current = min(open_set, key=lambda x: h[x])
        for (node, price) in graph[current]:
            if node not in open_set and node not in closed_set:
                open_set.add(node)
                h[node] = h[current] + price
                parents[node] = current
            else:
                if h[node] > h[current] + price:
                    h[node] = h[current] + price
                    parents[node] = current
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        open_set.remove(current)
        closed_set.add(current)
        
    return {
        x : (h[x], graph[x]) for x in graph.keys()
    }
    
graph = {
    'A': [('B', 2), ('C', 5)],
    'B': [('A', 2), ('D', 4), ('E', 1)],
    'C': [('A', 5), ('E', 3)],
    'D': [('B', 4), ('F', 2)],
    'E': [('B', 1), ('C', 3), ('F', 2)],
    'F': [('D', 2), ('E', 2)]
}

# print(f"Prvi:\n{zadatak17(graph, 'A')}\n")
# print(f"Prvi:\n{zadatak17(graph, 'B')}\n")
# print(f"Prvi:\n{zadatak17(graph, 'C')}\n")
print(f"Prvi:\n{zadatak17(graph, 'D')}\n")
# print(f"Prvi:\n{zadatak17(graph, 'E')}\n")
# print(f"Prvi:\n{zadatak17(graph, 'F')}\n")