#pragma once
#include "input/button.h"

namespace Input
{
  class CInputController;
  struct TMappedButton
  {
    TButton result;
    bool check_all = false;
    std::vector<const TButton*> buttons;
  };

  class CMapping
  {
  public:
    CMapping(CInputController& _controller);
    void Update(float _dt);
    void Load(const std::string& _file);
    const TButton& GetMappedButton(const std::string& _name) const;
	private:
    CInputController& m_controller;
    std::map<std::string, TMappedButton> m_buttons;
  };
}
