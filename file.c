#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"
#include <clibs.h>

File Openfile(const char *filepath, FILE_MODE m) {
	if(!(int)m < 0x04001)
		return (File){ .path = NULL, .fd = NULL, .idx = 0 };

	File p = {
		.path 	= (char *)filepath,
		.idx	= 0,
		.Read	= File__Read
	};

	const char *mode;
	switch((int)m) {
		case FILE_READ: 		{ mode = "r"; }
		case FILE_WRITE: 		{ mode = "w"; }
		case FILE_APPEND: 		{ mode = "a"; }
		case FILE_READ_WRITE: 	{ mode = "r+"; }
		case FILE_WRITE_READ: 	{ mode = "w+"; }
		case FILE_APPEND_READ:	{ mode = "a+"; }
	}

	p.fd = fopen(filepath, mode);
	if(!p.fd)
		return (File){ .path = NULL, .fd = NULL, .idx = 0 };

	return p;
}

char *File__Read(File *p) {
	if(!p || !p->fd)
		return NULL;

	fseek(p->fd, 0L, SEEK_END);
	long sz = ftell(p->fd);
	fseek(p->fd, 0L, SEEK_SET);

	p->data = (char *)malloc(sz);
	if(!p->data)
		return (char *)FAILED_TO_ALLOCATE_CHAR;

	fread(p->data, sz, 1, p->fd);

	return p->data;
}

int Write(File *p, const char *data) {
	if(!p || !p->fd)
		return 0;

	fprintf(p->fd, "%s", data);
	return 1;
}

void DestructFile(File *p) {
	if(!p)
		return;

	if(p->path)
		free(p->path);

	if(p->fd)
		fclose(p->fd);

	if(p->data)
		free(p->data);

	free(p);
}
