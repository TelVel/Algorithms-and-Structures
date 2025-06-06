#ifndef GRAPH_RGR_SIMPLEGRAPH_H
#define GRAPH_RGR_SIMPLEGRAPH_H

#define LGraphType false
#define MGraphType true
#define DGraphType true
#define NonDGraphType false

#include <iostream>
#include "elements/Edge.h"
#include "elements/Vertex.h"
#include "forms/GraphForm.h"
#include "forms/LGraph.h"
#include "forms/MGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
class SimpleGraph {
public:
    using VertexT = Vertex<DATA, NAME>;
    using EdgeT = Edge<DATA, NAME, WEIGHT>;

    class EdgeIterator {
    public:
        using reference = EdgeIterator &;

        EdgeIterator(vector<EdgeT *> *edgeVector, int ind) : edgeVector(edgeVector), index(ind) {}

        Edge<DATA, NAME, WEIGHT> *operator*() const { return (*edgeVector)[index]; }

        friend bool operator==(const EdgeIterator &a, const EdgeIterator &b) { return a.index == b.index; }

        friend bool operator!=(const EdgeIterator &a, const EdgeIterator &b) { return a.index != b.index; }

        const reference &operator++() {
            index++;
            if (index == edgeVector->size()) index = -1;
            return *this;
        }

        const reference operator++(int) {
            index++;
            if (index == edgeVector->size()) index = -1;
            return *this;
        }

        int getSize() { return edgeVector->size(); }

        int getInd() { return index; }

    private:
        vector<EdgeT *> *edgeVector;
        int index;
    };

    class VertexIterator {
    public:
        using reference = VertexIterator &;

        VertexIterator(vector<VertexT *> &vertexVector, int ind) : vertexVector(vertexVector), index(ind) {}

        NAME operator*() const { return vertexVector[index]->getName(); }

        Vertex<DATA, NAME> *operator->() { return vertexVector[index]; }

        friend bool operator==(const VertexIterator &a, const VertexIterator &b) { return a.index == b.index; }

        friend bool operator!=(const VertexIterator &a, const VertexIterator &b) { return a.index != b.index; }

        const reference &operator++() {
            index++;
            if (index == vertexVector.size()) index = -1;
            return *this;
        }

        const reference operator++(int) {
            index++;
            if (index == vertexVector.size()) index = -1;
            return *this;
        }

    private:
        vector<VertexT *> vertexVector;
        int index;
    };

    SimpleGraph();

    SimpleGraph(int _VCnt, bool _D, bool _F);

    SimpleGraph(int _VCnt, int _ECnt, bool _D, bool _F);

    SimpleGraph(SimpleGraph &G);

    ~SimpleGraph();

    int getV();

    int getE();

    bool isDirected();

    bool isDense();

    int getK();

    void toListGraph();

    void toMatrixGraph();

    VertexT *insertV();

    VertexT *insertV(NAME name);

    bool deleteV(VertexT *v);

    EdgeT *insertE(VertexT *i, VertexT *j);

    EdgeT *insertE(VertexT *i, VertexT *j, int _w);

    bool deleteE(EdgeT *e);

    EdgeT *getEdge(VertexT *v1, VertexT *v2);

    EdgeT *getEdge(int v1, int v2);

    void printGraph();

    VertexIterator vBegin();

    VertexIterator vEnd();

    EdgeIterator eBegin();

    EdgeIterator eEnd();

    EdgeIterator adjEBegin(int v);

    EdgeIterator adjEEnd(int v);

    GraphForm<DATA, NAME, WEIGHT> *graphForm;

private:
    void switchForm(GraphForm<DATA, NAME, WEIGHT> *newForm);

    int VCnt;
    int ECnt;
    bool D;
    bool dense;
};

template
class SimpleGraph<int, string, int>;


#endif //GRAPH_RGR_SIMPLEGRAPH_H
