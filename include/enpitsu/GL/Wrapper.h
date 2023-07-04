#ifndef ENPITSU_WRAPPER_H
#define ENPITSU_WRAPPER_H

#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/Exception.h"
#include "fmt/format.h"
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

    /**
     * This function throws an error when there's an OpenGL error in the call
     * @tparam Function function type
     * @tparam Args parameter pack type
     * @param function the OpenGL function pointer
     * @param args the arguments of the function
     * It is NOT recommended to run this in speed critical sections(such as draw calls) as it adds quite a bit of overhead
     */
    template<class Function, class ...Args>
    inline void callGLFunction(Function *function, Args ...args)
    {
        function(args...);
        auto error = glGetError();
#ifdef DEBUG
        PLOGD_IF(error != GL_NO_ERROR) << format("error: {}", error);
#endif
        if (error != GL_NO_ERROR) throw GLError("GL Error");
    }

} // enpitsu

#endif //ENPITSU_WRAPPER_H
