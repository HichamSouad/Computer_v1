# Computer_v1

A small polynomial-equation solver written in **C++17**. It takes a polynomial equation as input, reduces both sides to a single polynomial in standard form (`... = 0`), computes its degree, and solves it for degrees **0, 1, 2**. For degree 2, it reports real, double, or complex solutions depending on the sign of the discriminant.

This project is a classic **42-school exercise**, focusing on parsing, formal reduction, and math.

---

## Features

- Parses a polynomial equation written with terms like `c * X^n`.
- Moves everything to the left side and prints the **Reduced form** (`... = 0`).
- Detects and prints the **polynomial degree**.
- Solves the equation according to its degree:
  - **Degree 0** → "all reals are solutions" or "no solution".
  - **Degree 1** → a single real solution.
  - **Degree 2** → two real solutions, one double solution, or two complex solutions.
- Prints an error message if the degree is greater than 2 (not solveable).
- Interactive mode if no argument is provided.
- No external libraries, only the C++ standard library.

---

## Requirements

- A C++17 compiler (`g++` is used by default).
- `make`.

---

## Build

```bash
make
```

This produces the `computor` binary.

```bash
make clean
```

Removes the `computor` binary and object files.

---

## Usage

Pass the equation as a command-line argument:

```bash
./computor "5 * X^0 + 4 * X^1 = 4 * X^0"
```

If you run the program without any argument, it will prompt you to enter an equation interactively:

```bash
./computor
```

### Input format

- Use `* X^n` for each term (`c * X^n`).
- Operators `+` and `-` separate the terms.
- The equation is split on `=`.
- `X` is the variable; `^` gives the exponent (e.g. `X^2`).

---

## Examples

### Degree 0 — all real numbers are solutions

```bash
$ ./computor "5 * X^0 = 5 * X^0"

Reduced form: = 0
Polynomial degree: 0
Any real numbers are solutions.
```

### Degree 0 — no solution

```bash
$ ./computor "5 * X^0 = 4 * X^0"

Reduced form: 1 * X^0 = 0
No solution.
```

### Degree 1 — one real solution

```bash
$ ./computor "5 * X^0 + 4 * X^1 = 4 * X^0"

Reduced form: 1 * X^0 + 4 * X^1 = 0
Polynomial degree: 1
The solution is:
-0.25
```

### Degree 2 — two real solutions (Δ > 0)

```bash
$ ./computor "1 * X^0 + 0 * X^1 - 1 * X^2 = 0"

Reduced form: 1 * X^0 - 1 * X^2 = 0
Polynomial degree: 2
Discriminant is strictly positive, the two solutions are:
1
-1
```

### Degree 2 — one double solution (Δ = 0)

```bash
$ ./computor "1 * X^0 - 2 * X^1 + 1 * X^2 = 0"

Reduced form: 1 * X^0 - 2 * X^1 + 1 * X^2 = 0
Polynomial degree: 2
Discriminant is zero, the solution is:
1
```

### Degree 2 — two complex solutions (Δ < 0)

```bash
$ ./computor "5 * X^0 + 4 * X^1 + 3 * X^2 = 0"

Reduced form: 5 * X^0 + 4 * X^1 + 3 * X^2 = 0
Polynomial degree: 2
Discriminant is strictly negative, the two complex solutions are:
-2/3 - 1i/1
-2/3 + 1i/1
```

---

## How it works

1. The two sides of the equation (around `=`) are read.
2. Spacing around `+` / `-` signs is normalised and each `-` becomes `+-` so terms can be split cleanly.
3. Each term is parsed into a `(exponent, coefficient)` pair and accumulated into an ordered map (`std::map<int, double>`). Terms on the right-hand side are subtracted so everything is regrouped to the left.
4. The **reduced form** is printed from the map.
5. The degree of the polynomial is determined from the highest non-zero exponent.
6. Depending on the degree, the equation is solved:
   - Degree 0, 1: handled directly.
   - Degree 2: the discriminant `Δ = b² - 4ac` is computed and solutions are printed (real, double, or complex, with fractions simplified via GCD).
   - Degree > 2: an informative message says it cannot be solved.

---

## Project structure

```
.
├── Makefile   # build configuration
├── main.cpp   # program source code
└── README.md
```

---

## License

This project is for educational purposes as part of the 42 curriculum.