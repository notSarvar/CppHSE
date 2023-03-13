#pragma once

#include <iterator>
#include <vector>

//std::pair<typename std::iterator_traits<Iter1>::value_type, typename std::iterator_traits<Iter2>::value_type>

template <typename T, typename U>
auto Zip(const T& sequence1, const U& sequence2) {
    auto it1 = std::begin(sequence1);
    auto it2 = std::begin(sequence2);

    template<typename T, typename U>
    class ZipIterator {
    public:
        using value_type = std::pair<T, U>;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        ZipIterator(const typename std::vector<T>::const_iterator& it1,
                    const typename std::vector<U>::const_iterator& it2)
            : it1_(it1), it2_(it2) {}

        bool operator==(const ZipIterator& other) const {
            return it1_ == other.it1_ || it2_ == other.it2_;
        }

        bool operator!=(const ZipIterator& other) const {
            return *this != other;
        }

        reference operator*() const {
            return { *it1_, *it2_ };
        }

        ZipIterator& operator++() {
            ++it1_;
            ++it2_;
            return *this;
        }

    private:
        typename std::vector<T>::const_iterator it1_;
        typename std::vector<U>::const_iterator it2_;
    };

    template<typename T, typename U>
    class ZipRange {
    public:
        using iterator = ZipIterator<T, U>;

        ZipRange(const std::vector<T>& v1, const std::vector<U>& v2)
            : v1_(v1), v2_(v2) {}

        iterator begin() const {
            return { std::begin(v1_), std::begin(v2_) };
        }

        iterator end() const {
            return { std::end(v1_), std::end(v2_) };
        }

    private:
        const std::vector<T>& v1_;
        const std::vector<U>& v2_;
    };
     return {sequence1, seqquence2};

}
