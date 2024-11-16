#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file.h"

File SetFileMethod(File *x);
File Openfile(const char *filepath, FILE_MODE m) {
	if((int)m < 16385 && (int)m > 16390)
		return SetFileMethod(&(File){ .path = NULL, .fd = NULL, .idx = 0 });

	File p = {
		.path 		= strdup(filepath),
		.idx		= 0,
		.Read		= File__Read,
		.Write 		= File__Write,
		.Destruct 	= DestructFile
	};

	const char *mode;
	switch(m) {
		case FILE_READ: 		{ mode = "r"; break; }
		case FILE_WRITE: 		{ mode = "w"; break; }
		case FILE_APPEND: 		{ mode = "a"; break; }
		case FILE_READ_WRITE: 	{ mode = "r+"; break; }
		case FILE_WRITE_READ: 	{ mode = "w+"; break; }
		case FILE_APPEND_READ:	{ mode = "a+"; break; }
	}

	p.fd = fopen(filepath, mode);
	if(!p.fd)
		return SetFileMethod(&(File){ .path = NULL, .fd = NULL, .idx = 0 });

	return p;
}

File SetFileMethod(File *x) {
	x->Read		= File__Read;
	x->Write 	= File__Write;
	x->Destruct = DestructFile;

	return *x;
}

char *File__Read(File *p) {
	if(!p || !p->fd)
		return NULL;

	fseek(p->fd, 0L, SEEK_END);
	p->idx = ftell(p->fd);
	fseek(p->fd, 0L, SEEK_SET);

	p->data = (char *)malloc(p->idx + 1);
	memset(p->data, '\0', p->idx + 1);
	if(!p->data)
		return NULL;

	fread(p->data, p->idx, 1, p->fd);

	return p->data;
}

int File__Write(File *p, const char *data) {
	if(!p || !p->fd)
		return 0;

	fprintf(p->fd, "%s", data);
	fflush(p->fd);
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
}