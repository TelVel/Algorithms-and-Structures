#ifndef ASD_RGR_MGRAPH_H
#define ASD_RGR_MGRAPH_H

#include "../SimpleGraph.h"
#include "GraphForm.h"

template<typename DATA, typename NAME, typename WEIGHT>
class MGraph : public GraphForm<DATA, NAME, WEIGHT> {
public:
    using VertexT = Vertex<DATA, NAME>;
    using EdgeT = Edge<DATA, NAME, WEIGHT>;

    MGraph(unsigned _size, bool directed);

    MGraph(MGraph &G);

    ~MGraph();

    bool hasEdge(int i, int j);

    EdgeT *insertE(VertexT *v1, VertexT *v2);

    EdgeT *insertE(VertexT *v1, VertexT *v2, int _w);

    bool deleteE(EdgeT *e);

    EdgeT *getEdge(int v1, int v2);

    EdgeT *getEdge(VertexT *v1, VertexT *v2);

    void print();

    void setDirected(bool d);

    bool deleteV(int v);

    void insertV(int v);

    vector<VertexT *> &getVertexVector();

    vector<VertexT *> vertexVector;

    vector<EdgeT *> *getEdgeVector();

    vector<EdgeT *> *getEdgeVector(int v);

private:
    vector<vector<Edge<DATA, NAME, WEIGHT> *>> matrix;
    vector<EdgeT *> *edgeVector;
    unsigned size;
    bool directed;
};


#endif //ASD_RGR_MGRAPH_H
