#include "autoptr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
} User;

void user_destroy(User *u)
{
    puts("---");
    printf("Freeing %s\n", u->name);
    puts("---");
    free(u->name);
    free(u);
}
User *user_create(char *name)
{
    User *u = malloc(sizeof(*u));
    u->name = strdup(name);
    return u;
}

int main(int argc, char *argv[])
{
    // Will be freed automatically.
    autoptr int *my_num = malloc(sizeof(*my_num));

    // In the end will automatically call user_destroy with my_user
    autoptr_func(user_destroy) User *my_user = user_create("Denloob");

    // Will print `Hello, Denloob and the World!`
    defer({ printf("World!\n"); });
    defer({ printf("%s and the ", (*(User **)ptr)->name); }, my_user);
    printf("Hello, ");


    /* The complete output is:
```
Hello, Denloob and the World!
---
Freeing Denloob
---
```
    */

    return EXIT_SUCCESS;
}
