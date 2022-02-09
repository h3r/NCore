#include "events/event.h"
#include "events/imgui.h"
#include "layers/layer.h"

using namespace NC;

class EditorLayer : public Layer 
{
public:
	EditorLayer() : Layer("EditorLayer") {
    log_info("Constructor");
  }
  void OnAttach() {
    //EventManager::bind<ImGuiBegin>("ImGui", "EditorLayer", [&](const ImGuiBegin& _msg) { Inspect(); });
  }
  
  void OnDetach() {
		//EventManager::unbind<ImGuiBegin>("ImGui", "EditorLayer");
  }

  void OnUpdate() {
    //log_info("Hey! I'm actually being called!");
  }

  void OnEvent(Event& event) {
    //log_trace("Event: {}", event);
  }

  void OnInspect() {
		//log_trace("Event: {}");
    //ImGui::Text(GetName().c_str());
  }
};
REGISTER_LAYER("EditorLayer", EditorLayer);
