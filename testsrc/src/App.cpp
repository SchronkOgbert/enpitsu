//
// Created by weekendUM on 1/26/2023.
//

#include "App.h"
#include <memory>
#include <iostream>

using namespace enpitsu;

App::App()
{
    try
    {
        screen = std::make_unique<AScreen>();
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
    std::cout << "Created window\n";
}

void App::run()
{
    std::cout << "Running window\n";
    screen->start(); // program run
}
