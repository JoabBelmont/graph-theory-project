#include "header.hpp"

using Graph = map<int, list<int>>;

bool isBipartite(const Graph& graph, vector<char>& colors);
void addEdge(Graph& graph, int u, int v);
bool readGraphs(const string& filename, vector<Graph>& graphs, vector<int>& numVertices);

int main() {
    vector<Graph> graphs;
    vector<int> numVertices;
    int numGraphs = 0;

    if (!readGraphs("./tests/q1/SIM/cubic_bipartite_26_vertices.txt", graphs, numVertices)) {
        cout << "Failed to open file." << endl;
        return 1;
    }

    for (size_t i = 0; i < graphs.size(); ++i) {
        const Graph& graph = graphs[i];
        int vertices = numVertices[i];

        vector<char> colors(vertices, 'w');
        colors[0] = 'r';

        cout << "Graph " << i + 1 << ": ";
        cout << (isBipartite(graph, colors) ? "SIM" : "NAO") << endl;
    }

    return 0;
}

bool isBipartite(const Graph& graph, vector<char>& colors) {
    int numVertices = colors.size();

    for (int i = 0; i < numVertices; ++i) {
        if (colors[i] == 'w') {
            colors[i] = 'r';
        }

        for (int neighbor : graph.at(i)) {
            if (colors[neighbor] == 'w') {
                colors[neighbor] = (colors[i] == 'r') ? 'b' : 'r';
            } else {
                if (colors[neighbor] == colors[i]) {
                    return false;
                }
            }
        }
    }

    return true;
}

void addEdge(Graph& graph, int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool readGraphs(const string& filename, vector<Graph>& graphs, vector<int>& numVertices) {
    cout << "Reading graphs from file: " << filename << endl;

    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    int vertices, edges;
    while (file >> vertices >> edges) {
        Graph graph;
        for (int i = 0; i < edges; ++i) {
            int u, v;
            file >> u >> v;
            addEdge(graph, u, v);
        }

        graphs.push_back(graph);
        numVertices.push_back(vertices);
    }

    file.close();

    return true;
}
