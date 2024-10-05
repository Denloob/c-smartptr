#include "smartptr.h"
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
    // smartptr will ensure `free` is called on my_num before return
    smartptr int *my_num = malloc(sizeof(*my_num));

    if (1) {
        // smartptr/defer is scope based
        smartptr int *my_other_num = malloc(sizeof(*my_other_num));

        // my_other_num is freed here
    }

    // You can use custom function!
    // This will call user_destroy with my_user before return
    smartptr_func(user_destroy) User *my_user = user_create("Denloob");

    // smartptr/defer run LIFO style
    // Will print `Hello, Denloob and the World!`
    defer({ printf("World!\n"); });
    defer({ printf("%s and the ", (*(User **)ptr)->name); }, my_user);
    printf("Hello, ");


    /* The complete output is:

Hello, Denloob and the World!
---
Freeing Denloob
---

    */

    // More documentation is located in comments in smartptr.h

    return EXIT_SUCCESS;
}
