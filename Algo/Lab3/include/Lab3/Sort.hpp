#ifndef LAB3_SORT_HPP
#define LAB3_SORT_HPP

#include <concepts>
#include <compare>

namespace lab3 {

namespace detail {

template<typename T>
concept reference = std::is_reference_v<T>;

template<typename T, typename U>
concept lvalue_reference_of = std::same_as<T, std::add_lvalue_reference_t<U>>;

}

template<typename Iter>
concept Iterator = requires(Iter first, Iter last) {
    { *first } -> detail::reference;
    { first + 1 } -> std::same_as<Iter>;
    { first - 1 } -> std::same_as<Iter>;
    { ++first } -> detail::lvalue_reference_of<Iter>;
    { --first } -> detail::lvalue_reference_of<Iter>;
    { last - first } -> std::signed_integral;
    { first <=> last } -> std::convertible_to<std::partial_ordering>;
};

template<typename Compare, typename T>
concept Comparator = requires(Compare comp, const T &a, const T &b) {
    { comp(a, b) } -> std::same_as<bool>;
};

template<typename Iter, typename Compare>
concept SortableWithComparator = Iterator<Iter> && requires(Iter iter) {
    requires Comparator<Compare, std::remove_cvref_t<decltype(*iter)>>;
};

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void sort(Iter first, Iter last, Compare comp);

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void quick_sort(Iter first, Iter last, Compare comp, bool optimize_tiny = false);

template<typename Iter, typename Compare>
requires SortableWithComparator<Iter, Compare>
void insertion_sort(Iter first, Iter last, Compare comp);

}

#include "Sort.inl"

#endif //LAB3_SORT_HPP
