# Linked List Library for C

## Description

This library provides a comprehensive set of functions for creating and managing linked lists in C.

## Features

- Create a new linked list
- Add elements to the linked list
- Remove elements from the linked list
- Search for elements in the linked list

## Installation

- Go to the directory where you want to install the library. From now on, this directory will be referred to as `INSTALL_DIR`.
- Clone the repository using the following command:

```bash
git clone https://github.com/florjandule/llist.git
```

### Using CMake

- Add the subdirectory to your CMakeLists.txt file by adding the following line:
`add_subdirectory(INSTALL_DIR/llist)`
- Link the library to your target by adding the following line:
`target_link_libraries(basic_demo LLISTLIB)`


### Other Build Systems

For other build systems, you can include the source files in your project.
`llist.h` and `llist.c` are the only files you need to include in your project.

## Usage

Please refer to the [samples](samples) directory for examples on how to use the library.

## Contributing

Contributions are welcome. Please open an issue or submit a pull request.

## License

See [LICENSE](LICENSE)
