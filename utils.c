#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *ExecuteCmd(const char *cmd) {
	if(!cmd)
		return NULL;

	FILE *fd = popen(cmd, "r");
	if(!fd)
		return NULL;

	int BYTES = 0, idx = 0;
	char BUFFER[1024];
	char *data = (char *)malloc(1);
	while(fgets(BUFFER, 1023, fd) != NULL) {
		idx += strlen(BUFFER);
		data = (char *)realloc(data, idx);
		strncat(data, BUFFER, strlen(BUFFER));
		memset(BUFFER, '\0', 1023);
	}

	data[idx - 1] = '\0';
	fclose(fd);
	return data;
}
