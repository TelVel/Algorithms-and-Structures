#ifndef GRAPH_TASK_H
#define GRAPH_TASK_H

#include "SimpleGraph.h"
#include <vector>
#include <stack>

template<typename DATA, typename NAME>
class CycleFinder {
private:
    SimpleGraph<DATA, NAME, int>* Graph;
    int targetLength;
    int startVertex;
    std::vector<std::vector<int>> cycles;
    std::vector<bool> visited;

    void dfs(int current, std::vector<int>& path) {
        path.push_back(current);
        visited[current] = true;

        if (path.size() == targetLength) {
            if (Graph->getEdge(current, startVertex) != nullptr) {
                cycles.push_back(path);
                cycles.back().push_back(startVertex);
            }
            visited[current] = false;
            path.pop_back();
            return;
        }

        for (auto it = Graph->adjEBegin(current); it != Graph->adjEEnd(current); ++it) {
            int next = (*it)->getV2()->getInd();
            if (!visited[next]) {
                dfs(next, path);
            }
        }

        visited[current] = false;
        path.pop_back();
    }

public:
    CycleFinder(SimpleGraph<DATA, NAME, int>* g, int length, int start) 
        : Graph(g), targetLength(length), startVertex(start) {
        if (Graph) {
            visited.resize(Graph->getV(), false);
            std::vector<int> path;
            dfs(startVertex, path);
        }
    }

    CycleFinder(const CycleFinder& other) {
        Graph = other.Graph;
        targetLength = other.targetLength;
        startVertex = other.startVertex;
        cycles = other.cycles;
        if (Graph) solve();
    }

    ~CycleFinder() {
        cycles.clear();
        visited.clear();
    }

    void restart() {
        solve();
    }
    
    void set(SimpleGraph<DATA, NAME, int>* g) {
        Graph = g;
        restart();
    }

    std::vector<std::vector<int>> result() const {
        return cycles;
    }

private:
    void solve() {
        visited.assign(Graph->getV(), false);
        cycles.clear();
        if (Graph) {
            std::vector<int> path;
            dfs(startVertex, path);
        }
    }
};

#endif // GRAPH_TASK_H