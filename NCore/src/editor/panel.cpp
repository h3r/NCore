#include "ncpch.h"
#include "menu.h"
#include "panel.h"

namespace Editor::Panel
{
  std::map<std::string, Panel> Panel::m_editorPanels;
  std::map<std::string, bool>  Panel::m_defaultState;

  void Destroy() { Panel::m_editorPanels.clear(); }

  void Add(std::string name, std::function<void()> callback, std::string shortcut, ImGuiWindowFlags flags)
  {
    bool is_open = Panel::m_defaultState.count(name) > 0;
    Panel::m_editorPanels[name] = { is_open, name, callback, flags };
    Menu::Add("{9}Window/" + name, [&, name]() {
      Toggle(name);
    }, shortcut);
  }
  void Remove(std::string name)
  {
    Panel::m_editorPanels.erase(name);
  }
  void Toggle(std::string name)
  {
    if (Panel::m_editorPanels.find(name) != Panel::m_editorPanels.end())
      Panel::m_editorPanels[name].active = !Panel::m_editorPanels[name].active;
  }
  void Show(std::string name)
  {
    if (Panel::m_editorPanels.find(name) != Panel::m_editorPanels.end())
      Panel::m_editorPanels[name].active = true;
  }
  void Hide(std::string name)
  {
    if (Panel::m_editorPanels.find(name) != Panel::m_editorPanels.end())
      Panel::m_editorPanels[name].active = false;
  }
  bool State(std::string name) {
    if (Panel::m_editorPanels.find(name) != Panel::m_editorPanels.end())
    return Panel::m_editorPanels[name].active;
  }
  void RenderAll()
  {
    for (auto& p : Panel::m_editorPanels) {
      auto& panel = p.second;

      if (!panel.active)
        continue;

      ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(150, 150));
      if (!ImGui::Begin(panel.name.c_str(), &panel.active, panel.flags)) {
        ImGui::End();
        ImGui::PopStyleVar();
        continue;
      }
      ImGui::PopStyleVar();
      
      panel.callback();
      ImGui::End();
    }
  }

  void Parse(json j)
  {
    if (j.is_null() || j.empty()) return;
    std::vector<std::string> active = j;
    for (std::string s : active) {
      Panel::m_defaultState[s] = true;
    }
  }

  json Serialize() {
    std::vector<std::string> active;
    for (auto& it : Panel::m_editorPanels) {
      if (it.second.active)
        active.push_back(it.first);
    }
    json j = active;
    return j;
  }
}
