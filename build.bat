@REM `bof-launcher` library is not compatible with `__declspec(dllimport)`
@REM so we define `DECLSPEC_IMPORT` to be empty.
@REM `-lc` is needed for Zig to find `windows.h`, BOF is *not* linked with libc.
zig build-obj -O ReleaseSmall -lc -D"DECLSPEC_IMPORT=" example_bof.c

zig build-exe -O ReleaseSmall -lc example_bof_runner.c bof-launcher_win_x64.lib ole32.lib ws2_32.lib
