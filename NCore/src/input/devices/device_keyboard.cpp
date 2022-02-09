#pragma once

#include "ncpch.h"
#include "device_keyboard.h"

DeviceKeyboard::DeviceKeyboard(const std::string& _name)
	: Input::Device(_name)
{
}

void DeviceKeyboard::Update(Input::KeyboardData& _data)
{
  _data = m_data;
}

void DeviceKeyboard::FlushDevice() 
{
	memset(m_data.keys, 0, sizeof(bool)*Input::BT_KEYBOARD_COUNT);
}


/*
int DeviceKeyboard::processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
  if (message == WM_KEYDOWN) {
    my_data.keys[wParam] = true;
    return 1;
  }
  else if (message == WM_KEYUP) {
    my_data.keys[wParam] = false;
    return 1;
  }
  return 0;
}
*/


