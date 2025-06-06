#include "MGraph.h"

template<typename DATA, typename NAME, typename WEIGHT>
MGraph<DATA, NAME, WEIGHT>::MGraph(unsigned _size, bool _directed) {
    size = _size;
    directed = _directed;
    
    // Initialize matrix
    matrix.resize(size);
    for (int i = 0; i < size; ++i) {
        matrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = nullptr;
        }
    }
    
    // Initialize vertex vector
    vertexVector.clear();
    for (int i = 0; i < size; ++i) {
        VertexT* vertex = new VertexT();
        vertex->setInd(i);
        vertex->setName(to_string(i));
        vertexVector.push_back(vertex);
    }
    
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
}

template<typename DATA, typename NAME, typename WEIGHT>
MGraph<DATA, NAME, WEIGHT>::MGraph(MGraph &G) {
    size = G.size;
    matrix.resize(size);
    for (int i = 0; i < size; ++i) {
        matrix[i].resize(size);
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = G.matrix[i][j];
        }
    }
    directed = G.directed;
    for (int i = 0; i < size; ++i) {
        vertexVector[i] = G.vertexVector[i];
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
MGraph<DATA, NAME, WEIGHT>::~MGraph() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            delete matrix[i][j];
        }
    }
    delete edgeVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool MGraph<DATA, NAME, WEIGHT>::hasEdge(int i, int j) {
    return matrix[i][j];
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *MGraph<DATA, NAME, WEIGHT>::getEdge(VertexT *v1, VertexT *v2) {
    return matrix[v1->getInd()][v2->getInd()];
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *MGraph<DATA, NAME, WEIGHT>::getEdge(int v1, int v2) {
    return matrix[v1][v2];
}

template<typename DATA, typename NAME, typename WEIGHT>
bool MGraph<DATA, NAME, WEIGHT>::deleteE(EdgeT *e) {
    int i1 = e->getV1()->getInd();
    int i2 = e->getV2()->getInd();
    if (matrix[i1][i2]) {
        delete matrix[i1][i2];
        matrix[i1][i2] = nullptr;
        return true;
    }
    return false;
}

template<typename DATA, typename NAME, typename WEIGHT>
bool MGraph<DATA, NAME, WEIGHT>::deleteV(int v) {
    if (v < 0 || v >= size) return false;

    // Delete all edges connected to this vertex
    for (int j = 0; j < size; ++j) {
        delete matrix[v][j];  // Delete row
        delete matrix[j][v];  // Delete column
    }

    // Shift rows up
    for (int i = v; i < size - 1; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = matrix[i + 1][j];
        }
    }

    // Shift columns left
    for (int i = 0; i < size; ++i) {
        for (int j = v; j < size - 1; ++j) {
            matrix[i][j] = matrix[i][j + 1];
        }
    }

    // Update vertex indices in edges
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1; ++j) {
            if (matrix[i][j]) {
                if (matrix[i][j]->getV1()->getInd() > v) {
                    matrix[i][j]->getV1()->setInd(matrix[i][j]->getV1()->getInd() - 1);
                }
                if (matrix[i][j]->getV2()->getInd() > v) {
                    matrix[i][j]->getV2()->setInd(matrix[i][j]->getV2()->getInd() - 1);
                }
            }
        }
    }

    // Shrink matrix
    size--;
    matrix.resize(size);
    for (int i = 0; i < size; ++i) {
        matrix[i].resize(size);
    }

    return true;
}

template<typename DATA, typename NAME, typename WEIGHT>
void MGraph<DATA, NAME, WEIGHT>::insertV(int v) {
    if (v >= size) {
        matrix.resize(v + 1);
        for (int i = 0; i < v + 1; ++i) {
            matrix[i].resize(v + 1);
            for (int j = size; j < v + 1; ++j) {
                matrix[i][j] = nullptr;
            }
        }
        size++;
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
void MGraph<DATA, NAME, WEIGHT>::setDirected(bool d) {
    directed = d;
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *MGraph<DATA, NAME, WEIGHT>::insertE(VertexT *v1, VertexT *v2) {
    if (!v1 || !v2 || v1->getInd() < 0 || v2->getInd() < 0 || 
        v1->getInd() >= size || v2->getInd() >= size) {
        return nullptr;
    }
    
    // Use vertices from vertexVector
    VertexT* sourceVertex = vertexVector[v1->getInd()];
    VertexT* targetVertex = vertexVector[v2->getInd()];
    
    if (!directed) {
        matrix[v2->getInd()][v1->getInd()] = new Edge<DATA, NAME, WEIGHT>(targetVertex, sourceVertex, 1);
    }
    return matrix[v1->getInd()][v2->getInd()] = new Edge<DATA, NAME, WEIGHT>(sourceVertex, targetVertex, 1);
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT> *MGraph<DATA, NAME, WEIGHT>::insertE(VertexT *v1, VertexT *v2, int _w) {
    if (!v1 || !v2 || v1->getInd() < 0 || v2->getInd() < 0 || 
        v1->getInd() >= size || v2->getInd() >= size) {
        return nullptr;
    }
    
    // Use vertices from vertexVector
    VertexT* sourceVertex = vertexVector[v1->getInd()];
    VertexT* targetVertex = vertexVector[v2->getInd()];
    
    if (!directed) {
        matrix[v2->getInd()][v1->getInd()] = new Edge<DATA, NAME, WEIGHT>(targetVertex, sourceVertex, _w);
    }
    return matrix[v1->getInd()][v2->getInd()] = new Edge<DATA, NAME, WEIGHT>(sourceVertex, targetVertex, _w);
}

template<typename DATA, typename NAME, typename WEIGHT>
void MGraph<DATA, NAME, WEIGHT>::print() {
    cout << "MATRIX" << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j])
                cout << matrix[i][j]->getW() << " ";
            else
                cout << "0 ";
        }
        cout << endl;
    }
}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Vertex<DATA, NAME> *> &MGraph<DATA, NAME, WEIGHT>::getVertexVector() {
    return vertexVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Edge<DATA, NAME, WEIGHT> *> *MGraph<DATA, NAME, WEIGHT>::getEdgeVector() {
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j])
                edgeVector->push_back(matrix[i][j]);
        }
    }
    return edgeVector;
}

template<typename DATA, typename NAME, typename WEIGHT>
vector<Edge<DATA, NAME, WEIGHT> *> *MGraph<DATA, NAME, WEIGHT>::getEdgeVector(int v) {
    edgeVector = new vector<Edge<DATA, NAME, WEIGHT> *>();
    if (v < size)
        for (int i = 0; i < size; ++i) {
            if (matrix[v][i])
                edgeVector->push_back(matrix[v][i]);
        }
    return edgeVector;
}

template
class MGraph<int, std::string, int>;
