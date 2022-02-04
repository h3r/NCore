#pragma once
#include "core.h"
#include "core/window.h"
#include "events/application.h"

class Layer;
namespace NC {
  class NC_API CApplication {

  public:
    static CApplication& Get() { return *s_instance; }

    CApplication();
    virtual ~CApplication();
   
    void Run();
    void Close() { m_should_stop = true; }
    void OnEvent(TEvent& event);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
    CWindow& GetWindow() { return *m_window; }

  private:
    static CApplication* s_instance;
    std::unique_ptr<CWindow> m_window;
    bool m_should_stop = false;
    bool m_minimized = false;

    bool OnWindowClose(WindowCloseEvent& _event);
    bool OnWindowResize(WindowResizeEvent& _event);
  };

  //To be defined in client
  CApplication* CreateApplication();
}

#define APP NC::CApplication::Get()
