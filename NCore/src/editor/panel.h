#pragma once
#include "ncpch.h"

namespace Editor::Panel 
{
  namespace 
  {
    struct Panel {
      bool active = false;
      std::string name;
      std::function<void()> callback;
      ImGuiWindowFlags flags = 0;
      static std::map<std::string, Panel> m_editorPanels;
      static std::map<std::string, bool>  m_defaultState;
    };
  }
  void Destroy();
  void Add(std::string name, std::function<void()>, std::string shortcut = "", ImGuiWindowFlags flags = 0);
  void Remove(std::string name);
  void Toggle(std::string name);
  void Show(std::string name);
  void Hide(std::string name);
  bool State(std::string name);
  void RenderAll();

  void Parse(nlohmann::json j);
  nlohmann::json Serialize();
}
