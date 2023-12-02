#include <stdlib.h>
#include <stdio.h>
#include "bof.h"

int main(void) {
    FILE* fp = fopen("example_bof.obj", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Failed to load `example_bof.obj`.\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    long len = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    void* buf = malloc(len);
    if (buf == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        return 1;
    }

    if (fread(buf, 1, len, fp) != len) {
        fprintf(stderr, "Failed to read the file.\n");
        return 1;
    }
    fclose(fp);

    if (bofLauncherInit() < 0) {
        fprintf(stderr, "Failed to init bof-launcher library.\n");
    }

    BofObjectHandle bof_handle;
    if (bofObjectInitFromMemory((unsigned char*)buf, len, &bof_handle) < 0) {
        fprintf(stderr, "Failed to parse/init BOF.\n");
        return 1;
    }
    free(buf);
 
    BofContext* bof_context = NULL;
    if (bofObjectRun(bof_handle, NULL, 0, &bof_context) < 0) {
        fprintf(stderr, "Failed to run BOF.\n");
        return 1;
    }

    const char* output = bofContextGetOutput(bof_context, NULL);
    if (output) {
        printf("\n%s\n", output);
    }
    bofContextRelease(bof_context);

    bofObjectRelease(bof_handle);
    bofLauncherRelease();

    return 0;
}
