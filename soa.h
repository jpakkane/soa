/*
 * soa : Struct of arrays
 * Copyright (c) 2015 Jussi Pakkanen
 *
 * Lmsmap is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 3 as published by the Free Software Foundation
 *
 * Lmsmap is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with Libav; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#pragma once
#include<vector>
#include<utility>

template<typename T>
class Soa final {
private:

    struct SoaItem {
        T item1;
        T item2;
    };

    struct SoaItemRef {
        T &item1;
        T &item2;
    };

public:
    Soa() {}
    ~Soa() {}

    size_t size() const noexcept { return array1.size(); }
    bool empty() const noexcept { return array1.empty(); }
    size_t capacity() const noexcept { return array1.capacity(); }
    void emplace_back(T &&t1, T &&t2);
    void push_back(T &&t1, T &&t2);
    void clear() noexcept;

private:

    std::vector<T> array1;
    std::vector<T> array2;
};

template<typename T>
void Soa<T>::emplace_back(T &&t1, T &&t2) {
    array1.emplace_back(std::forward<T>(t1));
    array2.emplace_back(std::forward<T>(t2));
}

template<typename T>
void Soa<T>::push_back(T &&t1, T &&t2) {
    array1.push_back(std::forward<T>(t1));
    array2.push_back(std::forward<T>(t2));
}

template<typename T>
void Soa<T>::clear() {
    array1.clear();
    array2.clear();
}
