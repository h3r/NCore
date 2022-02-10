#include "events/event.h"
#include "events/imgui.h"
#include "events/render.h"
#include "layers/layer.h"
#include "render/shader.h"
#include "render/vertex_array.h"
#include "core/application.h"
#include "math/camera.h"
#include "utils/time.h"
#include "imgui.h"

using namespace NC;

class EditorLayer : public Layer 
{
	Ref<Shader> m_shader;
	Ref<VertexArray>  m_vertex_array;
	OrthoGraphicCamera m_camera;

public:
	EditorLayer() 
		: Layer("EditorLayer")
		, m_camera(-1.f,1.f,-1.f,1.f)
	{
    log_info("Constructor");

		{ //Create some geometry
	//Create VAO
			m_vertex_array.reset(VertexArray::Create());

			//Create Vertex Buffer
			float vertices[3 * 12] = {
			-.5f, -.5f, .0f,     .0f,  1.f, .0f,    -.5f, -.5f,    .0f,  .8f, .0f, 1.f,
			 .5f, -.5f, .0f,     .0f,  1.f, .0f,     .5f, -.5f,    .0f,  .8f, .0f, 1.f,
			 .0f,  .5f, .0f,     .0f,  1.f, .0f,     .0f,  .5f,    .0f,  .8f, .0f, 1.f,
			};
			Ref<VertexBuffer> m_vertex_buffer;
			m_vertex_buffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

			//Create Index Buffer
			unsigned int indices[3] = { 0,1,2 };
			Ref<IndexBuffer> m_index_buffer;
			m_index_buffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

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
					gl_Position = vec4(a_vertex * .5 + .5,1.0);
				}
			)";

			std::string fs_code = R"(#version 450

				layout( location = 1 ) in vec3 v_vertex;
				layout( location = 0 ) out vec4 color;

				void main() {
					color = vec4(v_vertex * .5 + .5, 1.0);
				}
			)";
			m_shader = Shader::Create("basic", vs_code, fs_code);
		}
  }
  void OnAttach() {
    //EventManager::bind<ImGuiBegin>("ImGui", "EditorLayer", [&](const ImGuiBegin& _msg) { Inspect(); });
  }
  
  void OnDetach() {
		//EventManager::unbind<ImGuiBegin>("ImGui", "EditorLayer");
  }

  void OnUpdate() {
    //log_info("Hey! I'm actually being called!");
		
		m_shader->SetFloat("u_time", TElapsedTime::Get().current);
		//m_shader->SetMat4("u_view_proj", m_camera.GetViewProjMatrix());

		{ //Render our Scene
			Application::Get().OnEvent(Renderer::Begin());
			Application::Get().OnEvent(Renderer::Submit(m_shader, m_vertex_array));
			Application::Get().OnEvent(Renderer::End());
		}
  }

  void OnEvent(Event& event) {
    //log_trace("Event: {}", event);
  }

  void OnInspect() {
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);
  }
};
REGISTER_LAYER("EditorLayer", EditorLayer);
