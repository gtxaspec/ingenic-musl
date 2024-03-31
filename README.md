# Musl Compatibility Shim for Ingenic Libraries

## Overview

This project provides a compatibility shim to enable Ingenic libraries, such as `libimp`, to work seamlessly with the musl compiler. It serves to bridge compatibility issues and facilitate the development of applications on Ingenic platforms using musl as the standard C library.

## Features

- Compatibility layer for Ingenic libraries to work with musl
- Supports various Ingenic libraries, including `libimp`
- Easy integration into existing projects

## Getting Started

### Prerequisites

- An Ingenic-based platform
- The musl compiler installed on your system

### Adding as a Submodule

To use this compatibility shim in your project, it's recommended to add it as a Git submodule. This approach helps in keeping the shim up to date with the latest changes.

1. Navigate to your project's root directory.
2. Run the following command to add this repository as a submodule:

```sh
git submodule add https://github.com/gtxaspec/ingenic_musl
git submodule update --init --recursive
```

### Using the Object File

1. Include the path to the musl compatibility shim source file in your project's compilation sources.
2. Compile the shim along with your project, ensuring the object file (`musl_shim.o`) is linked into the final executable.

Example for a Makefile:

```makefile
SOURCES += path/to/ingenic_musl/musl_shim.c
OBJECTS = $(SOURCES:.c=.o)

# Your usual build rules here

$(TARGET): $(OBJECTS)
    $(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@
```

### Usage

With the musl compatibility shim added to your project, you can now utilize Ingenic libraries as if they were native musl libraries. The compatibility shim handles the functions missing from musl.

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests through GitHub.

## License

This project is licensed under the MIT License
