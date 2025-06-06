#include "SimpleGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph() {
    VCount = 0;
    ECount = 0;
    D = false;
    dense = false;
    graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCount, bool _D, bool _F) {
    VCount = _VCount;
    ECount = 0;
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);

    for (int i = 0; i < VCount; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(int _VCount, int _ECount, bool _D, bool _F) {
    VCount = _VCount;
    ECount = 0;  // Start with 0 and increment as edges are added
    D = _D;
    dense = _F;

    if (dense == LGraphType)
        graphForm = new LGraph<DATA, NAME, WEIGHT>(VCount, D);
    else
        graphForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);

    for (int i = 0; i < VCount; ++i) {
        graphForm->getVertexVector().push_back(new VertexT());
        graphForm->getVertexVector()[i]->setName(to_string(i));
        graphForm->getVertexVector()[i]->setInd(i);
        graphForm->getVertexVector()[i]->setData(i+10);
    }
    
    if (_ECount <= 0) return;
    
    // Calculate maximum possible edges
    int maxEdges;
    if (D) {
        maxEdges = VCount * (VCount - 1);
    } else {
        maxEdges = (VCount * (VCount - 1)) / 2;
    }
    
    // Limit ECount to maximum possible edges
    int targetEdges = min(_ECount, maxEdges);
    
    // Add random edges until we reach the target
    srand(time(0));
    while (ECount < targetEdges) {
        int v1 = rand() % VCount;
        int v2 = rand() % VCount;
        
        // Skip self-loops
        if (v1 == v2) continue;
        
        // Skip if edge already exists
        if (graphForm->hasEdge(v1, v2)) continue;
        
        // Add the edge
        EdgeT* edge = graphForm->insertE(graphForm->getVertexVector()[v1], graphForm->getVertexVector()[v2]);
        if (edge) {
            ECount++;
        }
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
SimpleGraph<DATA, NAME, WEIGHT>::SimpleGraph(SimpleGraph &G) {
    VCount = G.VCount;
    ECount = G.ECount;
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
    // First, count and delete all edges connected to this vertex
    int edgesDeleted = 0;
    EdgeT* edge;
    
    if (D) {
        // For directed graphs, count both incoming and outgoing edges
        // Delete all incoming edges
        for (int i = 0; i < VCount; ++i) {
            edge = graphForm->getEdge(graphForm->getVertexVector()[i], v);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
            }
        }
        
        // Delete all outgoing edges
        for (int i = 0; i < VCount; ++i) {
            edge = graphForm->getEdge(v, graphForm->getVertexVector()[i]);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
            }
        }
    } else {
        // For undirected graphs, only count edges once
        for (int i = 0; i < VCount; ++i) {
            edge = graphForm->getEdge(v, graphForm->getVertexVector()[i]);
            if (edge) {
                graphForm->deleteE(edge);
                edgesDeleted++;
                // The corresponding edge in the opposite direction will be deleted by the graph implementation
            }
        }
    }
    
    // Update edge count
    ECount -= edgesDeleted;
    
    // Now delete the vertex itself
    for (int i = 0; i < VCount; ++i) {
        if (graphForm->getVertexVector()[i]->getInd() == v->getInd()) {
            delete graphForm->getVertexVector()[i];
            for (int j = i; j < VCount - 1; ++j) {
                graphForm->getVertexVector()[j] = graphForm->getVertexVector()[j + 1];
            }
            graphForm->deleteV(v->getInd());
            VCount--;
            graphForm->getVertexVector().resize(VCount);
            return true;
        }
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV() {
    auto *v = new Vertex<DATA, NAME>;
    VCount++;
    v->setInd(VCount - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCount - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *SimpleGraph<DATA, NAME, WEIGHT>::insertV(NAME name) {
    auto *v = new Vertex<DATA, NAME>;
    VCount++;
    v->setName(name);
    v->setInd(VCount - 1);
    graphForm->getVertexVector().push_back(v);
    graphForm->insertV(VCount - 1);
    return v;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::switchForm(GraphForm<DATA, NAME, WEIGHT> *newForm) {
    // First, create a mapping of old vertices to new vertices
    vector<VertexT*>& oldVertices = graphForm->getVertexVector();
    
    // Copy vertices while preserving indices
    for (size_t i = 0; i < oldVertices.size(); ++i) {
        VertexT* oldVertex = oldVertices[i];
        // Create new vertex with exact same properties
        VertexT* newVertex = new VertexT();
        newVertex->setInd(oldVertex->getInd());
        newVertex->setName(oldVertex->getName());
        newVertex->setData(oldVertex->getData());
        // Add to new graph's vertex vector
        newForm->getVertexVector().push_back(newVertex);
        newForm->insertV(newVertex->getInd());
    }

    ECount = 0;

    // Get all edges from old form
    vector<Edge<DATA, NAME, WEIGHT>*>* oldEdges = graphForm->getEdgeVector();
    if (oldEdges) {
        for (EdgeT* oldEdge : *oldEdges) {
            if (!oldEdge || !oldEdge->getV1() || !oldEdge->getV2()) continue;
            
            // Get indices from old edge
            int v1Idx = oldEdge->getV1()->getInd();
            int v2Idx = oldEdge->getV2()->getInd();
            
            // Validate indices
            if (v1Idx < 0 || v2Idx < 0 || 
                v1Idx >= newForm->getVertexVector().size() || 
                v2Idx >= newForm->getVertexVector().size()) {
                continue;
            }
            
            // Get corresponding vertices from new form
            VertexT* newV1 = newForm->getVertexVector()[v1Idx];
            VertexT* newV2 = newForm->getVertexVector()[v2Idx];
            
            if (!newV1 || !newV2) continue;
            
            // Create edge with same properties
            EdgeT* newEdge = newForm->insertE(newV1, newV2, oldEdge->getW());
            if (newEdge) {
                newEdge->setData(oldEdge->getData());
                ECount++;
            }
        }
        delete oldEdges;
    }
    
    // Set directed property
    newForm->setDirected(D);
    
    delete graphForm;
    graphForm = newForm;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toMatrixGraph() {
    if (dense == MGraphType) return;
    auto newForm = new MGraph<DATA, NAME, WEIGHT>(VCount, D);
    switchForm(newForm);
    dense = MGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::toListGraph() {
    if (dense == LGraphType)return;
    auto newForm = new LGraph<DATA, NAME, WEIGHT>(VCount, DGraphType);
    switchForm(newForm);
    newForm->setDirected(D);
    dense = LGraphType;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getK() {
    int K;
    if (D)
        K = ECount / (VCount * (VCount - 1));
    else
        K = VCount * (VCount - 1) / 2;
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
    return ECount;
}

template<typename DATA, typename NAME, typename WEIGHT>
int SimpleGraph<DATA, NAME, WEIGHT>::getV() {
    return VCount;
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
        ECount--;
    }
    return deleted;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j) {
    ECount++;
    return graphForm->insertE(i, j);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *SimpleGraph<DATA, NAME, WEIGHT>::insertE(VertexT *i, VertexT *j, int _w) {
    EdgeT* edge = graphForm->insertE(i, j, _w);
    if (edge) {
        ECount++;
    }
    return edge;
}

template<typename DATA, typename NAME, typename WEIGHT>
void SimpleGraph<DATA, NAME, WEIGHT>::printGraph() {
    graphForm->print();
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::eEnd() {
    return EdgeIterator<DATA, NAME, WEIGHT>(nullptr, -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::eBegin() {
    return EdgeIterator<DATA, NAME, WEIGHT>(graphForm->getEdgeVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
VertexIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::vEnd() {
    return VertexIterator<DATA, NAME, WEIGHT>(graphForm->getVertexVector(), -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
VertexIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::vBegin() {
    return VertexIterator<DATA, NAME, WEIGHT>(graphForm->getVertexVector(), 0);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::adjEEnd(int v) {
    return EdgeIterator<DATA, NAME, WEIGHT>(nullptr, -1);
}

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT> SimpleGraph<DATA, NAME, WEIGHT>::adjEBegin(int v) {
    return EdgeIterator<DATA, NAME, WEIGHT>(graphForm->getEdgeVector(v), 0);
}

