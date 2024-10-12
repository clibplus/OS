#pragma once

#include <stdio.h>

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
	int		(*Write)	(struct File *p, const char *data);
	void 	(*Destruct)	(struct File *p);
} File;

//
//			| - > Create a new intanse of a file struct
//			| - > Returns a ne struct with the file upon success or an empty struct upon failure
//
File 		Openfile(const char *filepath, FILE_MODE m);

//
//			| - > Read the file content
//			| - > Returns a char with the file content upon success or NULL upon failure
//
char 		*File__Read(File *p);

//
//			| - > Write to file
//			| - > Returns 1 upon success or 0 upon failure
//
int 		Write(File *p, const char *data);

//
//			| - > Destroy the struct
//
void 		DestructFile(File *p);
