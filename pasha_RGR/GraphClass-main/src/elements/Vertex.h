#ifndef GRAPH_RGR_VERTEX_H
#define GRAPH_RGR_VERTEX_H

#include <string>

using namespace std;

template<typename DATA, typename NAME>
class Vertex {
public:
    Vertex();

    Vertex(NAME _name, DATA _data);

    NAME getName();

    void setName(NAME _name);

    DATA getData();

    void setData(int _data);

    int getInd();

    void setInd(int _ind);

private:
    NAME name;
    DATA data;
    int index;
};


#endif //GRAPH_RGR_VERTEX_H
