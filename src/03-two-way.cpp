#include "header.hpp"

// KosaRaju's algorithm

void DFS(const Graph<int, int>& graph);
void DFSVisit(const Graph<int, int>& graph, int u, map<int, string>& colors, map<int, int>& distances, map<int, int>& parents, stack<int>& s);

void flipAllEdges(Graph<int, int>& graph);

void readGraph(const string& filename, Graph<int, int>& graph);
void printGraph(const Graph<int, int>& graph);

int main() {
    Graph<int, int> graph;
    readGraph("./tests/q3/grafo3.txt", graph);
    flipAllEdges(graph);
    printGraph(graph);

    return 0;
}

void DFS(const Graph<int, int>& graph) {
    map<int, string> colors;
    map<int, int> distances;
    map<int, int> parents;
    stack<int> s;

    for (const auto& entry : graph) {
        int u = entry.first;
        colors[u] = "White";
        parents[u] = -1;
        distances[u] = -1;
    }

    for (const auto& entry : graph) {
        int u = entry.first;
        if (colors[u] == "White") {
            DFSVisit(graph, u, colors, distances, parents, s);
        }
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void DFSVisit(const Graph<int, int>& graph, int u, map<int, string>& colors, map<int, int>& distances, map<int, int>& parents, stack<int>& s) {
    colors[u] = "Gray";

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            parents[v] = u;
            distances[v] = distances[u] + 1;
            DFSVisit(graph, v, colors, distances, parents, s);
        }
    }

    colors[u] = "Black";
    s.push(u);
}

void flipAllEdges(Graph<int, int>& graph) {
    Graph<int, int> flippedGraph;

    for (const auto& entry : graph) {
        int u = entry.first;
        for (int v : entry.second) {
            flippedGraph[v].push_back(u);
        }
    }

    graph = flippedGraph;
}

void readGraph(const string& filename, Graph<int, int>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    int vertices, edges;
    file >> vertices >> edges;

    for (int i = 0; i < edges; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
    }

    file.close();
}

void printGraph(const Graph<int, int>& graph) {
    for (const auto& entry : graph) {
        cout << entry.first << ": ";
        for (int neighbor : entry.second) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}