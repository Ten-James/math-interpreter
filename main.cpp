#include <iostream>
#include "src/Program.h"

int main() {
    std::srand(std::time(nullptr));
    Program program;

    program.whileLoop();

    return 0;
}
