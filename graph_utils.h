#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
#include <limits>
using namespace std;

unordered_map<string, vector<pair<string, int>>> graph;

void readGraph(const string& filename) {
    ifstream file(filename);
    string line;

    // Bỏ qua dòng tiêu đề
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);
        string u, v, w_str;
        getline(ss, u, ',');
        getline(ss, v, ',');
        getline(ss, w_str, ',');
        int w = stoi(w_str);
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // Nếu là undirected graph
    }
}

void dfsAllPaths(string u, string dest, set<string>& visited, vector<string>& path, vector<vector<string>>& allPaths) {
    visited.insert(u);
    path.push_back(u);
    if (u == dest) {
        allPaths.push_back(path);
    } else {
        for (auto& [v, w] : graph[u]) {
            if (visited.find(v) == visited.end()) {
                dfsAllPaths(v, dest, visited, path, allPaths);
            }
        }
    }
    path.pop_back();
    visited.erase(u);
}

pair<int, vector<string>> dijkstra(string start, string end) {
    unordered_map<string, int> dist;
    unordered_map<string, string> prev;
    for (auto& node : graph) {
        dist[node.first] = numeric_limits<int>::max();
    }
    dist[start] = 0;

    using pii = pair<int, string>;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (u == end) break;
        for (auto& [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    vector<string> path;
    string cur = end;
    while (cur != start && prev.find(cur) != prev.end()) {
        path.push_back(cur);
        cur = prev[cur];
    }
    if (cur == start) {
        path.push_back(start);
        reverse(path.begin(), path.end());
    } else {
        path.clear(); // no path found
    }
    return {dist[end], path};
}