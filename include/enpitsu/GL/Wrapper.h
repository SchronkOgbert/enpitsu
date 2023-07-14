#ifndef ENPITSU_WRAPPER_H
#define ENPITSU_WRAPPER_H

#include "enpitsu/helpers/defines.h"
#include "enpitsu/helpers/Exception.h"
#include "fmt/format.h"
#include <optional>

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
    requires std::invocable<Function&, Args...>
    inline auto callGLFunction(Function function, Args ...args)
    {
        using retType = decltype(std::function{function})::result_type;
        std::optional<int> ret = std::nullopt;
        if constexpr (typeid(retType) != typeid(void))
        {
            ret = static_cast<int>(function(args...));
        }
        else
        {
            function(args...);
        }
        auto error = glGetError();
#ifdef DEBUG
        PLOGE_IF(error != GL_NO_ERROR) << format("error: {}", error);
#endif
        if (error != GL_NO_ERROR) throw GLError("GL Error");
        return ret.value_or(0);
    }

} // enpitsu

#endif //ENPITSU_WRAPPER_H
