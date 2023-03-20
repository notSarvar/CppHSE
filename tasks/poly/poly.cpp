#include "poly.h"

#include <iostream>
#include <cmath>

Poly& Poly::DeleteZeros(Poly& p) {
    for (auto i = p.coefs_.begin(); i != p.coefs_.end();) {
        if (i->second) {
            i++;
        } else {
            i = p.coefs_.erase(i);
        }
    }
    return p;
}

Poly::Poly(std::vector<int64_t> coefs) {
    for (int64_t i = 0; i < coefs.size(); ++i) {
        if (coefs[i]) {
            coefs_[i] = coefs[i];
        }
    }
}

Poly::Poly(std::initializer_list<std::pair<const int64_t, int64_t>> coefs) : coefs_(coefs) {
    DeleteZeros(*this);
}

bool Poly::operator==(const Poly& other) const {
    return coefs_ == other.coefs_;
}

int64_t Poly::MyPow(int64_t base, int64_t exp) const {
    int64_t result = 1;
    for (;;) {
        if (exp & 1) {
            result *= base;
        }
        exp >>= 1;
        if (!exp) {
            break;
        }
        base *= base;
    }
    return result;
}

int64_t Poly::operator()(int64_t a) const {
    int64_t sum = 0;
    for (const auto& i : coefs_) {
        sum += i.second * Poly::MyPow(a, i.first);
    }
    return sum;
}

Poly Poly::operator-() const {
    Poly new_poly = *this;
    for (auto& i : new_poly.coefs_) {
        i.second *= -1;
    }
    return new_poly;
}

Poly& Poly::operator+=(const Poly& rhs) {
    for (const auto& i : rhs.coefs_) {
        coefs_[i.first] += i.second;
    }
    return Poly::DeleteZeros(*this);
}

Poly& Poly::operator-=(const Poly& rhs) {
    for (const auto& i : rhs.coefs_) {
        coefs_[i.first] -= i.second;
    }
    return Poly::DeleteZeros(*this);
}

Poly& Poly::operator*=(const Poly& rhs) {
    Poly new_poly;
    for (std::map<int64_t, int64_t, Poly::Cmp>::const_iterator l = coefs_.begin(); l != coefs_.end(); ++l) {
        for (std::map<int64_t, int64_t, Poly::Cmp>::const_iterator r = rhs.coefs_.begin(); r != rhs.coefs_.end(); ++r) {
            new_poly.coefs_[l->first + r->first] += l->second * r->second;
        }
    }
    *this = new_poly;
    return Poly::DeleteZeros(*this);
}

Poly operator-(const Poly& lhs, const Poly& rhs) {
    Poly new_poly = lhs;
    new_poly -= rhs;
    return new_poly;
}

Poly operator+(const Poly& lhs, const Poly& rhs) {
    Poly new_poly = lhs;
    new_poly += rhs;
    return new_poly;
}

Poly operator*(const Poly& lhs, const Poly& rhs) {
    Poly new_poly = lhs;
    new_poly *= rhs;
    return new_poly;
}

std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    if (poly.coefs_.empty()) {
        return stream << "y = 0";
    }
    stream << "y = ";
    bool first_coef = false;
    for (const auto& i : poly.coefs_) {
        auto coef = i.second;
        auto deg = i.first;
        if (first_coef) {
            if (coef < 0) {
                stream << " - ";
                coef *= -1;
            } else {
                stream << " + ";
            }
        }
        first_coef = true;
        stream << coef;
        if (!deg) {
            continue;
        }
        stream << "x^" << deg;
    }
    return stream;
}
