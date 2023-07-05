#include "header.hpp"

using Graph = vector<list<int>>;

void printEdges(Graph& graph);
void readGraph(const string& filename, Graph& graph);

void DFSVisit(Graph& graph, int u, vector<string>& colors, 
              vector<int>& parents, vector<int>& discoveryTimes, 
              vector<int>& lowTimes, int& time, vector<pair<int, int>>& bridges);
void transposeGraph(Graph& graph);
void DFS(Graph& graph, vector<pair<int, int>>& bridges);

int main() {
    Graph graph;
    vector<pair<int, int>> bridges;
    readGraph("./tests/q3/grafo3.txt", graph);

    DFS(graph, bridges);

    for (auto [u, v] : bridges) {
        cout << u << " " << v << endl;
    }

    // printEdges(graph);

    return 0;
}

void DFS(Graph& graph, vector<pair<int, int>>& bridges) {
    int time { 0 };
    size_t verticesNum = graph.size();
    vector<string> colors;
    vector<int> discoveryTimes(verticesNum), 
    lowTimes(verticesNum), 
    parents(verticesNum);

    colors.resize(verticesNum, "White");

    parents[0] = 0;
    // First DFS traversal
    for (int u = 0; u < verticesNum; ++u)
        if (colors[u] == "White")
            DFSVisit(graph, u, colors, parents, discoveryTimes, lowTimes, time, bridges);
}

void DFSVisit(Graph& graph, int u, vector<string>& colors, 
              vector<int>& parents, vector<int>& discoveryTimes, 
              vector<int>& lowTimes, int& time, vector<pair<int, int>>& bridges) {
    colors[u] = "Gray";
    time += 1;
    lowTimes[u] = discoveryTimes[u] = time;

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            parents[v] = u;
            DFSVisit(graph, v, colors, parents, discoveryTimes, lowTimes, time, bridges);
            if (lowTimes[v] < lowTimes[u])
                lowTimes[u] = lowTimes[v];
            if (discoveryTimes[u] < lowTimes[v]) {
                bridges.push_back({u, v});
            }
        }
    }

    colors[u] = "Black";

    for (int v : graph.at(u)) {
        if (v != parents[u]) {
            lowTimes[u] = min(lowTimes[u], lowTimes[v]);
        }
    }
}

void transposeGraph(Graph& graph) {
    size_t verticesNum = graph.size();
    Graph transposedGraph(verticesNum);

    for (int u = 0; u < verticesNum; ++u) {
        for (int v : graph[u]) {
            transposedGraph[v].push_back(u);
        }
    }

    graph = move(transposedGraph);
}


void readGraph(const string& filename, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    int edgesNum, verticesNum;
    file >> verticesNum >> edgesNum;

    graph.resize(verticesNum);

    for (int i = 0; i < edgesNum; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    file.close();
}

void printEdges(Graph& graph) {
    for (int u = 0; u < graph.size(); ++u) {
        for (int v : graph[u])
            cout << "(" << u << "," << v << ")" << endl;
    }
    cout << "#" << endl;
}
