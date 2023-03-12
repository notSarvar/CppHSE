#include "poly.h"

#include <iostream>
#include <cmath>

Poly::Poly() = default;

Poly::Poly(std::vector<int64_t> coefs) {
    for (int64_t i = 0; i < coefs.size(); ++i) {
        if (coefs[i]) {
            coefs_[i] = coefs[i];
        }
    }
}

Poly::Poly(std::initializer_list<std::pair<int64_t, int64_t>> coefs) {
    for (const auto& i : coefs) {
        if (i.second) {
            coefs_[i.first] = i.second;
        }
    }
}

bool Poly::operator==(const Poly& other) const {
    return coefs_ == other.coefs_;
}

int64_t Binpow(int64_t x, int64_t n) {
    int64_t res = 1;
    while (n) {
        if (n & 1) {
            res *= x;
        }
        x *= x;
        n >>= 1;
    }
    return res;
}

int64_t Poly::operator()(int64_t a) const {
    int64_t sum = 0;
    for (const auto& i : coefs_) {
        sum += i.second * static_cast<int64_t>(pow(static_cast<double>(a), static_cast<double>(i.first)));
    }
    return sum;
}

Poly Poly::operator-() const {
    Poly new_poly = *this;
    for (auto& i : coefs_) {
        new_poly.coefs_[i.first] *= -1;
    }
    return new_poly;
}

Poly& operator+=(Poly& lhs, const Poly& rhs) {
    for (const auto i : rhs.coefs_) {
        lhs.coefs_[i.first] += i.second;
    }
    for (auto& i : lhs.coefs_) {
        if (!i.second) {
            lhs.coefs_.erase(i.first);
        }
    }
    return lhs;
}

Poly& operator-=(Poly& lhs, const Poly& rhs) {
    for (const auto i : rhs.coefs_) {
        lhs.coefs_[i.first] -= i.second;
    }
    for (auto& i : lhs.coefs_) {
        if (!i.second) {
            lhs.coefs_.erase(i.first);
        }
    }
    return lhs;
}

Poly operator-(const Poly& lhs, const Poly& rhs) {
    Poly new_poly = lhs;

    for (const auto& i : rhs.coefs_) {
        new_poly.coefs_[i.first] -= i.second;
    }
    std::vector<int64_t> deletes;
    for (const auto& i : new_poly.coefs_) {
        if (!i.second) {
            deletes.push_back(i.first);
        }
    }
    for (auto i : deletes) {
        new_poly.coefs_.erase(i);
    }
    return new_poly;
}

Poly operator+(const Poly& lhs, const Poly& rhs) {
    Poly new_poly = lhs;
    for (const auto i : rhs.coefs_) {
        new_poly.coefs_[i.first] += i.second;
    }
    return new_poly;
}

Poly operator*(const Poly& lhs, const Poly& rhs) {
    Poly new_poly;
    for (std::map<int64_t, int64_t>::const_iterator l = lhs.coefs_.begin(); l != lhs.coefs_.end(); ++l) {
        for (std::map<int64_t, int64_t>::const_iterator r = rhs.coefs_.begin(); r != rhs.coefs_.end(); ++r) {
            new_poly.coefs_[l->first + r->first] += l->second * r->second;
        }
    }
    return new_poly;
}

Poly operator*=(Poly& lhs, const Poly& rhs) {
    for (std::map<int64_t, int64_t>::const_iterator l = lhs.coefs_.begin(); l != lhs.coefs_.end(); ++l) {
        for (std::map<int64_t, int64_t>::const_iterator r = rhs.coefs_.begin(); r != rhs.coefs_.end(); ++r) {
            lhs.coefs_[l->first + r->first] += l->second * r->second;
        }
    }
    return lhs;
}

std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    if (poly.coefs_.empty()) {
        std::string ans = "y = 0";
        stream << ans;
        return stream;
    }
    std::string ans = "y = ";
    std::string s;
    size_t f = 1;
    for (auto i : poly.coefs_) {
        auto coef = i.second;
        auto deg = i.first;
        if (!f) {
            if (coef < 0) {
                s = " - ";
                coef *= -1;
            } else {
                s = " + ";
            }
        }
        f = 0;
        ans += s;
        ans += std::to_string(coef);
        if (!deg) {
            continue;
        }
        ans += "x^";
        ans += std::to_string(deg);
    }
    stream << ans;
    return stream;
}
