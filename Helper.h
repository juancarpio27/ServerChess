//
// Created by pablo on 4/11/15.
//

#ifndef CHESS_SOLVER_HELPER_H
#define CHESS_SOLVER_HELPER_H

#include <vector>
#include <algorithm>

template<typename T>
inline void remove(std::vector<T> &v, const T &item) {
    v.erase(std::remove(v.begin(), v.end(), item), v.end());
}

#endif //CHESS_SOLVER_HELPER_H
