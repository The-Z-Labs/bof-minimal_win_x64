# How to write and run a simple BOF

This repository contains example C code that shows how to write, build and run a simple BOF ([Beacon Object File](https://hstechdocs.helpsystems.com/manuals/cobaltstrike/current/userguide/content/topics/beacon-object-files_main.htm)) using our [bof-launcher](https://github.com/The-Z-Labs/bof-launcher) library.

The only dependency is the [Zig package (0.13.0)](https://ziglang.org/download/) which we use here as a zero-dependency, drop-in C/C++ compiler that supports cross-compilation out-of-the-box. Download the package, add it to the `PATH` and you are ready to go.

To build this project just run `build.bat` script. This script will build both, an example BOF and an example BOF runner. Let's take a look at it here:

```bat
@REM STEP 1.
@REM Build example BOF with `zig build-obj`.
@REM
@REM `-lc` is needed for Zig to find `windows.h` but BOF itself *is not* linked with libc (but can still use it).
@REM
zig build-obj -O ReleaseSmall -target x86_64-windows-gnu -lc example_bof.c

@REM STEP 2.
@REM Build example BOF runner with `zig cc` (which is basically a standalone, zero-dependency `clang` with
@REM cross-compilation working out-of-the-box).
@REM
zig cc -lc -mcpu=x86_64 -o example_bof_runner.exe example_bof_runner.c bof-launcher_win_x64.lib -lole32 -lws2_32
```

After running the script two files will be generated:

    example_bof.obj
    example_bof_runner.exe

The first one is our BOF. It weights only 923 bytes and prints Windows version to its output. The second one is an example BOF runner which can load and execute any BOF using our [bof-launcher](https://github.com/The-Z-Labs/bof-launcher) library.

To run example BOF, do:

```
.\example_bof_runner.exe .\example_bof.obj
```

On my machine the output looks like:

```
<bof-filename>: .\example_bof.obj
File size is: 923
Running BOF from command line C application...

======== BOF OUTPUT ========
Windows version: 10.0, OS build number: 22631
============================
```
