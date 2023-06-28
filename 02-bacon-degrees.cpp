#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <tuple>
#include <unordered_map>

using namespace std;

typedef vector<list<string>> Graph;
typedef tuple<string, string, int> Actor;

void bubbleSort(vector<Actor>& actors, Graph& graph);
void readCSV(const string& filename, vector<Actor>& actors, Graph& graph);
void printGraph(const Graph& graph);
void BSF(const Graph& graph, vector<Actor>& actors, int start);

int main() {
    vector<Actor> actors;
    Graph graph;

    readCSV("./tests/q2/input.txt", actors, graph);

    actors.push_back({"Kevin Bacon", "", 0});

    cout << "Got here" << endl;
    // bubbleSort(actors, graph);

    cout << "Actors: " << endl;
    for (const auto& actor : actors) {
        cout << get<0>(actor) << endl;
    }
    cout << endl;

    cout << "Movies: " << endl;
    for (const auto& actor : actors) {
        cout << get<1>(actor) << endl;
    }
    cout << endl;

    cout << "Graph:" << endl;
    printGraph(graph);

    return 0;
}

void bubbleSort(vector<Actor>& actors, Graph& graph) {
    for (int i = 0; i < actors.size() - 1; ++i) {
        for (int j = 0; j < actors.size() - i - 1; ++j) {
            if (get<0>(actors[j]) > get<0>(actors[j + 1])) {
                swap(actors[j], actors[j + 1]);
                swap(graph[j], graph[j + 1]);
            }
        }
    }
}

void readCSV(const string& filename, vector<Actor>& actors, Graph& graph) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file." << endl;
        exit(1);
    }

    unordered_map<string, list<string>> adjacencyMap;

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string name1, movie, name2;
        Actor actor;
        getline(iss, name1, ';');
        getline(iss, movie, ';');
        getline(iss, name2, ';');

        actor = {name1, movie, 0};
        actors.push_back(actor);

        adjacencyMap[name2].push_back(name1);
    }

    file.close();

    // Convert the adjacencyMap to the graph
    for (const auto& entry : adjacencyMap) {
        const string& name = entry.first;
        const list<string>& neighbors = entry.second;

        graph.push_back({name});
        graph.back().insert(graph.back().end(), neighbors.begin(), neighbors.end());
    }
}

void printGraph(const Graph& graph) {
    for (const auto& adjacencyList : graph) {
        for (const auto& actor : adjacencyList) {
            cout << actor << " -> ";
        }
        cout << endl;
    }
}

void BSF(const Graph& graph, vector<Actor>& actors) {
}