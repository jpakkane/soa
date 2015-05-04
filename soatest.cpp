#include"soa.h"
#include<cassert>

void basic() {
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

void indexing() {
    Soa<int> foo;
    foo.push_back(4, -1);
    assert(foo[0].item1 == 4);
    assert(foo[0].item2 == -1);

    auto item = foo[0];
    assert(item.item1 == 4);
    assert(item.item2 == -1);
}

int main(int, char **) {
    basic();
    indexing();
}
