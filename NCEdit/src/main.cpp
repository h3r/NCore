#include "NCore.h"
#include "events/event.h"

using namespace glm;

class Game : public NC::CApplication
{
public:
  
  Game() {
		Layer* mylayer = LayerRegistry.Produce("EditorLayer");
    PushLayer(mylayer);
		
		//NC::EventManager::bind<NC::OnUpdate>("NCore", this, Update);//.bind<NC::OnUpdate>(Update);
		//NC::EventManager::bind<NC::OnRender>("NCore", this, Render);//.bind<NC::OnRender>(Render);
  }

  ~Game() {
  
  }

	void Update() {
		
	}

	void Render() {

	}
};

NC::CApplication* NC::CreateApplication() {
  return new Game();
}

