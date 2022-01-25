#include "ncpch.h"
#include "menu.h"
#include "action.h"
#include "panel.h"

namespace Editor::Menu
{
  void Add(std::string path, std::function<void()> callback, std::string shortcut)
  {
    nc_assert(!path.empty(), "Path cannot be empty");
    nc_assert(path.find("/") != std::string::npos, "Path invalid format <Menu>/<Action>");
    if (Action::Exists(path)) {
      log_warn("[Warn] EditorMenu action already exists: %s", path.c_str());
      return;
    }

    auto title = path.substr(0, path.find("/"));
    auto action = path.substr(path.find("/") + 1, path.size() - 1);

    auto i = title.find("}");
    if (i != std::string::npos)
      title = title.substr(i + 1, title.size() - 1);

    i = action.find("}");
    if (i != std::string::npos)
      action = action.substr(i + 1, action.size() - 1);

    Action::Add(path, title, action, shortcut, callback);
  }

  void Remove(std::string path) {
    Action::Remove(path);
  }

  void Render()
  {
    if (!ImGui::BeginMenuBar())
      return;

    bool menuopen = false;
    std::string oldkey = "";
    auto actions = Action::Actions();

    for (auto pair : actions)
    {
      auto action = pair.second;
      if (oldkey != action.title)
      {
        if (oldkey != "" && menuopen)
          ImGui::EndMenu();

        menuopen = true;
        oldkey = action.title;

        if (!ImGui::BeginMenu(action.title.c_str()))
        {
          menuopen = false;
          continue;
        }
      }

      auto name = action.action.c_str();
      if (menuopen && ImGui::MenuItem(name, action.shortcut.c_str(), Editor::Panel::State(name)))
        action.callback();
    }

    if (!actions.empty() && menuopen)
      ImGui::EndMenu();

    ImGui::EndMenuBar();
  }
}
