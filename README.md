# DynamicArray
A custom implementation of std::vector featuring manual memory management,
support for move semantics, mutable and const iterators.

### Features
- Copy and move constructors and assignment (rule of five)
- Forward and reverse iterators (mutable and const)
- GoogleTest unit tests
- Github CI configured

### Future work
- Refactor iterators to be STL-style, not Java-style
- Implement reserve(), resize(), clear(), emplace_back()