# Structure of arrays library

This is a library that aims to provide a simple header-only implementation
of a structure of arrays. What this means is that instead of doing this:

    struct Foo {
      int x;
      std::string foo;
      FooObj bar;
    };

    std::vector<Foo> myObj;


You instead do something like this:

    Soa<int, std::string, FooObj> myObj;

Which creates an object roughly equivalent to this:

    class Soa {
        std::vector<int> x;
        std::vector<std::string> foo;
        std::vector<FooObj> bar;
    };

With all the necessary legwork of iterators and so on. The reason to
do this is that it improves cache locality and removes struct "holes"
as all arrays are of one elementary type only.

# Contributing

For various reasons I need to keep the copyright on this code all
to myself. This means that in order to accept patches I would need
to do all the legal stuff of copyright assignments and all that.
I have no interest in that so therefore submissions from third parties
are not accepted. Sorry. Feel free to fork the code on your own, though.

# API stability

There is none.

Under **no** circumstances should you expose this in your public
headers.

# Contact

jpakkane at gmail dot com
