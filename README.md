<p align="center">
      <img src="https://drive.google.com/uc?export=download&confirm=no_antivirus&id=1SfyN1lorIzgTlXpDrQ_nP0ssHD3r8TEd" width="500">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/Version-v1.0-blue" alt="Version">
   <img src="https://img.shields.io/badge/License-MIT-success" alt="License">
</p>

## About

A simple C++ library that allows you to perform various methods for working with Boolean algebra.

## Documentation

### Input:

- **`All unique (used at least once) variables must be arranged alphabetically and in uppercase or x0, x1, x2... You can also use constants 0 and 1. `**
- **`()`** - Parenthesis for prioritizing operations.

### Operators:

- **`!`** - NOT
- **`*`** - AND
- **`+`** - OR 
- **`^`** - XOR
- **`=`** - XNOR
- **`>`** - IMPLY
- **`|`** - NAND
- **`#`** - NOR

### Methods:

- **`Boolean::simlplify (string str)`** - Return of a simplified boolean expression.
- **`Boolean::truth_table (string str)`** - Return of the truth table by boolean expression.
- **`Boolean::result (string str)`** - Returns the result of a boolean expression table.
- **`Boolean::polynom (string str)`** - Return of the Zhegalkin polynomial by a boolean expression.

## Developers

- [Gordey Piterin](https://github.com/bogoizbranniy)
