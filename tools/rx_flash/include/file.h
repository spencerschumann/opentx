#pragma once

typedef char TCHAR;
typedef unsigned char	BYTE;
typedef unsigned int	UINT;
typedef size_t FSIZE_t;

typedef struct {
	struct {
        FSIZE_t objsize;
        uint8_t *data;
    } obj;
	FSIZE_t	fptr;			/* File read/write pointer (Zeroed on file open) */
} FIL;

typedef enum {
	FR_OK = 0,
    FR_ERR = 1
} FRESULT;

#define	FA_READ				0x01

FRESULT f_open (FIL * fil, const TCHAR *name, BYTE flag);
FRESULT f_read (FIL* fil, void* data, UINT size, UINT* read);
FRESULT f_close (FIL * fil);
