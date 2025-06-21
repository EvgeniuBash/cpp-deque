#pragma once

#include <deque>
#include <string>

class Comp {
public:
    Comp() = default;

    bool operator()(const std::string& a, const std::string& b) const {
        return a < b;
    }
};

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1, const std::deque<T>& half2, const Comp& comparator) {
    std::deque<T> half;
    auto leftIterator = half1.begin();
    auto rightIterator = half2.begin();

    while(leftIterator < half1.end() && rightIterator < half2.end()) {
        if (comparator(*leftIterator, *rightIterator)) {
            half.push_back(*leftIterator);
            ++leftIterator;
        } else {
            half.push_back(*rightIterator);
            ++rightIterator;
        }
    }

    while (leftIterator != half1.end()) {
        half.push_back(*leftIterator);
        ++leftIterator;
    }

    while (rightIterator != half2.end()) {
        half.push_back(*rightIterator);
        ++rightIterator;
    }
    std::copy(leftIterator, half1.end(), std::back_inserter(half));
    std::copy(rightIterator, half2.end(), std::back_inserter(half));
    return half;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }

    const size_t mid = src.size() / 2;
    const std::deque<T> left_sorted = MergeSort(std::deque<T>(src.begin(), src.begin() + mid), comparator);
    const std::deque<T> right_sorted = MergeSort(std::deque<T>(src.begin() + mid, src.end()), comparator);

    return Merge(left_sorted, right_sorted, comparator);
    // Реализуйте рекурсивную функцию MergeSort
    // на основе задачи из урока о рекурсии.
}