#pragma once
#include "core.h"
#include "core/window.h"
#include "events/application.h"
#include "render/shader.h"
#include "render/buffer.h"
#include "render/vertex_array.h"

class Layer;
namespace NC {
  class NC_API Application {

  public:
    static Application& Get() { return *s_instance; }

    Application();
		virtual ~Application();
   
    void Run();
    void Close() { m_should_stop = true; }
    void OnEvent(Event& event);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
    CWindow& GetWindow() { return *m_window; }

  private:
    static Application* s_instance;
    Scope<CWindow> m_window;
    bool m_should_stop = false;
    bool m_minimized = false;

    bool OnWindowClose(WindowCloseEvent& _event);
    bool OnWindowResize(WindowResizeEvent& _event);
  };

  //To be defined in client
  Application* CreateApplication();
}

#define APP NC::Application::Get()
