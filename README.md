# CCP - C Command-line argument Parser

An easy to use command-line argument parsing library for C programming language.

## Quick Start

Run Following command to build `example.c`.

```bash
make example

# then execute example
./example
```

## Build the library

Run Following command to build the library as `libccp.a` file for static linking and
all header files to be included in other projects.

```
make
```

## Known limitations

- Using Doubly Linked-lists to store flags instead of Hash-tables. (I don't know how to implement HTs in C yet)
- Bad code style and lots of duplication that can be solved with more functions and macros

