# rot
rot is a little command line toy that allows you to rotate a string of text, like a ceasar cipher!

## Installation
Simply download the c file and the compile with gcc.

## Use
rot can either be used from standard input or being passed a command line argument.

Example 1:
```
> echo hello world | rot -o 1
gdkkn vnqkc
```

Example 2:
```
> rot -o 1 -r "gdkkn vnqkc"
hello world
```
