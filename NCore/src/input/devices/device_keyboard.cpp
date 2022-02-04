#pragma once

#include "ncpch.h"
#include "device_keyboard.h"

CDeviceKeyboard::CDeviceKeyboard(const std::string& _name)
	: Input::IDevice(_name)
{
}

void CDeviceKeyboard::Update(Input::TKeyboardData& _data)
{
  _data = m_data;
}

void CDeviceKeyboard::FlushDevice() 
{
	memset(m_data.keys, 0, sizeof(bool)*Input::BT_KEYBOARD_COUNT);
}


/*
int CDeviceKeyboard::processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam)
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


