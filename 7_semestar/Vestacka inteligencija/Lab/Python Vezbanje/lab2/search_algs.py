from functools import reduce
import queue

def breadth_first_search(g, start, end):
    if start == end:
        return [start]
    
    red = queue.Queue(len(g))
    obidjeni = set()
    prethodnici = dict()
    nadjen_cilj = False
    
    red.put(start)
    prethodnici[start] = None
    obidjeni.add(start)
    
    while (not nadjen_cilj) and (not red.empty()):
        trenutni_cvor = red.get()
        #obrada cvora
        for cvor in g[trenutni_cvor]:
            if cvor not in obidjeni:
                prethodnici[cvor] = trenutni_cvor
                obidjeni.add(cvor)
                red.put(cvor)
                if cvor == end:
                    nadjen_cilj = True
                    break
    path = []
    if(nadjen_cilj):
        cur = end
        while cur is not None:
            path.append(cur)
            cur = prethodnici[cur]
        path.reverse()
    return path        
             
            
def depth_first_search(g, start, end):
    
    if start == end:
        return [start]
    
    stack = queue.LifoQueue(len(g))
    visited = set()
    parent = dict()
    end_found = False
    
    parent[start] = None
    visited.add(start)
    stack.put(start)
    
    while (not end_found) and (not stack.empty()):
        current = stack.get()
        #obrada
        for node in g[current]:
            if node not in visited:
                parent[node] = current
                visited.add(node)
                stack.put(node)
                if node == end:
                    end_found = True
                    break
    path = []
    if(end_found):
        cur = end
        while cur is not None:
            path.append(cur)
            cur = parent[cur]
        path.reverse()
    return path
        

def hill_climbing_search(g, start, end):
    if start == end:
        return [start]
    
    stack = queue.LifoQueue(len(g))
    visited = set()
    parent = dict()
    found_end = False
    
    parent[start] = None
    stack.put(start)
    visited.add(start)
    
    while (not found_end) and (not stack.empty()):
        current = stack.get()
        #obrada
        destinations = [(g[dest][0], dest) for dest in g[current][1]]
        for dest in sorted(destinations, reverse=True):
            if dest[1] not in visited:
                visited.add(dest[1])
                stack.put(dest[1])
                parent[dest[1]] = current
                if dest[1] == end:
                    found_end = True
                    break
    path = []
    if found_end:
        cur = end
        while cur is not None:
            path.append(cur)
            cur = parent[cur]
        path.reverse()
    return path

def best_first_search(g,start,end):
    if start == end:
        return [start]
    
    priority = queue.PriorityQueue(len(g))
    visited = set()
    parents = dict()
    found_end = False
    
    priority.put((g[start][0],start))
    visited.add(start)
    parents[start] = None
    
    while (not found_end) and not (priority.empty()):
        current = priority.get()
        current_node = current[1]
        #obrada
        for node in g[current_node][1]:
            if node not in visited:
                visited.add(node)
                priority.put((g[node][0],node))
                parents[node] = current_node
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

def a_star_search(graph, start, end):
    if start == end:
        return [start]
    
    open_set = set()
    closed_set = set()
    parents = dict()
    found_end = False
    g = dict()
    
    open_set.add(start)
    parents[start] = None
    g[start] = 0
    
    while (not found_end) and (len(open_set) > 0):
        current = min(open_set, key = lambda x: g[x] + graph[x][0])
        if current == end:
            found_end = True
            break
        for (node, cost) in graph[current][1]:
            if node not in open_set and node not in closed_set:
                open_set.add(node)
                parents[node] = current
                g[node] = g[current] + cost
            else:
                if g[current] + cost < g[node]:
                    parents[node] = current
                    g[node] = g[current] + cost
                    #VEOMA VAZNO OVO:
                    if node in closed_set:
                        closed_set.remove(node)
                        open_set.add(node)
        open_set.remove(current)
        closed_set.add(current)
            
    path = []
    if found_end:
        cur = end
        while cur is not None:
            path.append(cur)
            cur = parents[cur]
        path.reverse()
    return path