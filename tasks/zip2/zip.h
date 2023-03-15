#pragma once

#include <iterator>
#include <vector>

template <typename T, typename U>
class Zipped {
public:
    Zipped(T f_begin, T f_end, U s_begin, U s_end)
        : f_begin_(f_begin), f_end_(f_end), s_begin_(s_begin), s_end_(s_end) {
    }

    class ZipIterator {
    public:
        using ValueType =
            std::pair<typename std::iterator_traits<T>::value_type, typename std::iterator_traits<U>::value_type>;

        ZipIterator(T it1, U it2) : it1_(it1), it2_(it2) {
        }

        bool operator==(const ZipIterator& other) const {
            return it1_ == other.it1_ || it2_ == other.it2_;
        }

        bool operator!=(const ZipIterator& other) const {
            return it1_ != other.it1_ || it2_ != other.it2_;
        }

        ValueType operator*() const {
            return {*it1_, *it2_};
        }

        ZipIterator& operator++() {
            ++it1_;
            ++it2_;
            return *this;
        }

    private:
        T it1_;
        U it2_;
    };

    ZipIterator begin() const {
        return ZipIterator(f_begin_, s_begin_);
    }

    ZipIterator end() const {
        return ZipIterator(f_end_, s_end_);
    }

private:
    T f_begin_;
    T f_end_;
    U s_begin_;
    U s_end_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    auto f_end = std::begin(sequence1);
    auto s_end = std::begin(sequence2);
    for (; f_end != std::end(sequence1) && s_end != std::end(sequence2); ++f_end, ++s_end) {
    }

    return Zipped(std::begin(sequence1), f_end, std::begin(sequence2), s_end);
}
