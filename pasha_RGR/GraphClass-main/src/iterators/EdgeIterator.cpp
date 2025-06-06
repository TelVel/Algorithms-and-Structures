#include "EdgeIterator.h"

template<typename DATA, typename NAME, typename WEIGHT>
EdgeIterator<DATA, NAME, WEIGHT>::EdgeIterator(vector<EdgeT *> *_edgeVector, int ind) {
    index = ind;
    edgeVector = _edgeVector;
    if (!edgeVector || edgeVector->size() <= 0) index = -1;
}

template
class EdgeIterator<int, string, int>;