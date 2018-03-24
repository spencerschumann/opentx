#include "opentx.h"
#include <stdio.h>

FRESULT f_open (FIL * fil, const TCHAR *name, BYTE flag) {
    FILE *f = NULL;
    fil->obj.objsize = 0;
    fil->obj.data = NULL;
    fil->fptr = 0;
    FRESULT result = FR_ERR;

    f = fopen(name, "r");
    if (!f) {
        printf("ERROR: could not open file %s\n", name);
        goto cleanup;
    }

    fseek(f, 0L, SEEK_END);
    fil->obj.objsize = ftell(f);
    rewind(f);

    // Limit size to 1 MB to prevent overly large malloc
    if (fil->obj.objsize > 1024 * 1024 * 1024) {
        printf("ERROR: file size of %s is above maximum threshold of 1 MB.\n", name);
        goto cleanup;
    }

    fil->obj.data = (uint8_t*)malloc(fil->obj.objsize);

    // Read the entire file now. The firmware update files
    // are small, and reading them all at once avoids potential
    // file read errors or delays during the update.
    if (fread(fil->obj.data, fil->obj.objsize, 1, f) != 1) {
        printf("ERROR: could not read entire file %s\n", name);
        goto cleanup;
    }

    result = FR_OK;

cleanup:
    if (result != FR_OK) {
        free(fil->obj.data);
        fil->obj.data = NULL;
    }
    if (f) {
        fclose(f);
    }
    return result;
}

FRESULT f_read (FIL* fil, void* data, UINT size, UINT* read) {
    if ((fil->fptr + size) > fil->obj.objsize) {
        // Trying to read more than what's available; just return the rest.
        size = fil->obj.objsize - fil->fptr;
    }
    if (size > 0) {
        memcpy(data, fil->obj.data + fil->fptr, size);
        fil->fptr += size;
        *read = size;
    }
    return FR_OK;
}

FRESULT f_close (FIL * fil) {
    free(fil->obj.data);
    fil->obj.data = NULL;
    return FR_OK;
}
