#ifndef LEAKS_H
# define LEAKS_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static inline void* __calloc(size_t size, size_t count, const char* file, int line, const char* function)
{
	int fd = open("adrress_logs.py", O_CREAT | O_RDWR | O_TRUNC, 0644);
	FILE *log = fopen("adrress_logs.py", "a");
    void* ptr = calloc(size, count);
    if (ptr != NULL)
        fprintf(log,"Memory allocated at address: %p, file: %s, line: %d function %s\n", ptr, file, line, function);
    else
        fprintf(log, "Failed to allocate memory at file: %s, line: %d\n", file, line);
	fclose(log);
	close(fd);
    return ptr;
}

static inline void __free(void *ptr, const char* file, int line)
{
	int fd = open("adrress_logs.py", O_CREAT | O_RDWR, 0644);
	FILE *log = fopen("adrress_logs.py", "a");
	fprintf(log,"Memory freed from address: %p, file: %s, line: %d\n", ptr, file, line);
	fclose(log);
	close(fd);
}

#ifndef calloc
#define calloc(count , size) __calloc(size , count, __FILE__, __LINE__, __FUNCTION__)
#endif

#ifndef free
#define free(ptr) __free(ptr, __FILE__, __LINE__)
#endif

#endif
