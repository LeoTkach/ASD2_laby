def tarry_algorithm(graph, start_vertex, end_vertex):
    n = len(graph)
    # Початкова вершина
    current_vertex = start_vertex
    # Список відвіданих вершин
    visited_vertices = [current_vertex]
    
    # матриця зі списками вершин, в які я вже ходив із поточної
    visited_to_vertices = [[] for i in range(n)]
    # матриця зі списками вершин, з яких я вже ходив у поточну
    visited_from_vertices = [[] for i in range(n)]

    # Поки не досягнуто кінцевої вершини
    while current_vertex != end_vertex:
        
        # Оновлюємо список суміжних вершин для поточної вершини
        adj_vertices = [i for i in range(n) if graph[current_vertex][i]==1]
        # print("current_vertex",current_vertex,"              adj_vertices",adj_vertices)
        
        # print("visited_to_vertices",visited_to_vertices[current_vertex],"    visited_from_vertices",visited_from_vertices[current_vertex])

        candidate_vertices = list(set(adj_vertices) - set(visited_to_vertices[current_vertex]) - set(visited_from_vertices[current_vertex]))

        # Якщо є доступні невідвідані вершини (в які з поточної вершини я не ходив або з яких я не ходив у поточну )
        if candidate_vertices:
            # Знаходимо найменшу серед них
            next_vertex = min(candidate_vertices)
            # Додаємо нову вершину до списку відвіданих
            visited_vertices.append(next_vertex)

            # оновлюємо список вершин у які я ходив для поточної та список вершин з яких я ходив для нової вершини
            visited_to_vertices[current_vertex].append(next_vertex)
            visited_from_vertices[next_vertex].append(current_vertex)

            # наприкінці змінюємо поточну вершину на вибрану
            current_vertex = next_vertex
        else:
            # Якщо немає доступних вершин
            candidate_vertices = list(set(adj_vertices) - set(visited_to_vertices[current_vertex]))
            # Якщо є вершини, з яких ми вже ходили в поточну вершину, але які ми ще не ходили
            if candidate_vertices:
                # Знаходимо найменшу серед них
                next_vertex = min(candidate_vertices)
                # Додаємо нову вершину до списку відвіданих та оновлюємо списки для поточної та нової вершин
                visited_vertices.append(next_vertex)

                # оновлюємо список вершин у які я ходив для поточної та список вершин з яких я ходив для нової вершини
                visited_to_vertices[current_vertex].append(next_vertex)
                visited_from_vertices[next_vertex].append(current_vertex)

                # наприкінці змінюємо поточну вершину на вибрану
                current_vertex = next_vertex
            else:
                # Якщо доступних невідвіданих вершин і вершин з яких ми можемо потрапити в поточну нема
                # То повертаємо None, що означає, що шлях не знайдено
                return None
    # Повертаємо список відвіданих вершин, який утворює шлях від start_vertex до end_vertex
    return visited_vertices



def graph_information_input():
    print("Enter the number of the vertices: ")
    n=int(input())
    graph = [[0]*n for i in range(n)]
    for i in range(n):
        for j in range(i+1,n):
            print("Enter the [",i,"][",j,"] element of adjacency matrix")
            graph[i][j]=int(input())
            graph[j][i]=graph[i][j]
    print("Enter the number of the start vertex: ")
    start_vertex=int(input())
    print("Enter the number of the end vertex: ")
    end_vertex=int(input())
    print("\nManually entered graph adjacency matrix: ")
    for i in range(n):
        for j in range(n):
            print(graph[i][j], end=' ')
        print()
    return graph, start_vertex, end_vertex


def graph_information_generation():
    import random
    print("Enter the number of the vertices: ")
    n = int(input())
    graph = [[0] * n for i in range(n)]
    for i in range(n):
        for j in range(i + 1, n):
            graph[i][j] = random.randint(0, 1)
            graph[j][i] = graph[i][j]
    print("Enter the number of the start vertex: ")
    start_vertex = int(input())
    print("Enter the number of the end vertex: ")
    end_vertex = int(input())
    print("\nGenerated graph adjacency matrix: ")
    for i in range(n):
        for j in range(n):
            print(graph[i][j], end=' ')
        print()
    return graph, start_vertex, end_vertex

def graph_drawing(graph):
    import networkx as nx
    import numpy as np
    import matplotlib.pyplot as plt
    np.random.seed(1)
    adj_matrix = np.array(graph)

    G = nx.from_numpy_array(adj_matrix)

    nx.draw(G, with_labels=True)
    plt.show()



print("Do you want to enter adjacency matrix manually or generate it instead ?(y/n)")
ans=input()
if (ans=='y'):
    graph, start_vertex, end_vertex=graph_information_input()
else:
    graph, start_vertex, end_vertex=graph_information_generation()




path = tarry_algorithm(graph, start_vertex, end_vertex)

if not path:
    print("There is no path between start_vertex and end_vertex")
    graph_drawing(graph)
else:
    print("Visited verticies: ")
    print(path)
    graph_drawing(graph)
