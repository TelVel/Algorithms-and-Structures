#include "LGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
LGraph<DATA, NAME, WEIGHT>::LGraph(unsigned _size, bool _directed) {
    size = _size;
    directed = _directed;
    list = nullptr;
    vertexVector.clear();  // Ensure vector is empty
    
    // Create vertices in correct order (size-1 to 0)
    VNode* lastNode = nullptr;
    for (int i = 0; i < size; ++i) {
        // Create vertex in vector first
        VertexT* vertex = new VertexT();
        vertex->setInd(i);
        vertex->setName(to_string(i));
        vertexVector.push_back(vertex);
        
        // Create list node
        VNode* newNode = new VNode(i, nullptr, nullptr);
        if (!list) {
            list = newNode;
        } else {
            lastNode->next = newNode;
        }
        lastNode = newNode;
    }
    
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
}

template<typename DATA, typename NAME, typename WEIGHT>
LGraph<DATA, NAME, WEIGHT>::LGraph(LGraph &G) {
    size = G.size;
    directed = G.directed;
    edgeVector = G.edgeVector;
    list = G.list;
}

template<typename DATA, typename NAME, typename WEIGHT>
void LGraph<DATA, NAME, WEIGHT>::insertV(int v) {
    if (v < 0 || v >= size) return;
    
    // Check if vertex already exists in list
    VNode *vtmp = list;
    VNode *prev = nullptr;
    
    while (vtmp && vtmp->v_ind < v) {
        prev = vtmp;
        vtmp = vtmp->next;
    }
    
    // If vertex already exists, return
    if (vtmp && vtmp->v_ind == v) return;
    
    // Create new vertex node
    VNode* newNode = new VNode(v, nullptr, vtmp);
    
    // Insert at correct position
    if (!prev) {
        list = newNode;
    } else {
        prev->next = newNode;
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
LGraph<DATA, NAME, WEIGHT>::~LGraph() {
    VNode *vtmp;
    ENode *elist, *etmp;
    while (list) {
        elist = list->eNode;
        while (elist) {
            etmp = elist->next;
            delete elist;
            elist = etmp;
        }
        vtmp = list->next;
        delete list;
        list = vtmp;
    }
    delete edgeVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool LGraph<DATA, NAME, WEIGHT>::hasEdge(int i, int j) {
    VNode *vtmp = list;
    ENode *etmp;
    Edge<DATA, NAME, WEIGHT> *e;
    while (vtmp) {
        etmp = vtmp->eNode;
        while (etmp) {
            e = etmp->e;
            if (e->getV1()->getInd() == i && e->getV2()->getInd() == j) {
                return true;
            }
            etmp = etmp->next;
        }
        vtmp = vtmp->next;
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *LGraph<DATA, NAME, WEIGHT>::getEdge(VertexT *v1, VertexT *v2) {
    return getEdge(v1->getInd(), v2->getInd());
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT>* LGraph<DATA, NAME, WEIGHT>::getEdge(int v1, int v2) {
    VNode* vnode = list;
    while (vnode) {
        if (vnode->v_ind == v1) {  // Нашли вершину v1
            ENode* enode = vnode->eNode;
            while (enode) {
                if (enode->e->getV2()->getInd() == v2) {  // Нашли ребро в v2
                    return enode->e;
                }
                enode = enode->next;
            }
            break;  // Все рёбра проверены
        }
        vnode = vnode->next;
    }
    return nullptr;  // Ребро не найдено
}

template<typename DATA, typename NAME, typename WEIGHT>
bool LGraph<DATA, NAME, WEIGHT>::deleteE(EdgeT *e) {
    VNode *vtmp = list;
    ENode *etmp, *prev;
    while (vtmp) {
        prev = vtmp->eNode;
        etmp = vtmp->eNode;
        if (etmp && (etmp->e->getV1() == e->getV1() && etmp->e->getV2() == e->getV2())) {
            vtmp->eNode = etmp->next;
            delete etmp->e;
            delete etmp;
            return true;
        }
        if (etmp) etmp = etmp->next;
        while (etmp) {
            if (etmp && (etmp->e->getV1() == e->getV1() && etmp->e->getV2() == e->getV2())) {
                prev->next = etmp->next;
                delete etmp->e;
                delete etmp;
                return true;
            }
            prev = etmp;
            etmp = etmp->next;
        }
        vtmp = vtmp->next;
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *LGraph<DATA, NAME, WEIGHT>::insertE(VertexT *v1, VertexT *v2) {
    Edge<DATA, NAME, WEIGHT> *res = insert(v1, v2, 1);
    if (!directed && res) {
        insert(v2, v1, 1);
    }
    return res;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *LGraph<DATA, NAME, WEIGHT>::insertE(VertexT *v1, VertexT *v2, int _w) {
    Edge<DATA, NAME, WEIGHT> *res = insert(v1, v2, _w);
    if (!directed && res) {
        insert(v2, v1, _w);
    }
    return res;
}

template<typename DATA, typename NAME, typename WEIGHT>
void LGraph<DATA, NAME, WEIGHT>::setDirected(bool d) {
    directed = d;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool LGraph<DATA, NAME, WEIGHT>::deleteV(int v) {
    VNode *vtmp, *prev;
    vtmp = prev = list;
    ENode *etmp, *edel;
    if (vtmp && vtmp->v_ind == v) {
        etmp = vtmp->eNode;
        while (etmp) {
            edel = etmp;
            etmp = etmp->next;
            delete edel;
        }
        list = vtmp->next;
        delete vtmp;
        size--;
        return true;
    }
    if (vtmp) vtmp = vtmp->next;
    while (vtmp) {
        if (vtmp->v_ind == v) {
            etmp = vtmp->eNode;
            while (etmp) {
                edel = etmp;
                etmp = etmp->next;
                delete edel->e;
                delete edel;
            }
            prev->next = vtmp->next;
            delete vtmp;
            size--;
            return true;
        }
        prev = prev->next;
        vtmp = vtmp->next;
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
void LGraph<DATA, NAME, WEIGHT>::print() {
    VertexT *v;
    VNode *vtmp, *prev;
    vtmp = prev = list;
    ENode *etmp, *edel;
    cout << "LIST" << endl;
    while (vtmp) {
        VertexT* vertex = this->vertexVector[vtmp->v_ind];
        
        cout << "*" << vtmp->v_ind << " [" << vertex->getName() << "]";
        etmp = vtmp->eNode;
        while (etmp) {
            cout  << "->" << etmp->e->getV2()->getInd() << "," << etmp->e->getW() << "," << etmp->e->getData();
            etmp = etmp->next;
        }
        cout << endl;
        vtmp = vtmp->next;
    }

}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Vertex<DATA, NAME> *> &LGraph<DATA, NAME, WEIGHT>::getVertexVector() {
    return vertexVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *LGraph<DATA, NAME, WEIGHT>::insert(VertexT *v1, VertexT *v2) {
    VNode *vtmp = list;
    ENode *etmp;
    Edge<DATA, NAME, WEIGHT> *res;
    while (vtmp) {
        if (vtmp->v_ind == v1->getInd()) {
            etmp = vtmp->eNode;
            res = new Edge<DATA, NAME, WEIGHT>(v1, v2, 1);
            if (!etmp) {
                vtmp->eNode = new ENode(res, nullptr);
            } else {
                while (etmp->next) {
                    etmp = etmp->next;
                }
                etmp->next = new ENode(res, nullptr);
            }
            return res;
        }
        vtmp = vtmp->next;
    }
    return nullptr;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *LGraph<DATA, NAME, WEIGHT>::insert(VertexT *v1, VertexT *v2, int _w) {
    if (!v1 || !v2 || v1->getInd() < 0 || v2->getInd() < 0 || 
        v1->getInd() >= vertexVector.size() || v2->getInd() >= vertexVector.size()) {
        return nullptr;
    }
    
    // Find vertex node for v1
    VNode *vtmp = list;
    while (vtmp && vtmp->v_ind != v1->getInd()) {
        vtmp = vtmp->next;
    }
    if (!vtmp) return nullptr;
    
    // Check for existing edge
    ENode *etmp = vtmp->eNode;
    while (etmp) {
        if (etmp->e && etmp->e->getV2() && 
            etmp->e->getV2()->getInd() == v2->getInd()) {
            return nullptr;
        }
        etmp = etmp->next;
    }
    
    // Use vertices from vertexVector to ensure consistency
    VertexT* sourceVertex = vertexVector[v1->getInd()];
    VertexT* targetVertex = vertexVector[v2->getInd()];
    
    // Create new edge
    Edge<DATA, NAME, WEIGHT> *res = new Edge<DATA, NAME, WEIGHT>(
        sourceVertex, targetVertex, _w
    );
    
    // Add to front of edge list
    vtmp->eNode = new ENode(res, vtmp->eNode);
    return res;
}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Edge<DATA, NAME, WEIGHT> *> *LGraph<DATA, NAME, WEIGHT>::getEdgeVector() {
    if (edgeVector) {
        delete edgeVector;
    }
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
    VNode *vtmp = list;
    ENode *etmp;

    while (vtmp) {
        etmp = vtmp->eNode;
        while (etmp) {
            if (etmp->e && etmp->e->getV1() && etmp->e->getV2() && 
                etmp->e->getV1()->getInd() < size && etmp->e->getV2()->getInd() < size) {
                edgeVector->push_back(etmp->e);
            }
            etmp = etmp->next;
        }
        vtmp = vtmp->next;
    }
    return edgeVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Edge<DATA, NAME, WEIGHT> *> *LGraph<DATA, NAME, WEIGHT>::getEdgeVector(int v) {
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
    VNode *vtmp = list;
    ENode *etmp;

    while (vtmp) {
        if (vtmp->v_ind == v) {
            etmp = vtmp->eNode;
            while (etmp) {
                edgeVector->push_back(etmp->e);
                etmp = etmp->next;
            }
            break;
        }
        vtmp = vtmp->next;
    }
    return edgeVector;
}


template
class LGraph<int, std::string, int>;