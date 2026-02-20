import queue

# NE ZNAM UPOMOC

# def zadatak10(graph, start, end, middle):
#     if start == end or start == middle or end == middle:
#         return []
    
#     q = queue.Queue(len(graph))
#     visited = set()
#     parents = dict()
#     found_middle = False
#     found_end = False
    
#     visited.add(start)
#     parents[start] = None
#     q.put(start)
    
#     while (not found_middle) and (not q.empty()):
#         current = q.get()
#         for node in graph[current]:
#             if node not in visited:
#                 visited.add(node)
#                 q.put(node)
#                 parents[node] = current
#                 if node == middle:
#                     found_middle = True
#                     break
    
#     while (not found_end) and (not q.empty):
#         current = q.get()
#         for node in graph[current]:
#             if node not in visited:
#                 visited.add(node)
#                 q.put(node)
#                 parents[node] = current
#                 if node == end:
#                     found_end = True
#                     break
                            
    
#     path = []
#     if found_end:
#         cur = end
#         while cur is not None:
#             path.append(cur)
#             cur = parents[cur]
#         path.reverse()
#     return path    


def zadatak10(graph, start, middle, end):
    if start == end:
        return []
    if start == middle == end:
        return [start]
    
    q = queue.Queue()
    paths = []
    
    q.put([start])
    
    while not q.empty():
        current_path = q.get()
        current_node = current_path[-1]
        
        if current_node == end:
            paths.append(current_path)
            continue
        else:
            for node in graph[current_node]:
                if node not in current_path:
                    new_path = current_path + [node]
                    q.put(new_path)
    
    return min([x for x in paths if middle in x], key=lambda x: len(x))

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

print(f"Prvi:\n{zadatak10(graph1_undirected, 'A', 'G', 'J')}\n")
print(f"Drugi:\n{zadatak10(graph2_undirected, 'A', 'F', 'L')}\n")