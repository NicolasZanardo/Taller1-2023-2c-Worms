#ifndef ROULETE_H
#define ROULETE_H

#include <vector>
#include <functional>

template <typename T>
class Roulete {
    int current_idx;
    public:
    std::vector<T> values;

    Roulete() : current_idx(0), values() {}
    
    T current() {
        return values[current_idx];
    }

    void next() {
        current_idx = (current_idx+1) % values.size();
    }

    void remove_if(std::function<bool(T)> must_remove) {
        int idx = 0;
        std::remove_if(values.begin(), values.end(), [must_remove, &idx, this](T item) {
            if (must_remove(item)) {
                if (idx <= current_idx) {
                    current_idx -= 1;
                }
                return true;
            }
            idx += 1;
            return false;
        });
    }
};
#endif