#ifndef ASD_RGR_EDGE_H
#define ASD_RGR_EDGE_H

#include "Vertex.h"

template<typename DATA, typename NAME, typename WEIGHT>
class Edge {
public:
    Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2);

    Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2, int _w);

    Edge(Vertex<DATA, NAME> *_v1, Vertex<DATA, NAME> *_v2, int _w, DATA _data);

    Vertex<DATA, NAME> *getV1();

    Vertex<DATA, NAME> *getV2();

    WEIGHT getW();

    void setW(WEIGHT _w);

    DATA getData();

    void setData(DATA _data);

private:
    Vertex<DATA, NAME> *v1;
    Vertex<DATA, NAME> *v2;
    WEIGHT w;
    DATA data;
};



#endif //ASD_RGR_EDGE_H
