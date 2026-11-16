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

g = Grafo()
g.add_aresta("A","B",1)
g.add_aresta("A","C",1)
g.add_aresta("B","C",1)
g.add_aresta("C","E",1)
g.add_aresta("D","E",1)
g.add_aresta("F","E",1)
g.add_aresta("D","F",1)
g.add_aresta("D","B",1)