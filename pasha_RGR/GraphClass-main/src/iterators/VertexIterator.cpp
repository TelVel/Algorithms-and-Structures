#include "VertexIterator.h"

template<typename DATA, typename NAME, typename WEIGHT>
VertexIterator<DATA, NAME, WEIGHT>::VertexIterator(vector<VertexT *> &_vertexVector, int ind) {
    vertexVector = _vertexVector;
    index = ind;
    if (vertexVector.size() <= 0) index = -1;
}

template
class VertexIterator<int, string, int>;