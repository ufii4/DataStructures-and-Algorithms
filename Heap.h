//
// Created by pcxie on 2020/12/4.
//

#ifndef DATASTRUCTURES_AND_ALGORITHMS_HEAP_H
#define DATASTRUCTURES_AND_ALGORITHMS_HEAP_H
#include <functional>

template<class T>
class Heap {
public:
    static void heapSort(size_t size, T *array, std::function<bool(T, T)> compare) {
        buildHeap(size, array, compare);
        for (int i = size; i > 2; i--) {
            std::swap(array[i - 1], array[0]);
            heapify(i-1, array, 1, compare);
        }
        std::swap(array[1],array[0]);
    }

    static void heapify(size_t size, T *array, size_t index, std::function<bool(T, T)> compare) {
        if (2 * index > size || index < 1) {
            return;
        }
        size_t i = index - 1;
        size_t l = 2 * index - 1;
        size_t r = 2 * index;
        size_t prior = i;
        if (l <= size - 1 && compare(array[l], array[prior])) {
            prior = l;
        }
        if (r <= size - 1 && compare(array[r], array[prior])) {
            prior = r;
        }
        if (prior == i) {
            return;
        }
        std::swap(array[i], array[prior]);
        heapify(size, array, prior + 1, compare);
    }

    static void buildHeap(size_t size, T *array, std::function<bool(T, T)> compare) {
        for (size_t i = size / 2; i > 0; i--) {
            heapify(size, array, i, compare);
        }
    }

};
#endif //DATASTRUCTURES_AND_ALGORITHMS_HEAP_H
