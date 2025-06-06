#ifndef ASD_RGR_SIMPLEGRAPH_H
#define ASD_RGR_SIMPLEGRAPH_H

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
#include "iterators/EdgeIterator.h"
#include "iterators/VertexIterator.h"

template<typename DATA, typename NAME, typename WEIGHT>
class SimpleGraph {
public:
    using VertexT = Vertex<DATA, NAME>;
    using EdgeT = Edge<DATA, NAME, WEIGHT>;

    SimpleGraph();

    SimpleGraph(int VCount, bool D, bool F);

    SimpleGraph(int VCount, int ECount, bool D, bool F);

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

    VertexIterator<DATA, NAME, WEIGHT> vBegin();

    VertexIterator<DATA, NAME, WEIGHT> vEnd();

    EdgeIterator<DATA, NAME, WEIGHT> eBegin();

    EdgeIterator<DATA, NAME, WEIGHT> eEnd();

    EdgeIterator<DATA, NAME, WEIGHT> adjEBegin(int v);

    EdgeIterator<DATA, NAME, WEIGHT> adjEEnd(int v);

    GraphForm<DATA, NAME, WEIGHT> *graphForm;

private:
    void switchForm(GraphForm<DATA, NAME, WEIGHT> *newForm);

    int VCount;
    int ECount;
    bool D;
    bool dense;
};

template
class SimpleGraph<int, string, int>;


#endif //ASD_RGR_SIMPLEGRAPH_H
