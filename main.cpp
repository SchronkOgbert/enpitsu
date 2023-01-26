#include "App.h"
#include <iostream>

int main()
{
    std::unique_ptr<App> app(new App());
    try
    {
        app->run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what();
    }
    std::cout << "end program\n";
}