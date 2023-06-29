#include "header.hpp"

typedef pair<string, string> Neighbor;

void readCSV(const string& filename, Graph<string, Neighbor>& graph);
void printGraph(const Graph<string, Neighbor>& graph);
void BFS(const Graph<string, Neighbor>& graph, const string& start);

int main() {
    Graph<string, Neighbor> graph;

    readCSV("./tests/q2/input.txt", graph);

    // BFS(graph, "Kevin Bacon");
    printGraph(graph);

    return 0;
}

void readCSV(const string& filename, Graph<string, Neighbor>& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string name1, movie, name2;
        getline(iss, name1, ';');
        getline(iss, movie, ';');
        getline(iss, name2, ';');

        graph[name2].push_back({name1, movie});
        graph[name1].push_back({name2, movie});
    }

    file.close();
}

void printGraph(const Graph<string, Neighbor>& graph) {
    for (const auto& entry : graph) {
        const string& actor = entry.first;
        const list<pair<string, string>>& neighbors = entry.second;

        cout << actor << " -> ";
        auto it = neighbors.begin();
        auto last = neighbors.end();
        --last;  // Move last iterator to the last neighbor

        for (; it != last; ++it) {
            cout << it->first << " -> ";
        }

        // Print the last neighbor without the arrow
        cout << last->first << endl;
    }
}


void BFS(const Graph<string, Neighbor>& graph, const string& start) {
    // TODO: Implement breadth-first search algorithm
    map<string, bool> visited;
    map<string, int> distances;
    map<string, string> parents;

    for (const auto& entry : graph) {
        const string& actor = entry.first;
        visited[actor] = false;
        distances[actor] = -1;
        parents[actor] = "";
    }

    queue<string> q;
    q.push(start);
    visited[start] = true;
    distances[start] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        // Process the current vertex
        // You can perform any required operations here

        // Traverse the neighbors of the current vertex
        for (const auto& neighbor : graph.at(current)) {
            const string& neighborName = neighbor.first;

            if (!visited[neighborName]) {
                visited[neighborName] = true;
                distances[neighborName] = distances[current] + 1;
                parents[neighborName] = current;
                q.push(neighborName);
            }
        }
    }

    // Print the distances and parent actors
    for (const auto& entry : distances) {
        const string& actorName = entry.first;
        cout << "O número de Bacon de " << actorName << " é " << distances[actorName];
        cout << " pelo filme " << graph.at(actorName).front().second << endl;
    }
}
