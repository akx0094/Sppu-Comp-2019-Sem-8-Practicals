#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        // Start from the given node
        visited[start] = true;
        q.push(start);

        // Perform BFS
        while (!q.empty()) {
            int node = q.front();
            q.pop();

            cout << "Visited: " << node << endl;

            // Parallelizing the exploration of neighbors
            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    #pragma omp critical
                    {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }
};

int main() {
    // Create graph with 6 vertices
    Graph g(6);

    // Add edges
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);

    // Run BFS starting from node 0
    g.BFS(0);

    return 0;
}

