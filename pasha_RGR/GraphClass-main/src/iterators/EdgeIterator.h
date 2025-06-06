#ifndef ASD_RGR_EDGEITERATOR_H
#define ASD_RGR_EDGEITERATOR_H

#include <vector>
#include "../elements/Edge.h"

template<typename DATA, typename NAME, typename WEIGHT>
class EdgeIterator {
public:
    using EdgeT = Edge<DATA, NAME, WEIGHT>;
    using reference = EdgeIterator &;

    EdgeIterator(vector<EdgeT *> *edgeVector, int ind);

    Edge<DATA, NAME, WEIGHT> *operator*() const { return (*edgeVector)[index]; }

    friend bool operator==(const EdgeIterator &a, const EdgeIterator &b) { return a.index == b.index; };

    friend bool operator!=(const EdgeIterator &a, const EdgeIterator &b) { return a.index != b.index; };

    const reference &operator++() {
        index++;
        if (index == edgeVector->size()) index = -1;
        return *this;
    }

    const reference operator++(int) {
        index++;
        if (index == edgeVector->size()) index = -1;
        return *this;
    }

    int getSize() { return edgeVector->size(); };

    int getInd() { return index; }

private:
    vector<EdgeT *> *edgeVector;
    int index;
};


#endif //ASD_RGR_EDGEITERATOR_H
