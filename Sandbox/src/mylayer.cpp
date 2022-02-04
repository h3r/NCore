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
    NC::CEventManager::bind<NC::ImGuiBegin>("ImGui", "MyLayer", [&](const NC::ImGuiBegin& _msg) { Inspect(); });
  }
  
  void OnDetach() {
    NC::CEventManager::unbind<NC::ImGuiBegin>("ImGui", "MyLayer");
  }

  void OnUpdate() {
    //log_info("Hey! I'm actually being called!");
  }

  void OnEvent(NC::TEvent& event) {
    //log_trace("TEvent: {}", event);
  }

  void Inspect() {
    //ImGui::Text(GetName().c_str());
  }
};
REGISTER_LAYER("MyLayer", CMyLayer);
