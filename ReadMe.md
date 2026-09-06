# Personal-Project

## About This Repository

This repository is my personal space for learning C++ by actually building
things, rather than just reading about them. The goal isn't to reinvent the
standard library — it's to understand *why* it's designed the way it is, by
running into the same problems it had to solve (memory management, generic
types, safe copying, growth strategies) myself, on purpose, in small,
self-contained projects.

Each project here is meant to:
- Teach a specific cluster of C++ concepts hands-on rather than in the abstract
- Be small enough to fully understand end-to-end, but real enough to be genuinely useful afterward
- Build on the previous project, so earlier lessons get reinforced rather than forgotten
- Stay interesting — data structures and language features are more fun to learn when they're in service of building something (a library, a tool, a small engine) rather than as isolated exercises

The first project in that spirit is `mylib`, described below: a custom
`Stack<T>` built from raw pointers up, with proper memory management,
generics, exceptions, and a real build/test setup around it. Future
projects in this repo will reuse `mylib` and build on top of it (for
example, using `Stack<T>` as the engine behind a small expression
parser/calculator), rather than starting from scratch each time.

# mylib - custom library
## What is `mylib`?

A small, header-only C++ library implementing a generic, dynamically-resizing
`Stack<T>` from scratch — built as a learning project to practice core C++
concepts: templates, the Rule of Three, RAII/memory management, exceptions,
and project tooling (CMake, GoogleTest).

This library is **not** meant to replace `std::stack` — it exists purely as
a hands-on way to understand how such containers work under the hood, and
as a reusable base for future learning projects.

## Features

- **Generic** — works with any type via templates (`Stack<int>`, `Stack<std::string>`, etc.)
- **Dynamically resizing** — grows automatically (capacity doubles) when full, similar to `std::vector`
- **Memory-safe** — implements the Rule of Three (destructor, copy constructor, copy assignment) for correct deep copies, no double-frees or dangling pointers
- **Exception-safe interface** — `pop()` and `peek()` throw `std::out_of_range` on an empty stack instead of reading invalid memory
- **Header-only** — just `#include "mylib/Stack.hpp"`, no separate compilation/linking step needed
- **Namespaced** (`myLib::`) to avoid collisions with `std::stack` or other libraries

## Project Structure

```
CodingConcepts/
├── include/
│   └── mylib/
│       └── Stack.hpp       # the library itself (header-only)
├── examples/
│   └── demo.cpp            # example usage / manual test program
├── tests/
│   └── test_stack.cpp      # GoogleTest unit tests
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Requirements

- A C++17-compatible compiler (GCC, Clang, or MSVC)
- CMake 3.14+
- Internet access on first build (CMake's `FetchContent` downloads GoogleTest automatically)

## Building

```bash
git clone <your-repo-url>
cd CodingConcepts

mkdir build
cd build
cmake ..
cmake --build .
```

This builds two targets:
- `demo` — a small example program exercising the stack (push/pop/peek, copying, resizing, exceptions)
- `tests` — the GoogleTest unit test suite

## Running

From the `build/` directory:

```bash
./demo            # run the example program
./tests           # run the unit test suite directly
ctest --output-on-failure   # or run tests via CTest
```

## Usage Example

```cpp
#include "mylib/Stack.hpp"
#include <iostream>

int main() {
    myLib::Stack<int> s(2);   // starts with capacity 2, grows automatically

    s.push(10);
    s.push(20);
    s.push(30);               // triggers an automatic resize

    std::cout << s.peek() << std::endl;   // 30
    std::cout << s.pop() << std::endl;    // 30
    std::cout << s.peek() << std::endl;   // 20

    try {
        myLib::Stack<int> empty(3);
        empty.pop();           // throws std::out_of_range
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
}
```

## API

| Method | Description |
|---|---|
| `Stack(int capacity)` | Construct a stack with an initial capacity |
| `void push(T value)` | Push a value onto the top; resizes automatically if full |
| `T pop()` | Remove and return the top value; throws `std::out_of_range` if empty |
| `T peek() const` | Return the top value without removing it; throws `std::out_of_range` if empty |
| `bool isEmpty() const` | Returns `true` if the stack has no elements |
| `bool isFull() const` | Returns `true` if the current internal array is at capacity (informational — `push` resizes past this automatically) |

## Using This Library In Another Project

Copy or add this repo as a submodule, then in the other project's `CMakeLists.txt`:

```cmake
add_subdirectory(CodingConcepts)
target_link_libraries(your_target PRIVATE mylib)
```

Then `#include "mylib/Stack.hpp"` and use `myLib::Stack<T>` as shown above.

## What This Project Was Built To Practice

- Class templates and out-of-class template member definitions
- The Rule of Three (destructor, copy constructor, copy assignment) and deep vs. shallow copies
- Dynamic memory management (`new[]` / `delete[]`) and why raw pointers require careful handling
- Amortized O(1) growth strategy (capacity doubling) for dynamic arrays
- Exception handling with `<stdexcept>`
- Header organization: include guards (`#pragma once`) and namespaces
- Reusable library structure with CMake (`INTERFACE` libraries, `target_include_directories`)
- Unit testing with GoogleTest (`FetchContent`, `TEST()`, `EXPECT_*`/`ASSERT_*`, `ctest`)

## License

Personal learning project — use freely.