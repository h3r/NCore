#include "ncpch.h"
#include "editor.h"

namespace Editor {

  void Destroy() {
    Action::Destroy();
    Panel::Destroy();
  }

  void Render() {
    Menu::Render();
    Panel::RenderAll();
  }
}
