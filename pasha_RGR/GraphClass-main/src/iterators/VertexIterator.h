#ifndef ASD_RGR_VERTEXITERATOR_H
#define ASD_RGR_VERTEXITERATOR_H

#include <vector>
#include "../elements/Vertex.h"

template<typename DATA, typename NAME, typename WEIGHT>
class VertexIterator {
public:
    using VertexT = Vertex<DATA, NAME>;
    using reference = VertexIterator &;

    VertexIterator(vector<VertexT *> &vertexVector, int ind);

    NAME operator*() const { return vertexVector[index]->getName(); }

    Vertex<DATA, NAME> *operator->() { return vertexVector[index]; }

    friend bool operator==(const VertexIterator &a, const VertexIterator &b) { return a.index == b.index; };

    friend bool operator!=(const VertexIterator &a, const VertexIterator &b) { return a.index != b.index; };

    const reference &operator++() {
        index++;
        if (index == vertexVector.size()) index = -1;
        return *this;
    }

    const reference operator++(int) {
        index++;
        if (index == vertexVector.size()) index = -1;
        return *this;
    }

private:
    vector<VertexT *> vertexVector;
    int index;
};


#endif //ASD_RGR_VERTEXITERATOR_H
