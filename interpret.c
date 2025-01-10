#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

// Struct for vars
typedef struct {
    char name[BUFFER_SIZE];
    int value;
} Variable;

Variable variables[100]; // Vars
int var_count = 0; // Var count

// Function for find variable
int find_variable(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1; // Don't finded
}

// Function for create or set value for variable
void set_variable(const char *name, int value) {
    int index = find_variable(name);
    if (index == -1) {
        // If var is not finded create new.
        strcpy(variables[var_count].name, name);
        variables[var_count].value = value;
        var_count++;
    } else {
        // Var finded! Set the value
        variables[index].value = value;
    }
}

// Function for get variable
int get_variable(const char *name) {
    int index = find_variable(name);
    if (index != -1) {
        return variables[index].value;
    }
    return 0; // If var is don't finded, return NULL
}

int main() {
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

        char command[BUFFER_SIZE];
        char var_name[BUFFER_SIZE];
        int value;

        // Let var type
        if (sscanf(line, "let %s = %d", var_name, &value) == 2) {
            set_variable(var_name, value);
            printf("%s = %d\n", var_name, get_variable(var_name));
        }

        // String var type
        else if (sscanf(line, "string %s = %s", var_name, line) == 2) {
            printf("%s = %s\n", var_name, line);
        }

        // Print function
        else if (sscanf(line, "print %s", var_name) == 1) {
            printf("%s\n", var_name);
        }
    }

    return 0;
}
