#include"soa.h"
#include<cassert>
#include<algorithm>
#include<cstdio>

void print_vector(const std::vector<int> &v) {
    for(const auto &i : v) {
        printf("%d ", i);
    }
    printf("\n");
}

void basic_test() {
    Soa<int> foo;
    assert(true);
    assert(foo.size() == 0);
    foo.emplace_back(2, 3);
    assert(foo.size() == 1);
    foo.push_back(100, 100);
    assert(foo.size() == 2);
    assert(!foo.empty());
    foo.clear();
    assert(foo.size() == 0);
    assert(foo.empty());
}

void indexing_test() {
    Soa<int> foo;
    foo.push_back(4, -1);
    assert(foo[0].item1 == 4);
    assert(foo[0].item2 == -1);

    auto item = foo[0];
    assert(item.item1 == 4);
    assert(item.item2 == -1);
}

void iterator_test() {
    Soa<int> foo;
    assert(foo.begin() == foo.end());
    foo.push_back(4, 4);
    auto start = foo.begin();
    auto stop = foo.end();
    assert(start != stop);
    assert(!(start == stop));
    start++;
    assert(start == stop);
}

void find_test() {
    Soa<int> foo;
    foo.push_back(1, 1);
    foo.push_back(2, 2);
    foo.push_back(3, 3);
    foo.push_back(4, 4);
    Soa<int>::swap_type target{3, 3};

    auto result = std::find(foo.begin(), foo.end(), target);
    assert(std::distance(foo.begin(), result) == 2);
}

void swap_test() {
    int one=1;
    int two=2;
    int three=3;
    int four=4;
    Soa<int>::value_type i1(one, two);
    Soa<int>::value_type i2(three, four);
    std::swap(i1, i2);
    assert(i1.item1 == 3);
    assert(i1.item2 == 4);
    assert(i2.item1 == 1);
    assert(i2.item2 == 2);
}

void sort_test() {
    Soa<int> foo;
    foo.push_back(4, 4);
    foo.push_back(2, 2);
    foo.push_back(1, 1);
    foo.push_back(3, 3);
    auto ordering = [](const Soa<int>::value_type &i1, const Soa<int>::value_type &i2) {
        if(i1.item1 < i2.item1)
            return true;
        if(i2.item1 < i1.item1)
            return false;
        if(i1.item2 < i2.item2)
            return true;
        return false;
    };
    std::sort(foo.begin(), foo.end(), ordering);
/*
    for(const auto &i : foo) {
        printf("%d %d\n", i.item1, i.item2);
    }
    */
    assert(foo[0].item1 == 1);
    assert(foo[0].item2 == 1);
    assert(foo[3].item2 == 4);
}

int main(int, char **) {
    basic_test();
    indexing_test();
    iterator_test();
    find_test();
    swap_test();
    sort_test();
}
