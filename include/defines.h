//
// Created by weekendUM on 1/24/2023.
//

#ifndef ENPITSU_DEFINES_H
#define ENPITSU_DEFINES_H

#define _CRT_SECURE_NO_DEPRECATE

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include "plog/Log.h"
#include "plog/Initializers/ConsoleInitializer.h"
#include "plog/Appenders/ColorConsoleAppender.h"
#include "plog/Formatters/TxtFormatter.h"

#ifdef _MSC_VER
#define strdup _strdup
#endif

#define OPENGL_DEFAULT_MAJOT_VERSION 4
#define OPENGL_DEFAULT_MINOR_VERSION 5
#define OPENGL_DEFAULT_PROFILE GLFW_OPENGL_ANY_PROFILE

#endif //ENPITSU_DEFINES_H
