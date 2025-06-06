#ifndef GRAPH_TASK_H
#define GRAPH_TASK_H

#include "SimpleGraph.h"
#include <vector>
#include <stack>

template<typename DATA, typename NAME>
class CycleFinder {
private:
    SimpleGraph<DATA, NAME, int>* graph;
    int targetLength;
    int startVertex;
    std::vector<std::vector<int>> cycles;
    std::vector<bool> visited; // Используем vector вместо массива

    void dfs(int current, std::vector<int>& path) {
        path.push_back(current);
        visited[current] = true;

        if (path.size() == targetLength) {
            if (graph->getEdge(current, startVertex) != nullptr) {
                cycles.push_back(path);
                cycles.back().push_back(startVertex);
            }
            visited[current] = false;
            path.pop_back();
            return;
        }

        for (auto it = graph->adjEBegin(current); it != graph->adjEEnd(current); ++it) {
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
        : graph(g), targetLength(length), startVertex(start) {
        if (graph) {
            visited.resize(graph->getV(), false);
            std::vector<int> path;
            dfs(startVertex, path);
        }
    }

    // Конструктор копирования
    CycleFinder(const CycleFinder& other) {
        graph = other.graph;
        targetLength = other.targetLength;
        startVertex = other.startVertex;
        cycles = other.cycles;
        if (graph) solve();
    }

    // Деструктор
    ~CycleFinder() = default;

    void restart() {
        solve();
    }
    
    void set(SimpleGraph<DATA, NAME, int>* g) {
        graph = g;
        restart();
    }

    std::vector<std::vector<int>> result() const {
        return cycles;
    }

private:
    void solve() {
        visited.assign(graph->getV(), false); // Очищаем и ресайзим
        cycles.clear();
        if (graph) {
            std::vector<int> path;
            dfs(startVertex, path);
        }
    }
};

#endif // GRAPH_TASK_H