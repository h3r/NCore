#include "ncpch.h"
#include "core/log.h"
#include "layers/layer.h"
#include "core/application.h"
#include "events/application.h"
#include "events/mouse.h"
#include "events/keyboard.h"
#include "events/imgui.h"
#include "utils.h"
#include "glad/glad.h"
#include "core/time.h"
TElapsedTime Time;

#define toString(src) #src
namespace NC {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Boolean:	return GL_BOOL;
		case ShaderDataType::Mat3:	  return GL_FLOAT;
		case ShaderDataType::Mat4:	  return GL_FLOAT;

		case ShaderDataType::Int:	    return GL_INT;
		case ShaderDataType::Int2:	  return GL_INT;
		case ShaderDataType::Int3:	  return GL_INT;
		case ShaderDataType::Int4:	  return GL_INT;

		case ShaderDataType::Float:	  return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;

		default: nc_fatal("Unknown ShaderDataType!"); return 0;
		}
	}

	unsigned int m_vertex_array;
  CApplication* CApplication::s_instance = nullptr;

  CApplication::CApplication() {
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

		//Vertex Array
		//Vertex Buffer
		//Index  Buffer
		{
			glGenVertexArrays(1, &m_vertex_array);
			glBindVertexArray(m_vertex_array);

			float vertices[3 * 11] = {
				-.5f, -.5f, .0f,     .0f,  1.f, .0f,    -.5f, -.5f,    .0f,  .8f, .0f,
				 .5f, -.5f, .0f,     .0f,  1.f, .0f,     .5f, -.5f,    .0f,  .8f, .0f,
				 .0f,  .5f, .0f,     .0f,  1.f, .0f,     .0f,  .5f,    .0f,  .8f, .0f,
			};
			m_vertex_buffer.reset( VertexBuffer::Create(vertices, sizeof(vertices)));
			
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_vertex" },
				{ ShaderDataType::Float3, "a_normal" },
				{ ShaderDataType::Float2, "a_coords" },
				{ ShaderDataType::Float4, "a_color"  },
			};

			m_vertex_buffer->SetLayout(layout);

			uint32_t index = 0;
			for (const auto& element : layout) 
			{
				glEnableVertexAttribArray(index);
				glVertexAttribPointer(
					index, 
					element.GetCount(), 
					ShaderDataTypeToOpenGLBaseType(element.type), 
					element.normalized? GL_TRUE : GL_FALSE, 
					layout.GetStride(),
					(const void*)element.offset
				);
				++index;
			}

			unsigned int indices[3] = { 0,1,2 };
			m_index_buffer.reset( IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)) );
		}

		std::string vs_code = R"(
			#version 450

			layout( location = 0 ) in vec3 "a_vertex"
			layout( location = 1 ) in vec3 "a_normal"
			layout( location = 2 ) in vec2 "a_coords"
			layout( location = 3 ) in vec4 "a_color" 
			layout( location = 4 ) out vec3 v_vertex;

			void main()
			{
				v_vertex = a_vertex;
				gl_Position = vec4(a_vertex,1.0);
			}
		)";

		std::string fs_code = R"(
			#version 450
			/*layout(std140, binding = 0) uniform global_state {
				float u_time;
			} globals*/

			layout( location = 4 ) in vec3 v_vertex;
			layout( location = 0 ) out vec4 color;

			void main()
			{
				color = vec4(v_vertex * .5 + .5, 1.0);
			}
		)";
		m_shader = CShader::Create("basic", vs_code, fs_code);
  }

  CApplication::~CApplication() {

  }

  void CApplication::Run() {
		
		static CTimer  time_since_last_render;

    while (!m_should_stop) {
			float elapsed = time_since_last_render.ElapsedAndReset();
			Time.Set(Time.current_unscaled + elapsed);

      glClearColor(.1f,.1f,.1f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);

      glBindVertexArray(m_vertex_array);
			m_shader->Bind();
			//log_info("Time: {}", Time.current);
			m_shader->SetFloat("u_time", Time.current);
      glDrawElements(GL_TRIANGLES, m_index_buffer->GetCount(), GL_UNSIGNED_INT, nullptr);

      for (auto* layer : LayerStack) {
        nc_assert(layer, "Layer is null");
        layer->OnUpdate();
      }

      ImGuiBegin begin;
      OnEvent(begin);
      //float dt = 0.16f;
      //EventManager.trigger<ImGuiBegin>(this, dt);

      for (auto* layer : LayerStack)
        layer->OnInspect();

      ImGuiEnd   end;
      OnEvent(end);

      m_window->OnUpdate();
    }
  }

  void CApplication::OnEvent(TEvent& _event) {

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
