#pragma once

#include <stdio.h>
#include <clibs.h>

typedef enum FILE_MODE {
	FILE_READ 			= 0x04001,
	FILE_WRITE 			= 0x04002,
	FILE_APPEND			= 0x04003,
	FILE_READ_WRITE		= 0x04004,
	FILE_WRITE_READ		= 0x04005,
	FILE_APPEND_READ	= 0x04006
} FILE_MODE;

typedef struct File {
	char 	*path;
	FILE	*fd;

	char 	*data;
	long	idx;

	char	*(*Read)	(struct File *p);
} File;

//
//
//
//
File Openfile(const char *filepath, FILE_MODE m);

//
//
//
//
char *File__Read(File *p);
