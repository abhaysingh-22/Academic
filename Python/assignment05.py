# ----- GRAPH REPRESENTATION + MST USING KRUSKAL & PRIM -----

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.graph = []  # For Kruskal (Edge List)
        self.adj = [[] for _ in range(vertices)]  # For Prim (Adjacency List)

    def add_edge(self, u, v, w):
        # Add to edge list
        self.graph.append([u, v, w])
        # Add to adjacency list
        self.adj[u].append((v, w))
        self.adj[v].append((u, w))

    # ---------- KRUSKAL'S ALGORITHM ----------
    def find_parent(self, parent, i):
        if parent[i] == i:
            return i
        return self.find_parent(parent, parent[i])

    def union(self, parent, rank, x, y):
        xroot = self.find_parent(parent, x)
        yroot = self.find_parent(parent, y)
        if rank[xroot] < rank[yroot]:
            parent[xroot] = yroot
        elif rank[xroot] > rank[yroot]:
            parent[yroot] = xroot
        else:
            parent[yroot] = xroot
            rank[xroot] += 1

    def kruskal_mst(self):
        result = []  # store MST edges
        i, e = 0, 0
        self.graph = sorted(self.graph, key=lambda item: item[2])
        parent = []
        rank = []

        for node in range(self.V):
            parent.append(node)
            rank.append(0)

        while e < self.V - 1 and i < len(self.graph):
            u, v, w = self.graph[i]
            i += 1
            x = self.find_parent(parent, u)
            y = self.find_parent(parent, v)

            if x != y:
                e += 1
                result.append((u, v, w))
                self.union(parent, rank, x, y)

        print("\nMinimum Spanning Tree using Kruskal's Algorithm:")
        total_cost = 0
        for u, v, w in result:
            print(f"Department {u} -- {v}  Distance: {w}")
            total_cost += w
        print("Total Minimum Distance:", total_cost)

    # ---------- PRIM'S ALGORITHM ----------
    def prim_mst(self):
        import heapq
        visited = [False] * self.V
        pq = [(0, 0)]  # (weight, vertex)
        total_cost = 0

        print("\nMinimum Spanning Tree using Prim's Algorithm:")
        while pq:
            w, u = heapq.heappop(pq)
            if visited[u]:
                continue
            visited[u] = True
            total_cost += w
            print(f"Included Department {u} with edge weight {w}")

            for v, wt in self.adj[u]:
                if not visited[v]:
                    heapq.heappush(pq, (wt, v))

        print("Total Minimum Distance:", total_cost)


# ---------- MAIN PROGRAM ----------
print("Enter number of departments (nodes): ")
V = int(input())
g = Graph(V)

E = int(input("Enter number of paths (edges): "))
print("Enter each path as: start_node end_node distance")

for _ in range(E):
    u, v, w = map(int, input().split())
    g.add_edge(u, v, w)

print("\n--- CAMPUS GRAPH REPRESENTATION ---")
for i in range(V):
    print(f"Department {i} -> {g.adj[i]}")

# a) Kruskal’s Algorithm
g.kruskal_mst()

# b) Prim’s Algorithm
g.prim_mst()
