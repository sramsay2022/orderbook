# Project Name

Market order book

## Overview

This project is used to model a financial order book. It takes in orders and tries to match immedietly, if there is no match it then adds the order to a FIFO priority queue.

## Prerequisites

Ensure you have the following installed:

- **CMake** (version 3.x or higher)
- **C++ Compiler** (GCC, Clang, MSVC, etc.)
- **Make/Ninja** (for Unix-based systems)
- **Conan/vcpkg** (optional for dependency management)

## Building the Project

1. Create a build directory:
   ```sh
   mkdir -p build && cd build
   ```
2. Run CMake to generate the build system files:
   ```sh
   cmake .. -DCMAKE_BUILD_TYPE=Release
   ```
3. Compile the project:
   ```sh
   cmake --build .
   ```

## Running the Application

After a successful build, run the executable:

```sh
./todo
```

## Cleaning the Build

To remove all generated files:

```sh
rm -rf build/
```




Shared pointer is used for Orderbook because both the matching engine and the users need to be able to see it.
Unique pointer is used for the orders because once theyve been placed, they belong to the OB and cant be changed, only deleted
