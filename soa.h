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

template<typename T>
class Soa final {
public:
    Soa() {}
    ~Soa() {}

    size_t size() { return array1.size(); }
    bool empty() { return array1.empty(); }
    size_t capacity() { return array1.capacity(); }

private:

    struct SoaItem {
        T item1;
        T item2;
    };

    struct SoaItemRef {
        T &item1;
        t &item2;
    };

    std::vector<T> array1;
    std::vector<T> array2;
};
