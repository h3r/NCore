#include "NCore.h"
#include "events/event.h"

using namespace glm;

class NCEditor : public NC::Application
{
public:
  
	NCEditor() {
		Layer* mylayer = LayerRegistry.Produce("EditorLayer");
    PushLayer(mylayer);
		
		//NC::EventManager::bind<NC::OnUpdate>("NCore", this, Update);//.bind<NC::OnUpdate>(Update);
		//NC::EventManager::bind<NC::OnRender>("NCore", this, Render);//.bind<NC::OnRender>(Render);
  }

  ~NCEditor() {
  
  }

	void Update() {
		
	}

	void Render() {

	}
};

NC::Application* NC::CreateApplication() {
  return new NCEditor();
}

