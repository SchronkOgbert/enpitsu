//
// Created by weekendUM on 1/26/2023.
//

#ifndef ENPITSU_ASCREEN_H
#define ENPITSU_ASCREEN_H

#include "Screen.h"


class AScreen : public enpitsu::Screen
{
public:
    AScreen() : enpitsu::Screen(std::make_tuple(800, 600))
    {}

    void init() override;
};


#endif //ENPITSU_ASCREEN_H
