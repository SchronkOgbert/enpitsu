#ifndef ENPITSU_DEFINES_H
#define ENPITSU_DEFINES_H

// this piece of shit needs to be here for stb to work
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

// std stuff
#include <string>
#include <memory>
#include <mutex>
#include <list>
#include <chrono>
#include <cstddef>
#include <concepts>
#include <iostream>
#include <functional>
#include <fstream>
#include <cstring>
#include <map>
#include <type_traits>
#include <thread>
#include <set>
#include <queue>
#include <initializer_list>
#include <exception>


// 3rd party stuff

#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include "plog/Log.h"
#include "plog/Initializers/ConsoleInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/transform.hpp"
#include "fmt/core.h"
#include "fmt/format.h"

// default settings
#ifndef OPENGL_DEFAULT_MAJOR_VERSION
#define OPENGL_DEFAULT_MAJOR_VERSION 4
#endif

#ifndef OPENGL_DEFAULT_MINOR_VERSION
#define OPENGL_DEFAULT_MINOR_VERSION 5
#endif

#ifndef OPENGL_DEFAULT_PROFILE
#define OPENGL_DEFAULT_PROFILE GLFW_OPENGL_ANY_PROFILE
#endif

// concepts, aliases, perfect forwards

namespace enpitsu
{
    using namespace fmt;

    template<class Object>
    concept objectType =
    requires(Object t)
    {
        { t.callInit() };
    };

    class VAO;

    template<class Shader>
    concept shaderType =
    requires(Shader t)
    {
        { t.getVao() };
    };

/**
 * perfect forward to std::make_unique, except it uses a concept to validate T
 * objects are always made using unique shaders, that is they should be in the care of the screen alone, others shall use the reference
 * @tparam T object type
 * @tparam Args constructor arguments pack type
 * @param args constructor arguments
 * @return same as std::make_unique, which is std::unique_ptr<T>&&
 */
    template<objectType T, class... Args>
    auto newObject(Args &&... args) -> decltype(std::make_unique<T>(
            std::forward<Args>(args)...)) // perfect forward for std::make_unique
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    /**
     * perfect forward to std::make_shared, except it uses a concept to validate T
     * returns a shader that shall be used by multiple objects
     * @tparam T shader type
     * @tparam Args constructor arguments pack type
     * @param args constructor arguments
     * @return same as std::make_shared, which is std::shared_ptr<T>&&
     */
    template<shaderType T, class... Args>
    auto newShader(Args&&... args) -> decltype(std::make_shared<T>(std::forward<Args>(args)...))
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

template<class T>
std::ostream& operator<<(std::ostream &out, const std::vector<T> &v)
{
    out << '[';
    for(size_t i = 0; i < v.size(); i++)
    {
        out << v[i] << ", ";
    }
    out << *(v.rbegin()) << ']';
}

#endif //ENPITSU_DEFINES_H
