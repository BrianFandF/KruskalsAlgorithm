#include <iostream>
#include <vector>
#include <algorithm>
#include<Windows.h>
using namespace std;

struct Edge {
    int source, destination, weight;
};

class Graph {
public:
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) : V(v), E(e) {}

    void addEdge(int source, int destination, int weight) {
        Edge edge = { source, destination, weight };
        edges.push_back(edge);
    }

    void kruskalMST() {
        vector<Edge> result;
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
            });

        vector<int> parent(V, -1);

        int edgeCount = 0;
        for (int i = 0; edgeCount < V - 1 && i < E; i++) {
            int source = edges[i].source;
            int destination = edges[i].destination;

            int sourceParent = find(parent, source);
            int destParent = find(parent, destination);

            if (sourceParent != destParent) {
                result.push_back(edges[i]);
                unionSets(parent, sourceParent, destParent);
                edgeCount++;
            }
        }

        cout << "Остовне дерево мінімальної ваги:" << endl;
        for (const Edge& edge : result) {
            cout << edge.source + 1 << " - " << edge.destination + 1 << " : " << edge.weight << endl;
        }

        int sum = 0;
        for (const Edge& edge : result) {
            sum += edge.weight;
        }

        cout << "Вага мінімального остовного дерева: " << sum << endl;
    }

private:
    int find(vector<int>& parent, int vertex) {
        if (parent[vertex] == -1) {
            return vertex;
        }
        return find(parent, parent[vertex]);
    }

    void unionSets(vector<int>& parent, int x, int y) {
        int xSet = find(parent, x);
        int ySet = find(parent, y);
        parent[xSet] = ySet;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int V = 14; // Кількість вершин графа
    int E = 39; // Кількість ребер графа

    Graph graph(V, E);

    // Вхідні дані: Матриця суміжності
    int adjacencyMatrix[14][14] = {
        {0, 5, 3, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 8, 0, 0, 0, 0, 0, 0, 0},
        {0, 5, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 9, 8, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 3, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 8, 0, 1, 2, 0, 4, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 4, 9, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (adjacencyMatrix[i][j] != 0) {
                graph.addEdge(i, j, adjacencyMatrix[i][j]);
            }
        }
    }

    graph.kruskalMST();

    return 0;
}