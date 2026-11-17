# Implementação de grafos em Python
from collections import deque
import heapq

class Grafo:
    def __init__(self):
        self.adj = {}

    def add_vertice(self, v):
        self.adj.setdefault(v, {})
    def add_aresta(self, u, v, w=1):
        self.add_vertice(u)
        self.add_vertice(v)
        self.adj[u][v] = w
        self.adj[v][u] = w
    def remove_aresta(self, u, v):
        del self.adj[u][v]
        del self.adj[v][u]
    def vizinhos(self, v):
        return self.adj[v].keys()
    def adjacentes(self, u, v):
        return u in self.adj[v]
    def grau(self, v):
        return len(self.adj[v])
    def vertices(self):
        return self.adj.keys()
    def remove_vertice(self, v):
        for verticeadj in self.adj[v]:
            self.adj[verticeadj][v]
        del self.adj[v]
    def arestas(self):
        vistos = set()
        for u in self.adj:
            for v, w in self.adj[u].items():
                if (v, u) not in vistos:
                    vistos.add((u, v))
                    yield (u, v, w)

def bfs(g,s): # busca em largura breadth-first
    dist = {s:0}
    pai = {s:None}
    fila = deque(s)
    while fila:
        u = fila.popleft()
        for v in sorted(g.vizinhos(u)):
            if v not in dist:
                dist[v] = dist[u]+1
                pai[v] = u
                fila.append(v)
    return dist,pai
    
def dijkstra(g, s):
    dist = { v: float("inf") for v in g.adj    }
    pai = {s: None}
    dist[s] = 0
    heap = [(0, s)]
    heapq.heapify(heap)
    while heap:
        du, u = heapq.heappop( heap )
        if du > dist[u]:
            continue
        for v, w in g.adj[u].items():
            if du + w < dist[v]:
                dist[v] = du + w
                pai[v] = u
                heapq.heappush(heap, (dist[v], v))
    return dist, pai



class UnionFind:
    def __init__(self, elementos):
        self.pai = {x: x for x in elementos}
        self.rank = {x: 0 for x in elementos}

    def find(self, x):
        if self.pai[x] != x:     # compressao
            self.pai[x] = self.find(self.pai[x])
        return self.pai[x]

    def union(self, x, y):
        rx, ry = self.find(x), self.find(y)
        if rx == ry:
            return False         # mesmo conjunto
        if self.rank[rx] < self.rank[ry]:
            rx, ry = ry, rx
        self.pai[ry] = rx        # uniao por rank
        if self.rank[rx] == self.rank[ry]:
            self.rank[rx] += 1
        return True


def kruskal(g):
    uf = UnionFind(g.vertices())
    agm = []
    n = len(g.vertices())
    for u, v, w in sorted(g.arestas(), key=lambda a: a[2]):
        if uf.union(u, v):
            agm.append((u, v, w))
            if len(agm) == n - 1:
                break
    return agm

g = Grafo()
g.add_aresta("A","B",4)
g.add_aresta("A","C",2)
g.add_aresta("B","C",1)
g.add_aresta("C","E",10)
g.add_aresta("D","E",2)
g.add_aresta("F","E",3)
g.add_aresta("D","F",6)
g.add_aresta("D","B",5)