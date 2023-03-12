#pragma once

#include <string>
#include <vector>
#include <map>

struct Cmp {
    bool operator()(int64_t a, int64_t b) const {
        return a > b;
    }
};

class Poly {
public:
    Poly();
    explicit Poly(std::vector<int64_t> coefs);
    Poly(std::initializer_list<std::pair<int64_t, int64_t>> coefs);
    bool operator==(const Poly& other) const;
    Poly operator-() const;
    friend std::ostream& operator<<(std::ostream& stream, const Poly& poly);
    friend Poly& operator+=(Poly& lhs, const Poly& rhs);
    friend Poly& operator-=(Poly& lhs, const Poly& rhs);
    friend Poly operator*=(Poly& lhs, const Poly& rhs);
    friend Poly operator-(const Poly& lhs, const Poly& rhs);
    friend Poly operator+(const Poly& lhs, const Poly& rhs);
    friend Poly operator*(const Poly& lhs, const Poly& rhs);
    int64_t operator()(int64_t a) const;

private:
    std::map<int64_t, int64_t, Cmp> coefs_;
};