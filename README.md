# How to write and run a simple BOF

This repository contains example C code that shows how to write and run a simple BOF (Beacon Object File) using our [bof-launcher](https://github.com/The-Z-Labs/bof-launcher) library.

The only dependency is the [Zig package](https://ziglang.org/download/) which we use here as a zero-dependency, drop-in C/C++ compiler that supports cross-compilation out-of-the-box. Download the package, add it to the `PATH` and you are ready to go.

To build this project just run `build.bat` script. This script will build both, an example BOF and an example BOF runner. Let's take a look at it here:

```bat
@REM STEP 1.
@REM Build example BOF with `zig build-obj`.
@REM
@REM `bof-launcher` library is not compatible with `__declspec(dllimport)` so we define
@REM `DECLSPEC_IMPORT` to be empty.
@REM `-lc` is needed for Zig to find `windows.h`, BOF is *not* linked with libc (but can still use it).
@REM
zig build-obj -O ReleaseSmall -target x86_64-windows-gnu -lc -D"DECLSPEC_IMPORT=" example_bof.c

@REM STEP 2.
@REM Build example BOF runner with `zig cc` (which is basically a standalone, zero-dependency `clang` with
@REM cross-compilation working out-of-the-box).
@REM
zig cc -lc -mcpu=x86_64 -o example_bof_runner.exe example_bof_runner.c bof-launcher_win_x64.lib ole32.lib ws2_32.lib
```
