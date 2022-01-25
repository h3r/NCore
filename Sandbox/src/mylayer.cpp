#include "NCore.h"
#include "events/event.h"
#include "events/imgui.h"
#include "imgui/imgui.h"

class CMyLayer : public Layer 
{
public:
  CMyLayer() : Layer("MyLayer") {
    log_info("Constructor");
  }
  void OnAttach() {
    NC::EventManager::bind<NC::ImGuiBegin>("ImGui", "MyLayer", [&](const NC::ImGuiBegin& _msg) { Inspect(); });
  }
  
  void OnDetach() {
    NC::EventManager::unbind<NC::ImGuiBegin>("ImGui", "MyLayer");
  }

  void OnUpdate() {
    log_info("Hey! I'm actually being called!");
  }

  void OnEvent(NC::Event& event) {
    log_trace("Event: {}", event);
  }

  void Inspect() {
    //ImGui::Text(GetName().c_str());
  }
};
REGISTER_LAYER("MyLayer", CMyLayer);
