#include<bits/stdc++.h>

using namespace std;

// Define a structure for edges
struct Edge {
    int to;
    int cost;
};

// Priority queue element: (total cost, current node, path so far)
struct NodeState {
    int cost;
    int node;
    vector<int> path;

    // Custom comparator for min-heap
    bool operator>(const NodeState& other) const {
        return cost > other.cost;
    }
};

// Uniform Cost Search function
vector<int> uniformCostSearch(int start, int goal, unordered_map<int, vector<Edge>>& graph) {
    // Min-heap priority queue
    priority_queue<NodeState, vector<NodeState>, greater<NodeState>> pq;
    unordered_map<int, int> visited;

    pq.push({0, start, {start}});

    while (!pq.empty()) {
        NodeState current = pq.top();
        pq.pop();

        int node = current.node;
        int cost = current.cost;

        // Skip if already visited with lower cost
        if (visited.find(node) != visited.end() && visited[node] <= cost)
            continue;

        visited[node] = cost;

        // Goal reached
        if (node == goal) {
            cout << "Total cost: " << cost << endl;
            return current.path;
        }

        // Explore neighbors
        for (Edge& edge : graph[node]) {
            if (visited.find(edge.to) == visited.end() || cost + edge.cost < visited[edge.to]) {
                vector<int> newPath = current.path;
                newPath.push_back(edge.to);
                pq.push({cost + edge.cost, edge.to, newPath});
            }
        }
    }

    // No path found
    return {};
}

// Helper to add undirected edge
void addEdge(unordered_map<int, vector<Edge>>& graph, int u, int v, int cost) {
    graph[u].push_back({v, cost});
    graph[v].push_back({u, cost});
}

// Example usage
int main() {
    unordered_map<int, vector<Edge>> graph;

    // Example graph
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 3);

    int start = 0, goal = 4;

    vector<int> path = uniformCostSearch(start, goal, graph);

    if (!path.empty()) {
        cout << "Path: ";
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }

    return 0;
}
