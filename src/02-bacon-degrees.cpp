#include "header.hpp"

typedef pair<string, string> Neighbor;

void readCSV(const string& filename, Graph<string, Neighbor>& graph);
void BFS(const Graph<string, Neighbor>& graph, const string& start);

int main() {
    Graph<string, Neighbor> graph;

    readCSV("./tests/q2/input.txt", graph);

    BFS(graph, "Kevin Bacon");

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
        string leftName, movie, rightName;
        getline(iss, leftName, ';');
        getline(iss, movie, ';');
        getline(iss, rightName, ';');

        Neighbor neighbor1{rightName, movie};
        Neighbor neighbor2{leftName, movie};

        graph[leftName].push_back(neighbor1);
        graph[rightName].push_back(neighbor2);
    }

    file.close();
}

void BFS(const Graph<string, Neighbor>& graph, const string& start) {
    map<string, string> colors;
    map<string, int> distances;
    map<string, string> parents;
    map<string, string> movies;

    for (const auto& entry : graph) {
        const string& actor = entry.first;
        colors[actor] = "White";
        parents[actor] = "";
        distances[actor] = -1;
    }

    queue<string> q;
    q.push(start);
    colors[start] = "Grey";
    distances[start] = 0;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        for (const auto& neighbor : graph.at(current)) {
            const string& neighborName = neighbor.first;
            const string& movie = neighbor.second;

            if (colors[neighborName] == "White") {
                colors[neighborName] = "Grey";
                distances[neighborName] = distances[current] + 1;
                parents[neighborName] = current;
                movies[neighborName] = movie;
                q.push(neighborName);
            }
        }

        colors[current] = "Black";
    }

    for (const auto& entry : distances) {
        const string& actorName = entry.first;
        const string& movie = movies[actorName];
        cout << "O numero de Bacon de " << actorName << " é " << distances[actorName];
        cout << " pelo filme " << movie << endl;
    }
}

