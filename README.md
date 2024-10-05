# C Smartptr

One header library, adding Go-like **defer** and C++ smartptr-like **auto-free** to C! \
*Requires gcc (-std=gnuc99 or higher)*

## Examples
- Basic malloc/free
```c
int main() {
    smartptr void *ptr = malloc(10);
    // Yep, ptr will be auto freed!
}
```

- Custom cleanup functions
```c
void user_destroy(User *user);

int main() {
    // You can specify a custom destructors
    smartptr_func(user_destroy) User *my_user = user_create("Denloob");
}
```

- You can defer a function to run in the end of the scope
```c
if (x == 1) {
    pthread_mutex_lock(&mutex);
    defer_func(pthread_mutex_unlock, &mutex);

    // Do something

    // Mutex unlocked in the end of the block
}
```

- You can also defer code blocks with arguments
```c
defer({ printf("Bye %s!\n", (*(User **)ptr)->name); }, my_user);
```

- And if you wish, you can smartptr blocks too
```c
smartptr_block({
    puts("Freeing...");
    free(*(void **)ptr); // <--- ptr is a pointer to my_num
}) int *my_num = malloc(sizeof(*my_num));
```

For more examples see [examples](./examples/) directory.
The macros are documented in the [header file](./smartptr.h)

## Installation
Copy [smartptr.h](./smartptr.h) into your project and `#include` it. That's it!
Make sure you are using `gcc`, although other compilers might work too.

## Contributing
Contributions are welcome! Open an Issue or a PR with your questions/suggestions.

## License
C Smartptr is licensed under the MIT License. See [LICENSE](./LICENSE) for more details.

## Other info
Inspired by [this](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3199.htm) proposal.
