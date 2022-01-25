#include "ncpch.h"
#include "action.h"

namespace Editor::Action {
  std::map<std::string, Action>& Actions() { return  m_editorActions; }
  void Destroy() { m_editorActions.clear(); }

  void Add(
    std::string path
    , std::string title
    , std::string action
    , std::string shortcut
    , std::function<void()> callback)
  {
    m_editorActions[path] = { title, action, shortcut, callback };
  }

  void Remove(std::string path) {
    m_editorActions.erase(path);
  }

  bool Exists(std::string path) {
    return (m_editorActions.find(path) != m_editorActions.end());
  }
}
