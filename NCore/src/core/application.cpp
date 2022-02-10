#include "ncpch.h"
#include "core/application.h"
#include "layers/layer.h"

#include "events/application.h"
#include "events/mouse.h"
#include "events/keyboard.h"
#include "events/imgui.h"
#include "events/render.h"

#include "utils/utils.h"
#include "utils/time.h"

#include "render/render_command.h"

#define toString(src) #src
namespace NC {

  Application* Application::s_instance = nullptr;

  Application::Application() {
		GenerateDefaultAssets();

    nc_assert(!s_instance, "Only one application allowed to exist");
    s_instance = this;

    m_window = std::unique_ptr<CWindow>(CWindow::Create());
    m_window->SetEventCallback(BIND(OnEvent));

		auto* controller_layer = LayerRegistry.Produce("ControllerLayer");
		PushLayer(controller_layer);

		auto* imgui_layer = LayerRegistry.Produce("ImguiLayer");
		PushOverlay(imgui_layer);
  }

  Application::~Application() {

  }

  void Application::Run() {

    while (!m_should_stop) 
		{
			static CTimer  time_since_last_render;
			float elapsed = time_since_last_render.ElapsedAndReset();
			TElapsedTime::Get().Set(TElapsedTime::Get().current_unscaled + elapsed);

			{	//Update Layers
				for (auto* layer : LayerStack) {
					nc_assert(layer, "Layer is null");
					layer->OnUpdate();
				}
			}

			{	//Imgui Inspect Layers
				OnEvent(ImGuiBegin());
				for (auto* layer : LayerStack)
					layer->OnInspect();
				OnEvent(ImGuiEnd());
			}

			OnEvent(Renderer::Flush());
			m_window->OnUpdate();

    }
  }

  void Application::OnEvent(Event& _event) {

    EventDispatcher dispatcher(_event);
    dispatcher.Dispatch<WindowCloseEvent>(BIND(OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND(OnWindowResize));


		dispatcher.Dispatch<Renderer::Begin>([](Renderer::Begin& event) { 
		 	RenderCommand::SetClearColor({ .1f, .1f, .1f, 1.f });
			RenderCommand::Clear();
			return true; 
		});

		dispatcher.Dispatch<Renderer::Submit>([](Renderer::Submit& e) { 
			e.m_shader->Bind();
			e.m_vertex_array->Bind();
			RenderCommand::DrawIndexed(e.m_vertex_array);
			return true; 
		});

		dispatcher.Dispatch<Renderer::End>([](Renderer::End& event) { 
			return true; 
		});

		dispatcher.Dispatch<Renderer::Flush>([this](Renderer::Flush& event) {
			return true;
		});

    for (auto it = LayerStack.rbegin(); it != LayerStack.rend(); ++it) {
      if (_event.m_handled) break;
      (*it)->OnEvent(_event);
    }
  }
  
  bool Application::OnWindowClose(WindowCloseEvent& _event) {
    if(_event.GetEventType() != WindowCloseEvent::GetStaticType())
      return false;

    m_should_stop = true;
    return true;
  }

  bool Application::OnWindowResize(WindowResizeEvent& _event){
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

  void Application::PushLayer(Layer* layer) {
    LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer) {
    LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }
}
