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
