#include "ncpch.h"
#include "glad/glad.h"
#include "core/log.h"
#include "layers/layer.h"
#include "core/application.h"
#include "events/application.h"
#include "events/mouse.h"
#include "events/keyboard.h"
#include "events/imgui.h"

namespace NC {
  CApplication* CApplication::s_instance = nullptr;

  CApplication::CApplication() {
    nc_assert(!s_instance, "Only one application allowed to exist");
    s_instance = this;

    m_window = std::unique_ptr<CWindow>(CWindow::Create());
    m_window->SetEventCallback(BIND(OnEvent));

    auto* imgui_layer = LayerRegistry.Produce("imgui");
    PushOverlay(imgui_layer);
  }

  CApplication::~CApplication() {

  }

  void CApplication::Run() {

    while (!m_should_stop) {
      glClearColor(1, 0, 1, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      for (auto* layer : LayerStack)
        layer->OnUpdate();

      ImGuiBegin begin;
      OnEvent(begin);

      for (auto* layer : LayerStack)
        layer->OnInspect();

      ImGuiEnd   end;
      OnEvent(end);

      m_window->OnUpdate();
    }
  }

  void CApplication::OnEvent(Event& _event) {
    CEventDispatcher dispatcher(_event);
    dispatcher.Dispatch<WindowCloseEvent>(BIND(OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND(OnWindowResize));

    for (auto it = LayerStack.rbegin(); it != LayerStack.rend(); ++it) {
      if (_event.m_handled) break;
      (*it)->OnEvent(_event);
    }
  }
  
  bool CApplication::OnWindowClose(WindowCloseEvent& _event) {
    if(_event.GetEventType() != WindowCloseEvent::GetStaticType())
      return false;

    m_should_stop = true;
    return true;
  }

  bool CApplication::OnWindowResize(WindowResizeEvent& _event){
    if (_event.GetEventType() != WindowCloseEvent::GetStaticType())
      return false;

    if (_event.m_width == 0 || _event.m_height == 0) {
      m_minimized = true;
      return false;
    }

    m_minimized = false;
    //Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
  }

  void CApplication::PushLayer(Layer* layer) {
    LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void CApplication::PushOverlay(Layer* layer) {
    LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }
}
