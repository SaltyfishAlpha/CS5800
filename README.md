# LeetCode Practice Framework (C++ / CMake)

This repo is set up to practice LeetCode problems locally with:

- One **subdirectory per problem** under `problems/`
- A **LeetCode-style `Solution`** implementation in `solution.cpp`
- A tiny `main.cpp` wrapper using a macro that **redirects stdin from an input file**, so you can read using **`cin` / `getline(cin, ...)` / `scanf`**, and write using **`cout` / `printf`**
- **Auto-discovery** of problems in CMake (no need to edit `CMakeLists.txt` per problem)

---

## Project layout

```
CS5800/
  CMakeLists.txt
  leetcode_runner.h
  problems/
    template/
      main.cpp
      solution.cpp
      input.txt
    two-sum/
      main.cpp
      solution.cpp
      input.txt
      input2.txt
```

---

## How it works

### Input file → stdin redirection

The macro in `leetcode_runner.h` opens:

`problems/<problem-name>/<input-file>`

and redirects it to **stdin** using `freopen(...)`. That means:

- You **do not** open any file in `main.cpp`
- You just read from stdin using `cin`, `getline(cin, ...)`, or `scanf`

### Finding input files after build

CMake defines `SOURCE_DIR` for each problem target, so input files are found correctly even when running from `cmake-build-*`.

---

## Building & running

### In CLion

- Reload CMake
- Select a target like `two-sum`
- Run / Debug

### From command line (PowerShell)

If you use the CLion default build folder:

```powershell
cmake -S . -B cmake-build-debug
cmake --build cmake-build-debug --target two-sum
.\cmake-build-debug\problems\two-sum\two-sum.exe
```

---

## Adding a new problem (recommended workflow)

1. Copy `problems/template` to a new folder:
   - Example: `problems/0001-two-sum/` or `problems/two-sum/`
2. Edit `problems/<your-problem>/solution.cpp` to match LeetCode style:
   - Keep it like the website (class `Solution { ... }`)
3. Edit `problems/<your-problem>/main.cpp` to:
   - Choose the input file
   - Parse stdin
   - Call `solution.yourMethod(...)`
   - Print output
4. Put test cases in `problems/<your-problem>/input.txt` (and `input2.txt`, etc.)

No `CMakeLists.txt` edits are required as long as the folder contains `main.cpp`.

---

## `LEETCODE_MAIN_BEGIN` macro

Defined in `leetcode_runner.h`.

### Default input file

```cpp
LEETCODE_MAIN_BEGIN("two-sum")
    // read from stdin
LEETCODE_MAIN_END
```

This defaults to `input.txt`.

### Custom input file

```cpp
LEETCODE_MAIN_BEGIN("two-sum", "input2.txt")
    // read from stdin
LEETCODE_MAIN_END
```

---

## Notes & tips

- **`cin >> x` vs `getline(cin, s)`**
  - `cin >> s` reads a token (stops at whitespace)
  - `getline` reads the whole line (good for inputs like `[1, 2, 3]` with spaces)
- **Speed**
  - If you use `cin` heavily, add at the start of your code block:
    - `ios::sync_with_stdio(false);`
    - `cin.tie(nullptr);`

