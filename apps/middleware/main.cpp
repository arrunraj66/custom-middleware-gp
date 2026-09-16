#include "custom_middleware/version.hpp"

#include <iostream>

int main()
{
    std::cout << "Custom Middleware GP version "
              << custom_middleware::version()
              << '\n';

    return 0;
}