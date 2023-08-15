#!/usr/bin/env bash


valgrind --leak-check=full ./a.out "$@"

