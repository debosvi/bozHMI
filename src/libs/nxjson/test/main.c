
#include "nxjson_test.h"

int main(int ac, char **av) {
    char infile[32];
    int i;
    for (i = 1; i < 2; i++) {
        sprintf(infile, "samples/%03d.json", i);
        char *input = load_file(infile);
        if (!input)
            break;
        const nx_json *json = nx_json_parse_utf8(input);
        char *buf = malloc(strlen(input) * 32 + 4000000);        // hope this will be large enough; depends on nesting & indenting
        char *p = buf;
        dump(json, p, &p, 0);
        nx_json_free(json);
        free(input);
        fprintf(stderr, "result: \n%s\n", buf);
        free(buf);
    }

    exit(EXIT_SUCCESS);
}
