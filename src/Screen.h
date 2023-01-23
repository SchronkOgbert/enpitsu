//
// Created by weekendUM on 1/23/2023.
//

#ifndef ENPITSU_SCREEN_H
#define ENPITSU_SCREEN_H

class Screen
{
public:
    Screen() = delete;
    explicit Screen(const std::tuple<int, int>& size, const bool& fullScreen = false);
};

#endif //ENPITSU_SCREEN_H
