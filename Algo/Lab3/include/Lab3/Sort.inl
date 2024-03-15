#ifndef LAB3_SORT_INL
#define LAB3_SORT_INL

#include <algorithm>

namespace lab3 {

namespace detail {

constexpr std::ptrdiff_t kMaxSizeForInsertionSort = 32;

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
static inline Iter median_of_three(Iter first, Iter last, Compare comp) {
    --last;
    Iter middle = first + (last - first) / 2;

    if (comp(*last, *first)) {
        if (comp(*middle, *last))
            return last;
        else if (comp(*middle, *first))
            return middle;
        else
            return first;
    } else {
        if (comp(*middle, *first))
            return first;
        else if (comp(*middle, *last))
            return middle;
        else
            return last;
    }
}

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
static inline Iter partition(Iter first, Iter last, Compare comp) {
    Iter pivot = median_of_three(first, last, comp);
    auto value = *pivot;

    Iter left = first, right = last - 1;
    while (true) {
        while (comp(*left, value)) ++left;
        while (comp(value, *right)) --right;

        if (left >= right) {
            break;
        }
        std::swap(*left, *right);
        ++left;
        --right;
    }
    return right + 1;
}

}

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void sort(Iter first, Iter last, Compare comp) {
    const auto size = last - first;
    if (size <= detail::kMaxSizeForInsertionSort) {
        insertion_sort(first, last, comp);
    } else {
        quick_sort(first, last, comp, true);
    }
}

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void quick_sort(Iter first, Iter last, Compare comp, const bool optimize_tiny) {
    auto sort = [optimize_tiny](Iter first, Iter last, Compare comp) {
        if (optimize_tiny) {
            lab3::sort(first, last, comp);
        } else {
            lab3::quick_sort(first, last, comp);
        }
    };
    while (last - first > 1) {
        Iter partition = detail::partition(first, last, comp);
        if (partition - first < last - partition) {
            sort(first, partition, comp);
            first = partition;
        } else {
            sort(partition, last, comp);
            last = partition;
        }
    }
}

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void insertion_sort(Iter first, Iter last, Compare comp) {
    if (last - first <= 1) {
        return;
    }

    for (Iter i = first + 1; i != last; ++i) {
        auto value = std::move(*i);
        auto j = (i - first) - 1;

        while (j >= 0 && comp(value, *(first + j))) {
            *(first + (j + 1)) = std::move(*(first + j));
            --j;
        }
        *(first + (j + 1)) = std::move(value);
    }
}

}

#endif //LAB3_SORT_INL
