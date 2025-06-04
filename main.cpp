#include <iostream>
#include <vector>
#include <set>
#include "graph_utils.h"
using namespace std;

int main() {
    readGraph("graph.csv");

    string start, end;

    cout << "Select start: "; cin>> start;
    cout<<"Select end: "; cin>> end;

    cout << "All paths from " << start << " to " << end << " using DFS:\n";
    set<string> visited;
    vector<string> path;
    vector<vector<string>> allPaths;
    dfsAllPaths(start, end, visited, path, allPaths);

    for (auto& p : allPaths) {
        for (auto& node : p)
            cout << node << " ";
        cout << endl;
    }

    auto [cost, shortestPath] = dijkstra(start, end);
    cout << "\nShortest path using Dijkstra from " << start << " to " << end << " (cost = " << cost << "):\n";
    for (auto& node : shortestPath)
        cout << node << " ";
    cout << endl;

    return 0;
}