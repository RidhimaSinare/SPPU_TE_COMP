#prims

class Graph:

    def __init__(self, vertices) -> None:
        self.vertex_map = {}
        self.V = len(vertices)
        self.graph = [[] for i in range(self.V)]
        for idx, vertex in enumerate(vertices):
            self.vertex_map[vertex] = idx
    
    def addEdge(self, u, v, w):
        uidx = self.vertex_map[u]
        vidx = self.vertex_map[v]
        self.graph[uidx].append((vidx,w))
        self.graph[vidx].append((uidx,w))
    
    def prims(self):

        cost = 0
        unvisited = set(range(self.V))
        mst = set()

        mst.add(0)
        unvisited.remove(0)

        while unvisited:

            minweight = float('inf')
            minedge = None

            for u in mst:
                for v, w in self.graph[u]:

                    if v in unvisited and w < minweight:
                        minweight = w
                        minedge = (u,v)
            
            if minedge:

                cost += minweight
                u, v = minedge
                # prin")
                mst.add(v)
                unvisited.remove(v)
        
        print("Total cost: ", cost)

def main():
    num_vertices = int(input("Enter the number of routers: "))
    vertices = input("Enter the hostname of the routers separated by space: ").split()
    g = Graph(vertices)

    edges = int(input("Enter the number of cables in the network: "))
    print("Enter the connections and cost for each cable (source,destination,cost): ")
    for _ in range(edges):
        u,v,w=input().split()
        g.addEdge(u,v,int(w))
    print("\n MST for routing  network: ")
    g.prims()

    print(g.graph)
    print(g.vertex_map)

main()
    