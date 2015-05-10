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
class Soa;

template<typename C, typename T>
class SoaIterator final {

public:

    typedef typename C::value_type value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t difference_type;
    typedef std::random_access_iterator_tag iterator_category;

    SoaIterator(C &container, size_t index) : container(&container), index(index) {
    }

    SoaIterator(const SoaIterator<C, T> &other) {
        container = other.container;
        index = other.index;
    }

    SoaIterator(SoaIterator<C, T> &&other) {
        container = other.container;
        index = other.index;
        other.container = nullptr;
        other.index = -1;
    }

    bool operator==(const SoaIterator<C, T> &other) const {
        return index == other.index;
    }

    bool operator!=(const SoaIterator<C, T> &other) const {
        return !(*this == other);
    }

    bool operator<(const SoaIterator<C, T> &other) const {
        return index < other.index;
    }

    bool operator>(const SoaIterator<C, T> &other) const {
        return index > other.index;
    }

    bool operator>=(const SoaIterator<C, T> &other) const {
        return index >= other.index;
    }

    bool operator<=(const SoaIterator<C, T> &other) const {
        return index <= other.index;
    }

    SoaIterator<C, T> operator=(const SoaIterator<C, T> &other) {
        this->index = other.index;
        return *this;
    }

    SoaIterator<C, T>& operator+=(difference_type diff) {
        index += diff;
        return *this;
    }

    SoaIterator<C, T>& operator++() {
        index++;
        return *this;
    }

    SoaIterator<C, T> operator++(int) {
        SoaIterator<C, T> old(*this);
        index++;
        return old;
    }

    SoaIterator<C, T>& operator--() {
        index--;
        return *this;
    }

    SoaIterator<C, T> operator--(int) {
        SoaIterator<C, T> old(*this);
        index--;
        return old;
    }

    SoaIterator<C, T> operator+(int i) const {
        SoaIterator<C, T> rval(*this);
        rval.index += i;
        return rval;
    }

    value_type operator*() {
        return (*container)[index];
    }

    difference_type operator-(const SoaIterator<Soa<T>, T> &other) const {
        return index - other.index;
    }
/*
    void swap(SoaIterator<C, T> &other) {
        Soa<C>::SoaItem tmp = (*container)[index];
        (*container)[index] = (*other.container)[other.index];
        (*other.container)[other.index] = tmp;
    }
*/
private:
    C *container;
    size_t index;
};

template<typename T>
class Soa final {
public:

    struct SoaItem {
        T item1;
        T item2;
    };

    struct SoaItemRef {
        T &item1;
        T &item2;
        SoaItemRef(T &i1, T &i2) : item1(i1), item2(i2) {
        }

        bool operator==(const SoaItem &i) const {
            return item1 == i.item1 && item2 == i.item2;
        }

    };

    typedef SoaItemRef value_type;

    Soa() {}
    ~Soa() {}

    size_t size() const noexcept { return array1.size(); }
    bool empty() const noexcept { return array1.empty(); }
    size_t capacity() const noexcept { return array1.capacity(); }
    void emplace_back(T &&t1, T &&t2);
    void push_back(T &&t1, T &&t2);
    void clear() noexcept;

    SoaItemRef operator[](size_t index);

    SoaIterator<Soa<T>, T> begin() {
        return SoaIterator<Soa<T>, T>(*this, 0);
    }

    SoaIterator<Soa<T>, T> end() {
        return SoaIterator<Soa<T>, T>(*this, array1.size());
    }

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
void Soa<T>::clear() noexcept {
    array1.clear();
    array2.clear();
}

template<typename T>
typename Soa<T>::SoaItemRef Soa<T>::operator[](size_t index) {
    return SoaItemRef(array1[index], array2[index]);
}
