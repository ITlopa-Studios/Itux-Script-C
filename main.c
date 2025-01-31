// Copyright (C) 2025 ITlopa
// The Ituxalien Script compiler written in C.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

void generate_code(const char *line, FILE *output_file) {
    char var_name[BUFFER_SIZE];
    char value[BUFFER_SIZE];

    // Let type
    if (sscanf(line, "let %s = %s", var_name, value) == 2) {
        fprintf(output_file, "    int %s = %s;\n", var_name, value);
    }

    // String type
    else if (sscanf(line, "string %s = %s", var_name, value) == 2) {
        fprintf(output_file, "    const char* %s = \"%s\";\n", var_name, value);
    }

    // Print command
    else if (sscanf(line, "print %s", value) == 1) {
        fprintf(output_file, "    printf(\"%s\");\n", value);
    }
}

int main() {
    FILE *output_file = fopen("output.c", "w");
    if (!output_file) {
        perror("Failed to open output file");
        return 1;
    }

    // Start of C code
    fprintf(output_file, "// Generated by Itux Script compiler. Don't modify!\n#include <stdio.h>\n\nint main() {\n");

    char line[BUFFER_SIZE];

    while (1) {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin)) {
            break; // Exit if error
        }

        // Delete \n symbol
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "exit") == 0) {
            break;
        }

        generate_code(line, output_file);
    }

    // End C code
    fprintf(output_file, "    return 0;\n}\n");
    fclose(output_file);

    return 0;
}
