#ifndef CONSOLE_H
#define CONSOLE_H
#include <windows.h>
#include <iostream>


/**
 * @brief Console class for initializing and interacting with the console.
 *
 * The Console class provides methods to initialize the console and print
 * messages to the console using standard input/output redirection.
 */
class Console {
public:
    /**
     * @brief Initialize the console for input and output redirection.
     *
     * The init method creates a new console for the process and redirects
     * standard input/output to the console.
     */
    static void init();

    /**
     * @brief Print a message to the console.
     *
     * The print method takes any printable object and outputs it to the console.
     *
     * @tparam T The type of the object to be printed.
     * @param message The message or object to be printed to the console.
     */
    template <typename T>
    static void print(const T& message);
};

#endif // CONSOLE_H
