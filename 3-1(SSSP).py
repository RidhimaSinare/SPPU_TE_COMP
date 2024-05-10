#SSSP

class Graph:

    def __init__(self, vertices) -> None:
        self.V = vertices
        self.n = len(vertices)
        self.graph = {v:{} for v in self.V}
    
    def addEdge(self, u, v, w):

        self.graph[u][v] = w
    
    def djikstra(self, src):

        visited = set()
        distances = {i:float('inf') for i in self.V}    #in self.V i.e for each vertex not in range
        distances[src] = 0

        while len(visited) < self.n:

            mindist = float('inf')
            minvertex = None

            for v in self.V:
                if v not in visited and distances[v] < mindist:
                    mindist = distances[v]
                    minvertex = v

            visited.add(minvertex)  #imp
            
            for v, w in self.graph[minvertex].items():

                dist = distances[minvertex] + w

                if dist < distances[v]:
                    distances[v] = dist
            
        for place, dist in distances.items():
            print(place, " -> ",dist)

if __name__=="__main__":

    places = input("Enter locations/vertex: ").split()

    g = Graph(places)

    e = int(input("Enter number of edges: "))

    for _ in range(e):

        u, v, w = input().split()
        g.addEdge(u, v, int(w)) #int(w) not just w
    
    src = input("Enter src: ")
    g.djikstra(src)







