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

TElapsedTime Time;

#define toString(src) #src
namespace NC {

  Application* Application::s_instance = nullptr;

  Application::Application() {
		GenerateDefaultAssets();

    nc_assert(!s_instance, "Only one application allowed to exist");
    s_instance = this;

    m_window = std::unique_ptr<CWindow>(CWindow::Create());
    m_window->SetEventCallback(BIND(OnEvent));

    auto* imgui_layer = LayerRegistry.Produce("ImguiLayer");
		nc_assert(imgui_layer, "");
    PushOverlay(imgui_layer);

		auto* controller_layer = LayerRegistry.Produce("ControllerLayer");
		nc_assert(controller_layer, "");
		PushLayer(controller_layer);

		{ //Create some geometry
			//Create VAO
			m_vertex_array.reset(  VertexArray::Create() );

			//Create Vertex Buffer
			float vertices[3 * 12] = {
			-.5f, -.5f, .0f,     .0f,  1.f, .0f,    -.5f, -.5f,    .0f,  .8f, .0f, 1.f,
			 .5f, -.5f, .0f,     .0f,  1.f, .0f,     .5f, -.5f,    .0f,  .8f, .0f, 1.f,
			 .0f,  .5f, .0f,     .0f,  1.f, .0f,     .0f,  .5f,    .0f,  .8f, .0f, 1.f,
			};
			Ref<VertexBuffer> m_vertex_buffer;
			m_vertex_buffer.reset( VertexBuffer::Create(vertices, sizeof(vertices)) );
			
			//Create Index Buffer
			unsigned int indices[3] = { 0,1,2 };
			Ref<IndexBuffer> m_index_buffer;
			m_index_buffer.reset(  IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );
			
			//Create & Set Vertex layout
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_vertex" },
				{ ShaderDataType::Float3, "a_normal" },
				{ ShaderDataType::Float2, "a_coords" },
				{ ShaderDataType::Float4, "a_color"  },
			};
			m_vertex_buffer->SetLayout(layout);
			
			//Set buffers into VAO
			m_vertex_array->SetIndexBuffer(m_index_buffer);
			m_vertex_array->AddVertexBuffer(m_vertex_buffer);
		}

		{ //Create a shader
			std::string vs_code = R"(#version 450
				layout( location = 0 ) in  vec3 a_vertex;
				layout( location = 1 ) out vec3 v_vertex;

				void main() {
					v_vertex = a_vertex;
					gl_Position = vec4(a_vertex,1.0);
				}
			)";

			std::string fs_code = R"(#version 450
				layout( location = 0 ) out vec4 color;
				layout( location = 1 ) in vec3 v_vertex;

				void main() {
					color = vec4(v_vertex * .5 + .5, 1.0);
				}
			)";
			m_shader = Shader::Create("basic", vs_code, fs_code);
		}
  }

  Application::~Application() {

  }

  void Application::Run() {

    while (!m_should_stop) 
		{
			static CTimer  time_since_last_render;
			float elapsed = time_since_last_render.ElapsedAndReset();
			Time.Set(Time.current_unscaled + elapsed);

			{ //Render our Scene
				OnEvent(Renderer::Begin());
				m_shader->Bind();
				OnEvent(Renderer::Submit(m_vertex_array));
				OnEvent(Renderer::End());
			}

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
			e.m_vertex_array->Bind();
			RenderCommand::DrawIndexed(e.m_vertex_array);
			return true; 
		});

		dispatcher.Dispatch<Renderer::End>([](Renderer::End& event) { 
			return true; 
		});

		dispatcher.Dispatch<Renderer::Flush>([this](Renderer::Flush& event) {
			m_window->OnUpdate();
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
