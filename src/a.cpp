#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void fillOrder(int v, const vector<vector<int>>& adjList, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;

    for (int u : adjList[v]) {
        if (!visited[u]) {
            fillOrder(u, adjList, visited, Stack);
        }
    }

    Stack.push(v);
}

vector<vector<int>> getTranspose(const vector<vector<int>>& adjList) {
    int V = adjList.size();
    vector<vector<int>> transposedAdjList(V);

    for (int v = 0; v < V; ++v) {
        for (int u : adjList[v]) {
            transposedAdjList[u].push_back(v);
        }
    }

    return transposedAdjList;
}

void DFSUtil(int v, const vector<vector<int>>& adjList, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);

    for (int u : adjList[v]) {
        if (!visited[u]) {
            DFSUtil(u, adjList, visited, component);
        }
    }
}

void printSCCs(const vector<vector<int>>& adjList) {
    int V = adjList.size();
    vector<bool> visited(V, false);
    stack<int> Stack;

    for (int v = 0; v < V; ++v) {
        if (!visited[v]) {
            fillOrder(v, adjList, visited, Stack);
        }
    }

    vector<vector<int>> transposedAdjList = getTranspose(adjList);
    fill(visited.begin(), visited.end(), false);

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            vector<int> component;
            DFSUtil(v, transposedAdjList, visited, component);

            // Print the strongly connected component
            for (int u : component) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    vector<vector<int>> adjList = {
        {1, 0},
        {0, 2},
        {2, 1},
        {0, 3},
        {3, 4},
    };

    cout << "Following are strongly connected components in the given graph:\n";
    printSCCs(adjList);

    return 0;
}
