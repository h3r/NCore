#include "ncpch.h"
#include "glad/glad.h"
#include "core/log.h"
#include "layers/layer.h"
#include "core/application.h"
#include "events/application.h"
#include "events/mouse.h"
#include "events/keyboard.h"
#include "events/imgui.h"
#include "utils.h"


#define toString(src) #src
unsigned int m_vertex_array, m_vertex_buffer, m_index_buffer;

namespace NC {
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
		//PushLayer(controller_layer);


		//Vertex Array
		//Vertex Buffer
		//Index  Buffer
		{
			glGenVertexArrays(1, &m_vertex_array);
			glBindVertexArray(m_vertex_array);

			glGenBuffers(1, &m_vertex_buffer);
			glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
			float vertices[3 * 3] = {
				-.5f, -.5f, .0f,
				 .5f, -.5f, .0f,
				 .0f,  .5f, .0f,
			};
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glDisableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		

			glGenBuffers(1, &m_index_buffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
			unsigned int indices[3] = { 0,1,2 };
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);
		}

		//Shader
		{
				GLuint vs = glCreateShader(GL_VERTEX_SHADER);
			{
				const GLchar* source = R"(void main() {
				})";
				glShaderSource(vs, 1, &source, 0);
				glCompileShader(vs);
				GLint res = 0;
				glGetShaderiv(vs,GL_COMPILE_STATUS, &res);
				if (res == GL_FALSE)
				{
					GLint length = 0;
					glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
					std::vector<GLchar> log(length);
					glGetShaderInfoLog(vs, length, &length, &log[0]);
					glDeleteShader(vs);
					log_error(log.data());
				}
			}
				GLuint fs = glCreateShader(GL_VERTEX_SHADER);
			{
				const GLchar* source = toString(void main() {

				});
				glShaderSource(fs, 1, &source, 0);
				glCompileShader(fs);
			}	
			{
				GLuint program = glCreateProgram();
				glAttachShader(program, vs);
				glAttachShader(program, fs);
				glLinkProgram(program);
			}
		}

  }

  CApplication::~CApplication() {

  }

  void CApplication::Run() {

    while (!m_should_stop) {
      glClearColor(.1,.1,.1, 1);
      glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_vertex_array);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
