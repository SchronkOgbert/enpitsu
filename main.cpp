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

    void init() override
    {
        Screen::init();
        std::cout << "MyScreen::init\n";
    }
};

int main()
{
    try
    {
        std::unique_ptr<MyScreen> screen(new MyScreen());
        screen->start();
        std::unique_ptr<MyScreen> screen1(new MyScreen());
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
}