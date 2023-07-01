#include "header.hpp"

// Kosaraju's algorithm

void printGraph(Graph<int, int>& graph);
void Kosaraju(Graph<int, int>& graph);
void DFSVisit(Graph<int, int>& graph, int u, vector<string>& colors, stack<int>& stack);
void DFSVisit(Graph<int, int>& graph, int u, vector<string>& colors, vector<int>& component);

void transposeGraph(Graph<int, int>& graph);

void readGraph(const string& filename, Graph<int, int>& graph);

int main() {
    Graph<int, int> graph;
    readGraph("./tests/q3/grafo3.txt", graph);

    // printGraph(graph);

    Kosaraju(graph);

    return 0;
}

void Kosaraju(Graph<int, int>& graph) {
    vector<string> colors (graph.size(), "White");
    stack<int> stack;
    vector<int> component, componentCopy;
    vector<vector<int>> SCCs;

    for (const auto& entry : graph) {
        int u = entry.first;

        if (colors[u] == "White") {
            DFSVisit(graph, u, colors, stack);
        }
    }

    transposeGraph(graph);

    for (auto& color : colors) {
        color = "White";
    }

    while (!stack.empty()) {
        int u = stack.top();
        stack.pop();

        if (colors[u] == "White") {
            DFSVisit(graph, u, colors, component);
            componentCopy = component;
            component.clear();
            SCCs.push_back(componentCopy);
        }
    }

    for (const auto& SCC : SCCs) {
        for (int u : SCC) {
            cout << u << " ";
        }
        cout << endl;
    }
}

void DFSVisit(Graph<int, int>& graph, int u, vector<string>& colors, stack<int>& stack) {
    colors[u] = "Gray";

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            DFSVisit(graph, v, colors, stack);
        }
    }

    colors[u] = "Black";
    stack.push(u);
}

void DFSVisit(Graph<int, int>& graph, int u, vector<string>& colors, vector<int>& component) {
    colors[u] = "Gray";
    component.push_back(u);

    for (int v : graph.at(u)) {
        if (colors[v] == "White") {
            DFSVisit(graph, v, colors, component);
        }
    }

    colors[u] = "Black";
}

void transposeGraph(Graph<int, int>& graph) {
    Graph<int, int> flippedGraph;

    for (const auto& entry : graph) {
        int u = entry.first;
        for (int v : entry.second) {
            flippedGraph[v].push_back(u);
        }
    }

    graph = move(flippedGraph);
}


void readGraph(const string& filename, Graph<int, int>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    int edgesNum, verticesNum;
    file >> verticesNum >> edgesNum;

    for (int i = 0; i < edgesNum; ++i) {
        int u, v;
        file >> u >> v;
        graph[u].push_back(v);
        graph[v] = {};
    }

    file.close();
}


void printGraph(Graph<int, int>& graph) {
    for (const auto& entry : graph) {
        int u = entry.first;
        cout << u << ": ";
        for (int v : entry.second) {
            cout << v << " ";
        }
        cout << endl;
    }
}
