//
// Created by weekendUM on 1/27/2023.
//

#include "Object2D.h"
#include "Screen.h"

void enpitsu::Object2D::draw()
{
    screen;
}

enpitsu::Object2D::Object2D(enpitsu::Screen *screen, const std::vector<Vector2> &points, bool isStatic) : Object(screen)
{

}
