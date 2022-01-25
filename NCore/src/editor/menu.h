#pragma once

namespace Editor::Menu {
  void Add(std::string path, std::function<void()> callback, std::string shortcut = "");
  void Remove(std::string path);
  void Render();
}





