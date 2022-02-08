#pragma once
#include "core.h"
#include "core/window.h"
#include "events/application.h"
#include "render/shader.h"
#include "render/buffer.h"

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
    Scope<CWindow> m_window;
    bool m_should_stop = false;
    bool m_minimized = false;
		Ref<CShader> m_shader;
		Ref<VertexBuffer> m_vertex_buffer;
		Ref<IndexBuffer>  m_index_buffer;

    bool OnWindowClose(WindowCloseEvent& _event);
    bool OnWindowResize(WindowResizeEvent& _event);
  };

  //To be defined in client
  CApplication* CreateApplication();
}

#define APP NC::CApplication::Get()
