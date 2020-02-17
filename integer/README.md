# Integer

## What is it?

That class is supposed to be a repacement of standard C++ integer types, when you need some profiling of your code.

Most of class methods are overloaded, so any third-party code can be put into integer types' work process.

## Examples

For example, if we want to check sorting's comparisons count, we can just put a counter into every comparison method.

Some interesting numbers about two tested sortings:

```
Generated vector size: 4096
Testing StupidBubbleSort...
StupidBubbleSort comparisons: 16773120
Testing STL sort...
STL sort comparisons: 56256
```

```
Generated vector size: 8192
Testing StupidBubbleSort...
StupidBubbleSort comparisons: 67100672
Testing STL sort...
STL sort comparisons: 125321
```
