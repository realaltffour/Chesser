#ifndef UNIV_INC_H
#define UNIV_INC_H
#pragma once

/*
        Deps Includes
*/

#if (!defined(__EMSCRIPTEN__)) && (!defined(__ANDROID__))
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>
#endif

#ifdef __ANDROID__

extern "C" {
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <errno.h>
#include <jni.h>
#include <stdlib.h>
#include <unistd.h>
}

#endif

#ifndef __EMSCRIPTEN__
#ifdef __WINDOWS__
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <windows.h>
#endif
#include <gflags/gflags.h>
#include <glog/logging.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

/*
        Universal files
*/
#include "Log.h"
#include "defs.h"
#include "globals.h"
#include "macros.h"
#include "utils/utils.h"

/*
        STL Includes
*/
#include <algorithm>
#include <deque>
#include <functional>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#include <fstream>
#include <istream>
#include <ostream>

#include <chrono>
#include <thread>

using namespace std;

/*
        Univ Definitions
*/

#endif