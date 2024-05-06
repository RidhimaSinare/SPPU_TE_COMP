#Minimum spanning / single source shortest path problem
#SSP problem using Djikstra's algorithm for city map

class Graph:

    def __init__(self, vertices):
        self.V = vertices
        self.graph = {v: {} for v in vertices}

    def addEdge(self, u, v, w):
        #directed graph
        self.graph[u][v] = w
    
    def djikstra(self, source):

        visited = set()
        distances = {v: float('inf') for v in self.V}
        distances[source] = 0

        #iterate while all vertices are visited
        while len(visited) < len(self.V):

            minnode = None
            mindist = float('inf')
            for node in self.V:
                if node not in visited and distances[node] < mindist:
                    mindist = distances[node]
                    minnode = node
            #add the minnode to visited

            visited.add(minnode)

            for neighbour, weight in self.graph[minnode].items():

                dist = distances[minnode] + weight

                if dist < distances[neighbour]:
                    distances[neighbour] = dist

        print("\nPlace \tDistance From", source)
        for place, dist in distances.items():
            print(place, "\t", dist)

if __name__=="__main__":

    places = input("Enter the locations in the map with spaces: ").split()

    g = Graph(places)

    E = int(input("Enter the number of edges in map: "))
    print("For each edge enter src, dest and weight: ")

    for _ in range(E):
        u, v, w = input().split()
        g.addEdge(u, v, int(w))
    
    
    source_place = input("Enter the name of the source vertex: ")
    g.djikstra(source_place)

            
    


    
