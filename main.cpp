#include "Screen.h"
#include <memory>
#include <iostream>

using namespace enpitsu;

class MyScreen : public Screen
{
public:
    MyScreen() : Screen(std::make_tuple(800, 600))
    {

    }
};

int main()
{
    std::unique_ptr<Screen> screen(nullptr);
    try
    {
        screen = std::make_unique<Screen>(
                std::make_tuple(800, 600)
                );
        screen->start();
    }
    catch (BadCustomInitException &exception)
    {
        std::cerr << exception.what();
    }
    catch (BadProcessCreation &exception)
    {
        std::cerr << exception.what();
    }
    catch (Exception &exception)
    {
        std::cerr << exception.what();
    }
    std::cout << "end program\n";
}