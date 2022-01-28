#include "NCore.h"

using namespace glm;

class Game : public NC::CApplication
{
public:
  
  Game() {
		Layer* mylayer = LayerRegistry.Produce("EditorLayer");
    PushLayer(mylayer);
  }

  ~Game() {
  
  }
};

NC::CApplication* NC::CreateApplication() {
  return new Game();
}

