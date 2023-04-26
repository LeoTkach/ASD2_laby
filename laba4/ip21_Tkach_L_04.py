def tarry_algorithm(graph, start_vertex, end_vertex):
    n = len(graph)
    # спочатку встановлюю поточну вершину, як початкову
    current_vertex = start_vertex
    # створюю список відвіданих вершин та одразу додаю туди першу початкову вершину
    visited_vertices = [current_vertex]
    
    # матриця зі списками вершин, в які я вже ходив із поточної
    visited_to_vertices = [[] for i in range(n)]
    # матриця зі списками вершин, з яких я вже ходив у поточну
    visited_from_vertices = [[] for i in range(n)]

    # запускаю цикл, поки не досягнуто кінцевої вершини
    while current_vertex != end_vertex:
        
        # створюю список суміжних вершин для поточної вершини
        adj_vertices = [i for i in range(n) if graph[current_vertex][i]==1]
       
        # створюю список доступних невідвіданих вершини (в які з поточної вершини я не ходив та з яких я не ходив у поточну )
        candidate_vertices = list(set(adj_vertices) - set(visited_to_vertices[current_vertex]) - set(visited_from_vertices[current_vertex]))

        # Якщо є доступні невідвідані вершини 
        if candidate_vertices:
            # обираємо найменшу серед них
            next_vertex = candidate_vertices[0]

            # Додаємо нову вершину до списку відвіданих
            visited_vertices.append(next_vertex)

            # оновлюємо список вершин у які я ходив для поточної та список вершин з яких я ходив для нової вершини
            visited_to_vertices[current_vertex].append(next_vertex)
            visited_from_vertices[next_vertex].append(current_vertex)

            # наприкінці змінюємо поточну вершину на обрану
            current_vertex = next_vertex

        # Якщо немає доступних вершин, тобто той список пустий
        else:   
            # тоді створюємо новий список достпуних вершин, але тепер туди входять ті вершини з яких в поточну ми вже ходили
            candidate_vertices = list(set(adj_vertices) - set(visited_to_vertices[current_vertex]))

            # Якщо є вершини, з яких ми вже ходили в поточну вершину, але які ми ще не ходили
            if candidate_vertices:
                # обираємо найменшу серед них
                next_vertex = candidate_vertices[0]

                # Додаємо нову вершину до списку відвіданих
                visited_vertices.append(next_vertex)

                # оновлюємо список вершин у які я ходив для поточної та список вершин з яких я ходив для нової вершини
                visited_to_vertices[current_vertex].append(next_vertex)
                visited_from_vertices[next_vertex].append(current_vertex)

                # наприкінці змінюємо поточну вершину на обрану
                current_vertex = next_vertex
            else:
                # Якщо залишились тількі ті вершини, в які з цієї вершини ми вже ходили
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
    print("There is no path between",start_vertex,"and",end_vertex)
    graph_drawing(graph)
else:
    print("The path between",start_vertex,"and",end_vertex,"is: ")
    print(path)
    graph_drawing(graph)
