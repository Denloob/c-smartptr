# C Smartptr

Header-only library, adding Go-like **defer** and C++ smartptr-like **auto-free** to C! \
*Requires gcc (-std=gnu99 or higher)*

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
    // You can specify custom destructors
    smartptr_func(user_destroy) User *my_user = user_create("Denloob");
}
```

- You can defer a function to run in the end of the scope
```c
if (x == 1) {
    pthread_mutex_lock(&mutex);
    defer({ pthread_mutex_unlock(&mutex); });

    // Do something

    // Mutex unlocked in the end of the block
}
```

- You can also defer code blocks with the variables in the scope!
```c
my_user = ...
defer({ printf("Bye %s!\n", my_user->name); });
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

## QnA

#### **Q: I compile with gcc but use `clangd` for static analysis. Will this library break clang?**

A: You can easily allow the library to "do nothing" if it detects a non compatible compiler (like clang). \
Thus clang (or any other compiler) analyzer will not break, and the gcc-compiled
code will still work as intended. \
To do this, open the header, and in the beginning, find
```c
// If you wish, you may enable for clang or any other non-gnu compiler to completely
// ignore most* smartptr/defer statements. This can be useful for example if you
// are using it as an LSP (like clangd).
// * - non-special features like smartptr_func_ptr or smartptr will still work
#if (!defined(__GNUC__) || defined(__clang__))

#if 0
#define smartptr__setting_DO_NOTHING_SPECIAL
#else
#error "Unsupported compiler"
#endif

#endif
```
Now, switch the `#if 0` to `#if 1`. \
That's it!

#### **Q: I am writing in a non-libc environment and `stdlib`/`free` breaks my compiling/linking**

A: The easiest solution is to completely disable smartptr__free. Open the header and locate
```c
// If you do not wish to have a macro `smartptr` that calls free
// (for example if you don't have libc, remove the following define)
#define smartptr__setting_SUPPORT_FREE
```
somewhere in the beginning of the file. Now simply remove the `#define` line and
you are good to go! \
All of the other smartptr and defer features will work as intended.

## Contributing
Contributions are welcome! Open an Issue or a PR with your questions/suggestions.

## License
C Smartptr is licensed under the MIT License. See [LICENSE](./LICENSE) for more details.

## Other info
Inspired by [this](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3199.htm) proposal.
