#include"soa.h"
#include<cassert>
#include<algorithm>

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

void iterator() {
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

void find() {
    Soa<int> foo;
    foo.push_back(1, 1);
    foo.push_back(2, 2);
    foo.push_back(3, 3);
    foo.push_back(4, 4);
    Soa<int>::SoaItem target{3, 3};

    auto result = std::find(foo.begin(), foo.end(), target);
    assert(std::distance(foo.begin(), result) == 2);
}

int main(int, char **) {
    basic();
    indexing();
    iterator();
    find();
}
