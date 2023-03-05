//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_EXCEPTION_H
#define ENPITSU_EXCEPTION_H

#include "defines.h"

namespace enpitsu
{
    class Exception : public std::exception
    {
        std::string whatText;
    public:
        Exception() = delete;

        Exception(const std::string &what)
        {
            this->whatText = what;
        }

        Exception(const std::string &&what) : Exception(what)
        {}

        Exception(const char *what) : Exception(std::string(what))
        {}

        [[nodiscard]] const char *what() const noexcept override
        {
            return this->whatText.c_str();
        }
    };
}
#endif //ENPITSU_EXCEPTION_H
