# Prikaz grafa stanja
def display_graph(graph):
    for key in graph:
        print(f"{key} | [{graph[key][0] if graph[key][0] is not None else '_'}], {graph[key][1]}")

# Prikaz islands-a
def print_islands(islands):
    for island, data in islands.items():
        print(f"{island}:")
        print(f"  Neighbors: {data['NEIGHBORS']}")
        print(f"  Cells:     {data['CELLS']}")
        print()