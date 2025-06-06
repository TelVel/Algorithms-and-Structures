#ifndef ASD_RGR_LGRAPH_H
#define ASD_RGR_LGRAPH_H

#include "../SimpleGraph.h"
#include "GraphForm.h"

template<typename DATA, typename NAME, typename WEIGHT>
class LGraph : public GraphForm<DATA, NAME, WEIGHT> {
public:
    using VertexT = Vertex<DATA, NAME>;
    using EdgeT = Edge<DATA, NAME, WEIGHT>;

    LGraph(unsigned _size, bool directed);

    LGraph(LGraph &G);

    ~LGraph();

    bool hasEdge(int i, int j);

    EdgeT *insertE(VertexT *v1, VertexT *v2);

    EdgeT *insertE(VertexT *v1, VertexT *v2, int _w);

    bool deleteE(EdgeT *e);

    EdgeT *getEdge(int v1, int v2);

    EdgeT *getEdge(VertexT *v1, VertexT *v2);

    void print();

    bool deleteV(int v);

    void insertV(int v);

    void setDirected(bool d);

    vector<VertexT *> &getVertexVector();

    vector<VertexT *> vertexVector;

    vector<EdgeT *> *getEdgeVector();

    vector<EdgeT *> *getEdgeVector(int v);

private:
    class ENode {
    public:

        ENode(Edge<DATA, NAME, WEIGHT> *_e, ENode *_next) {
            e = _e;
            next = _next;
        }

        Edge<DATA, NAME, WEIGHT> *e;
        ENode *next;
    };

    class VNode {
    public:
        VNode(int ind, ENode *_eNode, VNode *_next) {
            v_ind = ind;
            eNode = _eNode;
            next = _next;
        }

        int v_ind;
        ENode *eNode;
        VNode *next;
    };

    Edge<DATA, NAME, WEIGHT> *insert(VertexT *v1, VertexT *v2);
    Edge<DATA, NAME, WEIGHT> *insert(VertexT *v1, VertexT *v2, int _w);
    vector<EdgeT *> *edgeVector;
    VNode *list;
    unsigned size;
    bool directed;
};


#endif //ASD_RGR_LGRAPH_H
