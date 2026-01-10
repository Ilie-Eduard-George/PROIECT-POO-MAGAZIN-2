#pragma once
#include <vector>
#include <ostream>
#include <stdexcept>

template <typename T>
class History {
private:
    std::vector<T> items_;

public:
    void add(const T& item) { items_.push_back(item); }

    std::size_t size() const { return items_.size(); }

    void clear() { items_.clear(); }

    void print(std::ostream& os) const {
        for (const auto& x : items_) os << x << "\n";
    }
};
