#include "ncpch.h"
#include "input/input.h"
#include "input_controller.h"

namespace Input
{
  CMapping::CMapping(CInputController& _controller)
    : m_controller(_controller)
  {
  }

  void CMapping::Update(float _dt)
  {
    for (auto& mapped_bt : m_buttons)
    {
      TMappedButton& map_bt = mapped_bt.second;

      float value = 0.f;
      bool all = true;
      for (auto& bt : map_bt.buttons)
      {
        all &= bt->isPressed();

        // get the highest value of all the defined buttons
        if (fabsf(bt->m_value) > fabsf(value))
        {
          value = bt->m_value;
        }
      }

      if (map_bt.check_all && !all)
      {
        value = 0.f;
      }

      map_bt.result.update(value, _dt);
    }
  }

  const TButton& CMapping::GetMappedButton(const std::string& _name) const
  {
    // check in the custom mapped buttons
    auto it = m_buttons.find(_name);
    if (it != m_buttons.end())
    {
      return it->second.result;
    }

    // check in the system-registered buttons
    const TButtonDef* bt_def = CInput::GetButtonDefinition(_name);
    if (bt_def)
    {
      return m_controller[*bt_def];
    }

    // return a dummy
    return TButton::dummy;
  }

  void CMapping::Load(const std::string& _file)
  {
    m_buttons.clear();

    auto j_data = LoadJson(_file);
    for (auto& j_entry : j_data)
    {
      if (j_entry.is_array())
        continue;

      TMappedButton mapped_bt;

      const std::string name = j_entry["name"];
      mapped_bt.check_all = j_entry["check"] == "all";
      for (auto& j_button : j_entry["buttons"])
      {
        const TButtonDef* bt_def = CInput::GetButtonDefinition(j_button);
        if (!bt_def) continue;

        const TButton& bt = m_controller[*bt_def];
        mapped_bt.buttons.push_back(&bt);
      }

      m_buttons[name] = std::move(mapped_bt);
    }
  }
}
