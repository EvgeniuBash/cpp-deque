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
    size_t f1 = 0, f2 = 0;

    while(f1 < half1.size() && f2 < half2.size()) {
        if (comparator(half1[f1], half2[f2])) {
            half.push_back(half1[f1]);
            ++f1;
        } else {
            half.push_back(half2[f2]);
            ++f2;
        }
    }

    while (f1 < half1.size()) {
        half.push_back(half1[f1]);
        ++f1;
    }

    while (f2 < half2.size()) {
        half.push_back(half2[f2]);
        ++f2;
    }
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