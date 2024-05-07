class Graph:

    def __init__(self,vertices):
        self.vertex_map = {}
        self.V = len(vertices)
        self.graph = [[] for i in range(self.V)]
        for idx,vertex in enumerate(vertices):
            self.vertex_map[vertex] = idx

    def add_edge(self,u,v,w):
        u_idx = self.vertex_map[u]
        v_idx = self.vertex_map[v]
        self.graph[u_idx].append((v_idx,w))
        self.graph[v_idx].append((u_idx,w))
    
    def prims_mst(self):
        cost = 0
        unvisited = set(range(self.V))
        mst_set = set()

        mst_set.add(0)
        unvisited.remove(0)

        while unvisited:
            min_weight = float('inf')
            min_edge = None 
            for u in mst_set:
                for v, weight in self.graph[u]:
                    if v in unvisited and weight < min_weight:
                        min_weight = weight
                        min_edge = (u,v)

            if min_edge:
                u,v =min_edge
                print(f"Cable from router {list(self.vertex_map.keys())[u]} to router {list(self.vertex_map.keys())[v]} with cost {min_weight} added to the network.")
                #converted keys of vertex map into a list so that easy for slicing
                cost += min_weight
                mst_set.add(v)
                unvisited.remove(v)
        
        print(f"Total cost is {cost}")
def main():
    num_vertices = int(input("Enter the number of routers: "))
    vertices = input("Enter the hostname of the routers separated by space").split()
    g = Graph(vertices)

    edges = int(input("Enter the number of cables in the network: "))
    print("Enter the connections and cost for each cable (source,destination,cost): ")
    for _ in range(edges):
        u,v,w=input().split()
        g.add_edge(u,v,int(w))
    print("\n MST for routing  network: ")
    g.prims_mst()

main()