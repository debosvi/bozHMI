
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "nxjson.h"

#define ERROR(msg, p) fprintf(stderr, "ERROR: " msg " %s\n", (p));

extern char* load_file(const char* filepath);
extern void dump(const nx_json* json, char* out, char** end, int indent);
