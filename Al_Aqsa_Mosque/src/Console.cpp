#include "console.h"
#include <windows.h>
#include <iostream>
// Explicit instantiation for the char[16] type
template void Console::print<char[16]>(const char(&message)[16]);

void Console::init() {
    // AllocConsole() creates a new console for the process
    AllocConsole();

    // freopen() redirects standard input/output to the console
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

template <typename T>
void Console::print(const T& message) {
    // You can use std::cout to print to the console
    std::cout << message << std::endl;
}

// Explicit instantiation for other types if needed
template void Console::print<int>(const int& message);
template void Console::print<std::string>(const std::string& message);
// Add more explicit instantiations as needed for other types
