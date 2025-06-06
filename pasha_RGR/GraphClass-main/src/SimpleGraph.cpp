#include "SimpleGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph() {
    VCnt = 0;
    ECnt = 0;
    D = false;
    dense = false;
    graphForm = new LGraph<DATA, NAME, WEIGHT>(VCnt, D);
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCnt, bool _D, bool _F) {
    VCnt = _VCnt;
    ECnt = 0;
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCnt, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCnt, D);

    for (int i = 0; i < VCnt; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCnt, int _ECnt, bool _D, bool _F) {
    VCnt = _VCnt;
    ECnt = 0;
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCnt, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCnt, D);

    for (int i = 0; i < VCnt; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
    
    if (_ECnt <= 0) return;

    int maxEdges;
    if (D) {
        maxEdges = VCnt * (VCnt - 1);
    } else {
        maxEdges = (VCnt * (VCnt - 1)) / 2;
    }

    int targetEdges = min(_ECnt, maxEdges);
    srand(time(0));
    while (ECnt < targetEdges) {
        int v1 = rand() % VCnt;
        int v2 = rand() % VCnt;
        if (v1 == v2) continue;
        if (graphForm->hasEdge(v1, v2)) continue;
        EdgeT* edge = graphForm->insertE(graphForm->getVertexVector()[v1], graphForm->getVertexVector()[v2]);
        if (edge) {
            ECnt++;
        }
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(SimpleGraph &G) {
    VCnt = G.VCnt;
    ECnt = G.ECnt;
    D = G.D;
    dense = G.dense;
    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(
                reinterpret_cast<LGraph<int, basic_string<char>, int> &>(G.graphForm));
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(
                reinterpret_cast<MGraph<int, basic_string<char>, int> &>(G.graphForm));
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::~SimpleGraph() {
    delete graphForm;
}


template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::deleteV(VertexT *v) {
    int edgesDeleted = 0;
    EdgeT* edge;
    
    if (D) {
        for (int i = 0; i < VCnt; ++i) {
            edge = graphForm->getEdge(graphForm->getVertexVector()[i], v);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
            }
        }
        
        for (int i = 0; i < VCnt; ++i) {
            edge = graphForm->getEdge(v, graphForm->getVertexVector()[i]);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
            }
        }
    } else {
        for (int i = 0; i < VCnt; ++i) {
            edge = graphForm->getEdge(v, graphForm->getVertexVector()[i]);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
            }
        }
    }

    ECnt -= edgesDeleted;

    for (int i = 0; i < VCnt; ++i) {
        if (graphForm->getVertexVector()[i]->getInd() == v->getInd()) {
            delete graphForm->getVertexVector()[i];
            for (int j = i; j < VCnt - 1; ++j) {
                graphForm->getVertexVector()[j] = graphForm->getVertexVector()[j + 1];
            }
            graphForm->deleteV(v->getInd());
            VCnt--;
            graphForm->getVertexVector().resize(VCnt);
            return true;
        }
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV() {
    auto *v = new Vertex<DATA, NAME>;
    VCnt++;
    v->setInd(VCnt - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCnt - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV(NAME name) {
    auto *v = new Vertex<DATA, NAME>;
    VCnt++;
    v->setName(name);
    v->setInd(VCnt - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCnt - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::switchForm(GraphForm<DATA, NAME, WEIGHT> *newForm) {
    vector<VertexT*>& oldVertices = graphForm->getVertexVector();
    for (size_t i = 0; i < oldVertices.size(); ++i) {
        VertexT* oldVertex = oldVertices[i];
        VertexT* newVertex = new VertexT();
        newVertex->setInd(oldVertex->getInd());
        newVertex->setName(oldVertex->getName());
        newVertex->setData(oldVertex->getData());
        newForm->getVertexVector().push_back(newVertex);
        newForm->insertV(newVertex->getInd());
    }

    ECnt = 0;
    vector<Edge<DATA, NAME, WEIGHT>*>* oldEdges = graphForm->getEdgeVector();
    if (oldEdges) {
        for (EdgeT* oldEdge : *oldEdges) {
            if (!oldEdge || !oldEdge->getV1() || !oldEdge->getV2()) continue;
            int v1Idx = oldEdge->getV1()->getInd();
            int v2Idx = oldEdge->getV2()->getInd();
            if (v1Idx < 0 || v2Idx < 0 || 
                v1Idx >= newForm->getVertexVector().size() || 
                v2Idx >= newForm->getVertexVector().size()) {
                continue;
            }

            VertexT* newV1 = newForm->getVertexVector()[v1Idx];
            VertexT* newV2 = newForm->getVertexVector()[v2Idx];
            
            if (!newV1 || !newV2) continue;

            EdgeT* newEdge = newForm->insertE(newV1, newV2, oldEdge->getW());
            if (newEdge) {
                newEdge->setData(oldEdge->getData());
                ECnt++;
            }
        }
        delete oldEdges;
    }

    newForm->setDirected(D);
    
    delete graphForm;
    graphForm = newForm;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toMatrixGraph() {
    if (dense == MGraphType) return;
    auto newForm = new MGraph<DATA, NAME, WEIGHT>(VCnt, D);
    switchForm(newForm);
    dense = MGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toListGraph() {
    if (dense == LGraphType)return;
    auto newForm = new LGraph<DATA, NAME, WEIGHT>(VCnt, DGraphType);
    switchForm(newForm);
    newForm->setDirected(D);
    dense = LGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getK() {
    int K;
    if (D)
        K = ECnt / (VCnt * (VCnt - 1));
    else
        K = VCnt * (VCnt - 1) / 2;
    return K;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::isDense() {
    return dense;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::isDirected() {
    return D;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getE() {
    return ECnt;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getV() {
    return VCnt;
}


template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::getEdge(VertexT *v1, VertexT *v2) {
    return graphForm->getEdge(v1, v2);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::getEdge(int v1, int v2) {
    return graphForm->getEdge(v1, v2);
}

template<typename DATA, typename NAME, typename WEIGHT>
bool SimpleGraph<DATA, NAME, WEIGHT>::deleteE(EdgeT *e) {
    bool deleted = graphForm->deleteE(e);
    cout << deleted << endl;
    if (deleted) {
        ECnt--;
    }
    return deleted;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j) {
    ECnt++;
    return graphForm->insertE(i, j);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j, int _w) {
    EdgeT* edge = graphForm->insertE(i, j, _w);
    if (edge) {
        ECnt++;
    }
    return edge;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::printGraph() {
    graphForm->print();
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::EdgeIterator SimpleGraph<DATA, NAME, WEIGHT>::eBegin() {
    return EdgeIterator(graphForm->getEdgeVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::EdgeIterator SimpleGraph<DATA, NAME, WEIGHT>::eEnd() {
    return EdgeIterator(nullptr, -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::VertexIterator SimpleGraph<DATA, NAME, WEIGHT>::vBegin() {
    return VertexIterator(graphForm->getVertexVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::VertexIterator SimpleGraph<DATA, NAME, WEIGHT>::vEnd() {
    return VertexIterator(graphForm->getVertexVector(), -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::EdgeIterator SimpleGraph<DATA, NAME, WEIGHT>::adjEBegin(int v) {
    return EdgeIterator(graphForm->getEdgeVector(v), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
typename SimpleGraph<DATA, NAME, WEIGHT>::EdgeIterator SimpleGraph<DATA, NAME, WEIGHT>::adjEEnd(int v) {
    return EdgeIterator(nullptr, -1);
}

