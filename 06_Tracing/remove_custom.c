#include <dlfcn.h>
#include <string.h>

typedef int (*remove_type)(const char *);

int remove(const char *str) {
	if (strncmp(str, "PROTECT", 7) != 0) {
		((remove_type)(dlsym(RTLD_NEXT, "remove")))(str);
	}
	return 0;
}
