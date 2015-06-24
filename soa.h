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

template<typename T>
class ElementProxy final {
private:
    std::vector<T> *arr;
    size_t index;
public:
    ElementProxy() = delete;
    ElementProxy(std::vector<T> &v, size_t index) : arr(&v), index(index) {
    }
/*
    operator T() {
        return (*arr)[index];
    }

    operator T() const {
        return (*arr)[index];
    }
*/
    T& value() const noexcept {
        return (*arr)[index];
    }

    ElementProxy<T>& operator=(const T &other) {
        (*arr)[index] = other;
        return *this;
    }

    void swap(ElementProxy<T> &other) {
        T tmp((*arr)[index]);
        (*arr)[index] = (*other.arr)[other.index];
        (*other.arr)[other.index] = tmp;
        printf("Elementproxy swap.\n");
    }


};

namespace std {
template<typename T>
void swap(ElementProxy<T> &a, ElementProxy<T> &b) {
    a.swap(b);
}
}

template<typename T>
struct StructProxy final {
    ElementProxy<T> item1;
    ElementProxy<T> item2;

    StructProxy() = delete;
    StructProxy(const ElementProxy<T> &i1, const ElementProxy<T> &i2) :
        item1(i1), item2(i2) {
    }

    void swap(StructProxy<T> &other) {
        std::swap(item1, other.item1);
        std::swap(item2, other.item2);
        printf("StructProxy swap.\n");
    }
};

// For whatever reason, you need to have this in both std and
// regular namespaces. std::swap takes the std:: one while
// std::sort takes the other one. Weird.
namespace std {
template<typename T>
void swap(StructProxy<T> &a, StructProxy<T> &b) {
    a.swap(b);
}
}

template<typename T>
void swap(StructProxy<T> &a, StructProxy<T> &b) {
    a.swap(b);
}

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

    SoaIterator<C, T> operator=(SoaIterator<C, T> &&other) {
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

    value_type& operator*() {
        new(proxy) value_type((*container)[index]);
        return *(reinterpret_cast<value_type*>(proxy));
    }

    difference_type operator-(const SoaIterator<Soa<T>, T> &other) const {
        return index - other.index;
    }

private:
    char proxy[sizeof(value_type)];
    C *container;
    size_t index;
};

template<typename T>
struct SoaItem {
    T item1;
    T item2;
};

template<typename T>
struct SoaItemRef {
    T &item1;
    T &item2;
    SoaItemRef(T &i1, T &i2) : item1(i1), item2(i2) {
    }

    SoaItemRef(SoaItemRef<T> && other) noexcept : item1(other.item1), item2(other.item2) {
    }

    SoaItemRef(const SoaItemRef<T> &other) noexcept : item1(other.item1), item2(other.item2) {
    }

    bool operator==(const SoaItem<T> &i) const noexcept {
        return item1 == i.item1 && item2 == i.item2;
    }

    bool operator==(const SoaItemRef<T> &i) const noexcept {
        return item1 == i.item1 && item2 == i.item2;
    }

    SoaItemRef& operator=(SoaItemRef<T> &&other) noexcept {
        item1 = other.item1;
        item2 = other.item2;
        return *this;
    }

    SoaItemRef& operator=(const SoaItemRef<T> &other) noexcept {
        item1 = other.item1;
        item2 = other.item2;
        return *this;
    }

    void swap(const SoaItemRef<T> &i) {
        printf("Calling itemref swap.\n");
        T tmp;
        tmp = item1;
        item1 = i.item1;
        i.item1 = tmp;

        tmp = item2;
        item2 = i.item2;
        i.item2 = tmp;
    }
};

namespace std {
template<typename T>
void swap(SoaItemRef<T> &a, SoaItemRef<T> &b) {
    a.swap(b);
}
}

template<typename T>
void swap(SoaItemRef<T> &a, SoaItemRef<T> &b) {
    a.swap(b);
}

template<typename T>
class Soa final {
public:

    typedef SoaItemRef<T> value_type;
    typedef SoaItem<T> swap_type;

    Soa() {}
    ~Soa() {}

    size_t size() const noexcept { return array1.size(); }
    bool empty() const noexcept { return array1.empty(); }
    size_t capacity() const noexcept { return array1.capacity(); }
    void emplace_back(T &&t1, T &&t2);
    void push_back(T &&t1, T &&t2);
    void clear() noexcept;

    value_type operator[](size_t index);

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
typename Soa<T>::value_type Soa<T>::operator[](size_t index) {
    return Soa<T>::value_type(array1[index], array2[index]);
}
