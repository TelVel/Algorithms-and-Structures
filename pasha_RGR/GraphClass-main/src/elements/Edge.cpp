#include "Edge.h"

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT>::Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2) {
    v1 = _v1;
    v2 = _v2;
    data = v1->getInd() * 10 + v2->getInd();
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT>::Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2, int _w) {
    v1 = _v1;
    v2 = _v2;
    w = _w;
    data = v1->getInd() * 10 + v2->getInd();
}

template<typename DATA, typename NAME, typename WEIGHT>
Edge<DATA, NAME, WEIGHT>::Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2, int _w, DATA _data) {
    v1 = _v1;
    v2 = _v2;
    w = _w;
    data = _data;
}

template<typename DATA, typename NAME, typename WEIGHT>
void Edge<DATA, NAME, WEIGHT>::setData(DATA _data) { data = _data; }

template<typename DATA, typename NAME, typename WEIGHT>
DATA Edge<DATA, NAME, WEIGHT>::getData() { return data; }

template<typename DATA, typename NAME, typename WEIGHT>
void Edge<DATA, NAME, WEIGHT>::setW(WEIGHT _w) { w = _w; }

template<typename DATA, typename NAME, typename WEIGHT>
WEIGHT Edge<DATA, NAME, WEIGHT>::getW() { return w; }

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *Edge<DATA, NAME, WEIGHT>::getV2() { return v2; }

template<typename DATA, typename NAME, typename WEIGHT>
Vertex<DATA, NAME> *Edge<DATA, NAME, WEIGHT>::getV1() { return v1; }
template
class Edge<int, string, int>;