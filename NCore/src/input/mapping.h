#pragma once
#include "input/button.h"

namespace Input
{
  class InputController;
  struct MappedButton
  {
    Button result;
    bool check_all = false;
    std::vector<const Button*> buttons;
  };

  class Mapping
  {
  public:
    Mapping(InputController& _controller);
    void Update(float _dt);
    void Load(const std::string& _file);
    const Button& GetMappedButton(const std::string& _name) const;
	private:
    InputController& m_controller;
    std::map<std::string, MappedButton> m_buttons;
  };
}
