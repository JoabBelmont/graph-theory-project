#include "header.hpp"

using Graph = vector<list<int>>;

void printEdges(Graph& graph);
void readGraph(const string& filename, Graph& graph);

void DFSVisit(Graph& graph, int u, vector<string>& colors, stack<int>& stack);
void DFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& component);
void transposeGraph(Graph& graph);
void Kosaraju(Graph& graph, vector<vector<int>>& SCCs);
void createTwoWays(Graph& graph, vector<int>& SCC);
bool checkComponent(int& vertex, vector<int>& component);

int main() {
    Graph graph;
    vector<vector<int>> SCCs;
    readGraph("./tests/q3/grafo2.txt", graph);

    printEdges(graph);

    Kosaraju(graph, SCCs);

    for (auto& SCC : SCCs) {
        for (int u : SCC)
            cout << u << " ";
        cout << endl;
    }

    for (auto& SCC : SCCs)
        createTwoWays(graph, SCC);

    transposeGraph(graph);

    // printEdges(graph);

    return 0;
}

void createTwoWays(Graph& graph, vector<int>& SCC) {
    for (int u : SCC) {
        for (int v : graph[u]) {
            if (!checkComponent(v, SCC))
                graph[v].push_back(u);
        }
    }
}

bool checkComponent(int& vertex, vector<int>& component) {
    for (int u : component)
        if (u == vertex)
            return true;

    return false;
}

void Kosaraju(Graph& graph, vector<vector<int>>& SCCs) {
    vector<string> colors;
    stack<int> stack;
    vector<int> component, componentCopy;

    size_t verticesNum = graph.size();
    colors.resize(verticesNum, "White");

    // First DFS traversal
    for (int u = 0; u < verticesNum; ++u)
        if (colors[u] == "White")
            DFSVisit(graph, u, colors, stack);

    // Transpose the graph
    transposeGraph(graph);

    // Reset colors map to all vertices set to "White"
    for (auto& color : colors)
        color = "White";

    // Second DFS traversal to find strongly connected components
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
}

void DFSVisit(Graph& graph, int u, vector<string>& colors, stack<int>& stack) {
    colors[u] = "Gray";

    for (int v : graph.at(u))
        if (colors[v] == "White")
            DFSVisit(graph, v, colors, stack);

    colors[u] = "Black";
    stack.push(u);
}

void DFSVisit(Graph& graph, int u, vector<string>& colors, vector<int>& component) {
    colors[u] = "Gray";
    component.push_back(u);

    for (int v : graph.at(u))
        if (colors[v] == "White")
            DFSVisit(graph, v, colors, component);

    colors[u] = "Black";
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
