#ifndef ENPITSU_DEFINES_H
#define ENPITSU_DEFINES_H

// VS compiler workaround
#define _CRT_SECURE_NO_DEPRECATE

// also VS compiler workaround
#ifdef _MSC_VER
#define strdup _strdup
#endif

// this piece of shit needs to be here for stb to work
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

// default settings
#define OPENGL_DEFAULT_MAJOT_VERSION 4
#define OPENGL_DEFAULT_MINOR_VERSION 5
#define OPENGL_DEFAULT_PROFILE GLFW_OPENGL_ANY_PROFILE

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

// 3rd party stuff
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "plog/Log.h"
#include "plog/Initializers/ConsoleInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Formatters/TxtFormatter.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#endif //ENPITSU_DEFINES_H
