#prims

class Graph:

    def __init__(self, vertices) -> None:
        self.V = len(vertices)
        self.graph = [[] for i in range(self.V)]
        self.vertex_map = {}

        for idx, vertex in enumerate(vertices):
            self.vertex_map[vertex] = idx
    
    def addEdge(self, u, v, w):

        uidx = self.vertex_map[u]
        vidx = self.vertex_map[v]
        self.graph[uidx].append((vidx, w))
        self.graph[vidx].append((uidx, w))

    def prims(self):

        mst = set()
        unvisited = set(range(self.V))
        cost = 0

        mst.add(0)  #remember to add first in mst and remove from unvisited
        unvisited.remove(0)

        while unvisited:

            minedge = None
            mindist = float('inf')

            for u in mst:

                for v, w in self.graph[u]:  #not items()

                    if v in unvisited and w<mindist:
                        minedge = (u,v)
                        mindist = w
            
            if minedge:

                u, v = minedge
                cost += mindist
                unvisited.remove(v) #remember to both add and remove
                mst.add(v)
        
        print("Final cost: ", cost)


if __name__=="__main__":

    routers = input("Enter router names: ").split()

    g = Graph(routers)

    e = int(input("Enter number of connections: "))

    for _ in range(e):
        
        u, v, w = input("Enter route and weight: ").split()
        g.addEdge(u, v, int(w))
    
    g.prims()

    print(g.vertex_map)
