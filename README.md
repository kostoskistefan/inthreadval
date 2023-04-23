# Inthreadval

Inthreadval is a simple cross-platform C library for executing user defined functions at regular intervals. It provides a convenient way to run background tasks in a separate thread, without blocking the main thread of the program.

## Example

The following example consists of the following steps:

 1. Create a new Inthreadval instance that will call the `callback` function each second (defined by `INTERVAL_IN_MILLISECONDS`)
 2. Starts the thread 
 3. Puts the main thread to sleep for 5 seconds, while the other thread keeps running at regular intervals
 4. After the 5 second sleep, the thread is stopped
 5. The Inthreadval instance is destroyed to free the memory

```c
#ifdef __unix__
    #include <unistd.h>
#elif __WIN32
    #include <windows.h>
    #define sleep(x) Sleep(x)
#endif

#define INTERVAL_IN_MILLISECONDS 1000 // 1000 milliseconds = 1 second

void callback(void)
{
    printf("inthreadval::info: Hello, world!\n");
}

int main(int argc, char *argv[])
{
    Inthreadval *inthreadval = inthreadval_create(callback, INTERVAL_IN_MILLISECONDS);

    inthreadval_start(inthreadval);
    sleep(5);
    inthreadval_stop(inthreadval);

    inthreadval_destroy(inthreadval);

    return 0;
}
```

## License

The Inthreadval is licensed under the MIT License. See `LICENSE` for details.
