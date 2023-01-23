#include "iostream"
#include "src/Screen.h"

int main()
{
    std::cout << "Hello world\n";
    std::unique_ptr<Screen> screen(new Screen(std::make_tuple(800, 600)));
}
