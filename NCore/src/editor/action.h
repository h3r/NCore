#pragma once

namespace Editor::Action
{
  struct Action {
    std::string title;
    std::string action;
    std::string shortcut;
    std::function<void()> callback;
  };

  namespace {
    std::map<std::string, Action> m_editorActions;
  }

  std::map<std::string, Action>& Actions();
  void Destroy();

  void Add(
      std::string path
    , std::string title
    , std::string action
    , std::string shortcut
    , std::function<void()> callback);

  void Remove(std::string path);
  bool Exists(std::string path);
}