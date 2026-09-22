# Competitive Programming Repository

A personal collection of competitive programming solutions, algorithms, data structures, templates, and utilities developed through ICPC and other programming contests.

The repository is primarily written in C++, with a few Python tools for testing and development.

## Repository Structure

The code is organized broadly by subject:

```text
├── Bitmasks/
├── Classic problems/
├── Data structures/
├── Extra stuff/
├── Geometry/
├── Graph/
├── Math/
├── Others (untested)/
├── Strings/
├── pendiente/
├── base.cpp
├── tester.py
└── mixed facts.txt
```

The folders contain solutions and implementations covering common competitive-programming topics, while `pendiente/` contains problems and ideas that still need further work.

## Base Template

`base.cpp` contains my standard C++ template used as a starting point for contest solutions.

It includes commonly used aliases, macros, fast I/O setup, random-number generation, and GNU PBDS support.

## Testing Utility

`tester.py` is a small differential-testing utility for comparing two solutions against automatically generated test cases.

It can be used to find counterexamples when developing or debugging contest solutions.

## Notes and References

The repository also contains miscellaneous reference material, including mathematical formulas, implementation notes, and configuration information that can be useful during contests.

## Status

This is an evolving collection rather than a formally maintained library. Some implementations have been used and tested extensively, while others are experimental or have not yet been fully verified.

For that reason, individual files should be evaluated independently before being used in a contest or another project.
