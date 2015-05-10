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
    Soa<int>::SoaItem target{3, 3};

    auto result = std::find(foo.begin(), foo.end(), target);
    assert(std::distance(foo.begin(), result) == 2);
}

void swap_test() {
    int one=1;
    int two=2;
    int three=3;
    int four=4;
    Soa<int>::SoaItemRef i1(one, two);
    Soa<int>::SoaItemRef i2(three, four);
    std::swap(i1, i2);
    //i1.swap(i2);
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
    auto ordering = [](const Soa<int>::SoaItemRef &i1, const Soa<int>::SoaItemRef &i2) {
        if(i1.item1 < i2.item1)
            return true;
        if(i2.item1 < i1.item1)
            return false;
        if(i1.item2 < i2.item2)
            return true;
        return false;
    };
    std::sort(foo.begin(), foo.end(), ordering);
    for(const auto &i : foo) {
        printf("%d %d\n", i.item1, i.item2);
    }
    assert(foo[0].item1 == 1);
    assert(foo[3].item2 == 4);
}

void elem_test() {
    std::vector<int> foobar{0, 1, 2, 3, 4};
    ElementProxy<int> p1(foobar, 0);
    ElementProxy<int> p2(foobar, 2);
    assert(foobar[0] == 0);
    assert(foobar[2] == 2);
    assert(p1.value() == 0);
    assert(p2.value() == 2);
    std::swap(p1, p2);
    assert(p1.value() == 2);
    assert(p2.value() == 0);
    assert(foobar[0] == 2);
    assert(foobar[2] == 0);

    p1 = 44;
    assert(foobar[0] == 44);
}

void struct_test() {
    std::vector<int> v1{0, 1, 2, 3, 4};
    std::vector<int> v2{4, 3, 2, 1, 0};
    ElementProxy<int> p1(v1, 0);
    ElementProxy<int> p2(v1, 1);
    ElementProxy<int> p3(v2, 0);
    ElementProxy<int> p4(v2, 1);
    StructProxy<int> sp1(p1, p3);
    StructProxy<int> sp2(p2, p4);
    print_vector(v1);
    print_vector(v2);

    printf("\n");
    std::swap(sp1, sp2);
    print_vector(v1);
    print_vector(v2);
    assert(v1[0] == 1);
    assert(v2[0] == 3);
    assert(v1[1] == 0);
    assert(v2[1] == 4);
    assert(p1.value() == 1);
    assert(p3.value() == 3);

    sp1.item1 = 44;
    assert(p1.value() == 44);
}

void sort_test2() {
    std::vector<int> v1{0, 1, 2, 3, 4};
    std::vector<int> v2{4, 3, 2, 1, 0};
    std::vector<StructProxy<int>> combined;
    for(int i=0; i<v1.size(); i++) {
        combined.emplace_back(ElementProxy<int>(v1, i), ElementProxy<int>(v2, i));
    }
    auto ordering = [](const StructProxy<int> &p1, const StructProxy<int> &p2) {
        printf("%d %d\n", p1.item2.value(), p2.item2.value());
        return p1.item2.value() < p2.item2.value();
    };
/*
    printf("Sort test\n");
    print_vector(v1);
    print_vector(v2);
*/
    std::swap(*combined.begin(), *(combined.begin()+1));

    /*
    print_vector(v1);
    print_vector(v2);
    */
    std::sort(combined.begin(), combined.end(), ordering);
    /*
    print_vector(v1);
    print_vector(v2);
    */
    assert(v1[0] == 4);
}

int main(int, char **) {
    basic_test();
    indexing_test();
    iterator_test();
    find_test();
    elem_test();
    struct_test();
    //swap_test();
    //sort_test();
    sort_test2();
}
