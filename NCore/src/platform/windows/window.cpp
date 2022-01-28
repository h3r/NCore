#include "ncpch.h"
#include "window.h"

#include "core/log.h"
#include "core/core.h"
#include "events/application.h"
#include "events/keyboard.h"
#include "events/mouse.h"
#include "platform/opengl/context.h";

#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_opengl3.cpp"


namespace NC {

  static bool s_glfw_initialized = false;

  CWindow* CWindow::Create(const TWindowProps& _props)
  {
    return new CWinWindow(_props);
  }

  CWinWindow::CWinWindow(const TWindowProps& _props) {
    Init(_props);
  }

  CWinWindow::~CWinWindow() {
    Stop();
  }

  void CWinWindow::Init(const TWindowProps& _props) {

    m_data.title = _props.title;
    m_data.width = _props.width;
    m_data.height = _props.height;

    log_info("Creating window {0} ({1}, {2})", m_data.title, m_data.width, m_data.height);

    if (!s_glfw_initialized) {
      int ok = glfwInit();
      nc_assert(ok, "Could not initialize GLFW");
      s_glfw_initialized = true;
    }

    //Create a GLFW Window
    m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		m_context = new OpenGLContext(m_window);
		m_context->Init();

    glfwSetWindowUserPointer(m_window, &m_data);
    SetVSync(true);

    //Set GLFW callbacks
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* _window, int _w, int _h) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);
      WindowResizeEvent event(_w, _h);
      data.width = _w;
      data.height = _h;
      data.callback(event);
    });

    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* _window) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);
      WindowCloseEvent event;
      data.callback(event);
    });

    glfwSetKeyCallback(m_window, [](GLFWwindow* _window, int _key, int _scandcode, int _action, int _mods) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);

      switch (_action) {
        case GLFW_PRESS: {
          KeyPressedEvent event(_key, 0);
          data.callback(event);
          break;
        }
        case GLFW_RELEASE: {
          KeyReleasedEvent event(_key);
          data.callback(event);
          break;
        }
        case GLFW_REPEAT: {
          KeyPressedEvent event(_key, 1);
          data.callback(event);
          break;
        }
      }
    });

    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* _window, int _button, int _action, int _mods) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);

      switch (_action) {
        case GLFW_PRESS: {
          MouseButtonPressedEvent event(_button);
          data.callback(event);
          break;
        }
        case GLFW_RELEASE: {
          MouseButtonReleasedEvent event(_button);
          data.callback(event);
          break;
        }
      }
    });

    glfwSetScrollCallback(m_window, [](GLFWwindow* _window, double _scroll_x, double _scroll_y) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);
      MouseScrollEvent event(_scroll_x, _scroll_y);
      data.callback(event);
    });

    glfwSetCursorPosCallback(m_window, [](GLFWwindow* _window, double _pos_x, double _pos_y) {
      TWindowData& data = *(TWindowData*)glfwGetWindowUserPointer(_window);
      MouseMoveEvent event(_pos_x, _pos_y);
      data.callback(event);
    });

    glfwSetErrorCallback([](int _error, const char* _msg) {
      log_error("GLFW error({}):{}", _error, _msg);
    });

  }

  void CWinWindow::Stop() {
    glfwDestroyWindow(m_window);
  }

  void CWinWindow::OnUpdate() {
    glfwPollEvents();
		m_context->SwapBuffers();
  }

  void CWinWindow::SetVSync(bool _enabled) {
    glfwSwapInterval(_enabled ? 1 : 0);
    m_data.vsync = _enabled;
  }

  bool CWinWindow::IsVSync() const {
    return m_data.vsync;
  }
}
