#include "App.h"
#include <iostream>

int main()
{
    std::unique_ptr<App> app(new App());
    app->run();
    std::cout << "end program\n";
}