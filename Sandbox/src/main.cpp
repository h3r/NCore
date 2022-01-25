#include "NCore.h"

using namespace glm;

class Game : public NC::CApplication
{
public:
  
  Game() {
    Layer* mylayer = LayerRegistry.Produce("MyLayer");
    LayerStack.PushLayer(mylayer);
  }

  ~Game() {
  
  }
};

NC::CApplication* NC::CreateApplication() {
  return new Game();
}

int main(int argc, char** argv) {

  NC::CLog::Init();
  vec3 a(1.f, 2.f, 3.f);

  auto app = NC::CreateApplication();
  app->Run();
  delete app;

  return 0;

}
