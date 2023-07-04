#ifndef ENPITSU_WRAPPER_H
#define ENPITSU_WRAPPER_H

#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/Exception.h"
#include <concepts>
#include <cstdarg>
#include <functional>

namespace enpitsu
{

    class GLError : public Exception
    {
    public:
        using Exception::Exception;
    };

    template<class Function, class ...Args>
    void callGLFunction(Function *function, Args ...args)
    {
        function(args...);
        auto error = glGetError();
        PLOGD_IF(error != GL_NO_ERROR) << format("error: {}", error);
//        if(error != GL_NO_ERROR) throw GLError("GL Error");
    }

} // enpitsu

#endif //ENPITSU_WRAPPER_H
