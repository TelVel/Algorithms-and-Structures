#include "Vertex.h"

template<typename DATA, typename NAME>
Vertex<DATA, NAME>::Vertex() {
    //name = nullptr;
    data = 0;
    index = 0;
}

template<typename DATA, typename NAME>
Vertex<DATA, NAME>::Vertex(NAME _name, DATA _data) {
    name = _name;
    data = _data;
}

template<typename DATA, typename NAME>
NAME Vertex<DATA, NAME>::getName() { return name; }

template<typename DATA, typename NAME>
DATA Vertex<DATA, NAME>::getData() { return data; };

template<typename DATA, typename NAME>
void Vertex<DATA, NAME>::setName(NAME _name) { name = _name; }

template<typename DATA, typename NAME>
void Vertex<DATA, NAME>::setData(int _data) { data = _data; }

template<typename DATA, typename NAME>
int Vertex<DATA, NAME>::getInd() { return index; }

template<typename DATA, typename NAME>
void Vertex<DATA, NAME>::setInd(int _ind) { index = _ind; }

template
class Vertex<int, string>;