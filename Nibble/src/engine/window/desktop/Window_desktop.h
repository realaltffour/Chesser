/**
 * @file Window_desktop.h
 * @author Ayham Mamoun (ayhamaboualfadl@gmail.com)
 * @brief Contains window definition to be run on desktops.
 * @version 0.1
 * @date 2019-05-31
 *
 */
#ifndef WINDOW_DESKTOP_H
#define WINDOW_DESKTOP_H
#pragma once

#include "common.h"
#include "error_macros.h"

#include <engine/events/events.h>
#include <engine/mvp/MVP.h>

#include "__init.h"

#include <engine/Timer.h>

#include <engine/window/WindowBase.h>
#include <engine/renderers/pingpong/PingPongRenderer.h>

namespace GEngine {
    namespace Window {
        /**
         * @brief This window Class is used for Desktop
         *
         */
        class Window : public GEngine::Window::WindowBase {
            public:
                /**
                 * @brief Construct a new Window object
                 *
                 * @param auto_size If true, auto size the window to the full monitor.
                 * @param width		The width of the window.
                 * @param height	The height of the window.
                 * @param title		The title of the window.
                 */
                Window(bool auto_size, int width, int height, std::string title);
                ~Window(void);

                void start(void) override;
                void destroy(void) override;

            private:  // Vars
                GLFWwindow* _window;

            public:
                void __init(int w, int h, std::string str) override;
                void __loop(void) override;

                // GLFW Events Funcs
            public:
                /**
                 * @brief Function called when a key event is fired.
                 *
                 * @param key		The key code of the action key.
                 * @param scancode	The scancode of the key.
                 * @param action	The event action, ex: KeyReleased, KeyPressed.
                 * @param mods		The key mods.
                 */
                void OnKey(int key, int scancode, int action, int mods);
                /**
                 * @brief Function called when a mouse event is fired.
                 *
                 * @param button	The key code of the button.
                 * @param action	The action of the event.
                 * @param mods		The mods of the event.
                 */
                void OnMouseButton(int button, int action, int mods);
                /**
                 * @brief Function called when a resize event is fired.
                 *
                 * @param width		The width of the window.
                 * @param height	The height of the window.
                 */
                void OnResize(int width, int height);
                /**
                 * @brief Function called when mouse moved is fired.
                 *
                 * @param xpos		The location of the mouse relative to the window.
                 * @param ypos		The location of the ouse relative to the window.
                 */
                void OnMousePos(double xpos, double ypos);
                /**
                 * @brief Function called when cursor enters the window.
                 *
                 */
                void OnCursorEntered(void);
                /**
                 * @brief Function called when cursor exits the window.
                 *
                 */
                void OnCursorExit(void);
        };

        static void mouse_button_callback(GLFWwindow* window, int button, int action,
                int mods) {
            void* data = glfwGetWindowUserPointer(window);
            GEngine::Window::Window* win = static_cast<GEngine::Window::Window*>(data);

            win->OnMouseButton(button, action, mods);
        }

        static void cursor_enter_callback(GLFWwindow* window, int entered) {
            void* data = glfwGetWindowUserPointer(window);
            GEngine::Window::Window* win = static_cast<GEngine::Window::Window*>(data);

            if (entered)
                win->OnCursorEntered();
            else
                win->OnCursorExit();
        }

        static void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
            void* data = glfwGetWindowUserPointer(window);
            Window* win = static_cast<Window*>(data);
            win->OnMousePos(xpos, ypos);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action,
                int mods) {
            void* data = glfwGetWindowUserPointer(window);
            Window* win = static_cast<Window*>(data);
            win->OnKey(key, scancode, action, mods);
        }
        static void resize_callback(GLFWwindow* window, int width, int height) {
            void* data = glfwGetWindowUserPointer(window);
            Window* win = static_cast<Window*>(data);
            win->OnResize(width, height);
        }

    }  // namespace Window
}  // namespace GEngine
#endif
