#ifndef COMMON_H
#define COMMON_H
#pragma once

/*
		Deps Includes
*/

#if defined(__DESKTOP__)
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#endif

#if defined(__WEB__)
#include <GLES3/gl32.h>
#include <GLFW/glfw3.h>
#include <emscripten/emscripten.h>
#endif

#ifdef __ANDROID__
#define GLFM_INCLUDE_ES3
#include <glfm.h>
#define FILE_COMPAT_ANDROID_ACTIVITY glfmAndroidGetActivity()
#include <vendor/file_compat.h>
#endif

#ifndef __EMSCRIPTEN__
#ifdef __WINDOWS__
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <windows.h>
#endif
#include <gflags/gflags.h>
#include <glog/logging.h>
#endif

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
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
#if (__OS__ != __OS_WIN32__) || (__OS__ != __OS_WIN64__)
#include <thread>
#else
#include <vendor/threads/mingw.thread.h>
#endif

using namespace std;

/*
		Univ Definitions
*/

#endif