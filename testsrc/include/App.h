//
// Created by weekendUM on 1/26/2023.
//

#ifndef ENPITSU_APP_H
#define ENPITSU_APP_H

#include "AScreen.h"


class App
{
    std::shared_ptr<AScreen> screen;
public:
    App();

    void run();
};


#endif //ENPITSU_APP_H
