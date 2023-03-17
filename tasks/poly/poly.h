#pragma once

#include <string>
#include <vector>
#include <map>

class Poly {
public:
    Poly() = default;
    explicit Poly(std::vector<int64_t> coefs);
    Poly(std::initializer_list<std::pair<const int64_t, int64_t>> coefs);
    bool operator==(const Poly& other) const;
    Poly operator-() const;
    int64_t operator()(int64_t a) const;
    friend std::ostream& operator<<(std::ostream& stream, const Poly& poly);
    Poly& operator+=(const Poly& rhs);
    Poly& operator-=(const Poly& rhs);
    Poly& operator*=(const Poly& rhs);
    friend Poly operator-(const Poly& lhs, const Poly& rhs);
    friend Poly operator+(const Poly& lhs, const Poly& rhs);
    friend Poly operator*(const Poly& lhs, const Poly& rhs);

private:
    struct Cmp {
        bool operator()(int64_t a, int64_t b) const {
            return a > b;
        }
    };
    int64_t MyPow(int64_t base, int64_t exp) const;
    static Poly& DeleteZeros(Poly& p);
    std::map<int64_t, int64_t, Cmp> coefs_;
};