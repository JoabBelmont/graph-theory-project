#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>

using namespace std;

typedef vector<list<pair<string, string>>> Graph;

void buildGraph(const string& filename, Graph& graph);
int getBaconNumber(const Graph& graph, const string& actor);
string getMovieWithBacon(const Graph& graph, const string& actor);
void DFS(const Graph& graph, const string& actor, unordered_map<string, bool>& visited, int& baconNumber);
void printBaconNumbers(const Graph& graph);

int main() {
    Graph graph;
    buildGraph("./tests/q2/input.txt", graph);

    printBaconNumbers(graph);

    return 0;
}

void buildGraph(const string& filename, Graph& graph) {
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

        size_t pos1 = line.find(';');
        string actor1 = line.substr(0, pos1);

        size_t pos2 = line.find(';', pos1 + 1);
        string movie = line.substr(pos1 + 1, pos2 - pos1 - 1);

        string actor2 = line.substr(pos2 + 1);

        graph.push_back({{ actor1, movie }, { actor2, movie }});
    }

    file.close();
}

int getBaconNumber(const Graph& graph, const string& actor) {
    unordered_map<string, bool> visited;
    int baconNumber = 0;

    DFS(graph, actor, visited, baconNumber);

    return baconNumber;
}

string getMovieWithBacon(const Graph& graph, const string& actor) {
    for (const auto& pair : graph) {
        for (const auto& actorMoviePair : pair) {
            if (actorMoviePair.first == actor && actorMoviePair.second == "Kevin Bacon") {
                return actorMoviePair.second;
            }
        }
    }

    return "";
}

void DFS(const Graph& graph, const string& actor, unordered_map<string, bool>& visited, int& baconNumber) {
    visited[actor] = true;

    for (const auto& pair : graph) {
        for (const auto& actorMoviePair : pair) {
            if (actorMoviePair.first == actor) {
                if (actorMoviePair.second == "Kevin Bacon") {
                    baconNumber = 1;
                    return;
                }

                if (!visited[actorMoviePair.second]) {
                    DFS(graph, actorMoviePair.second, visited, baconNumber);
                    if (baconNumber != 0) {
                        baconNumber++;
                        return;
                    }
                }
            }
        }
    }
}

void printBaconNumbers(const Graph& graph) {
    vector<string> actors;
    for (const auto& pair : graph) {
        for (const auto& actorMoviePair : pair) {
            actors.push_back(actorMoviePair.first);
        }
    }
    sort(actors.begin(), actors.end());

    for (const auto& actor : actors) {
        int baconNumber = getBaconNumber(graph, actor);
        if (baconNumber != 0) {
            string movie = getMovieWithBacon(graph, actor);
            cout << "O numero de Bacon de " << actor << " é " << baconNumber << " pelo filme " << movie << endl;
        }
    }
}
