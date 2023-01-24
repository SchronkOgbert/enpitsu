#include "Screen.h"
#include <memory>
#include <iostream>

using namespace enpitsu;

int main()
{
    try
    {
        std::unique_ptr<Screen> screen(new Screen(
                std::make_tuple(800, 600),
                false,
                []() -> bool
                {
                    return false;
                }
        ));
    }
    catch (BadCustomInitException &exception)
    {
        std::cerr << exception.what();
    }
}