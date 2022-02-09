#pragma once

#include "ncpch.h"
#include "device_raw_input.h"
#include "input/interfaces/mouse.h"
#include "input/interfaces/keyboard.h"

// value tables: http://keithditch.powweb.com/Games/html/raw_input.html

DeviceRawInput::DeviceRawInput(const std::string& _name)
  : Input::Device(_name)
{
  /*
	RAWINPUTDEVICE Rid[2];

  Rid[0].usUsagePage = 0x01;
  Rid[0].usUsage = 0x02; // mouse
  Rid[0].dwFlags = 0; // RIDEV_INPUTSINK; // enable to allow input without the window focus
  Rid[0].hwndTarget = Game.g_window_handle;

  Rid[1].usUsagePage = 0x01;
  Rid[1].usUsage = 0x06; // keyboard
  Rid[1].dwFlags = 0; // RIDEV_INPUTSINK; // enable to allow input without the window focus
  Rid[1].hwndTarget = Game.g_window_handle;

  if (RegisterRawInputDevices(Rid, 2, sizeof(Rid[0])) == FALSE) {
    //registration failed. Call GetLastError for the cause of the error
  }

  // just to have a reference value for the mouse position
  POINT cursorPos;
  GetCursorPos(&cursorPos);
  ScreenToClient(Game.g_window_handle, &cursorPos);
  m_mouseAcumX = static_cast<float>(cursorPos.x);
  m_mouseAcumY = static_cast<float>(cursorPos.y);
	*/
}

void DeviceRawInput::Update(Input::MouseData& _data)
{
	_data.pos_x = m_mouse_accum_x;
	_data.pos_y = m_mouse_accum_y;
  _data.scroll = static_cast<float>(m_wheel_delta_steps);
  for (int i = 0; i < Input::BT_MOUSE_COUNT; ++i)
  {
		_data.buttons[i] = m_mouse_buttons[i];
  }
	m_wheel_delta_steps = 0;
}

void DeviceRawInput::Update(Input::KeyboardData& _data)
{
  for (int i = 0; i < Input::BT_KEYBOARD_COUNT; ++i)
  {
    _data.keys[i] = m_keys[i];
  }
}

/*
int DeviceRawInput::processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_INPUT:
    {
      UINT dwSize = 0;

      GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
      LPBYTE lpb = new BYTE[dwSize];
      if (lpb == NULL)
      {
        return 0;
      }

      if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
      {
        OutputDebugString(TEXT("GetRawInputData does not return correct size !\n"));
        return 0;
      }

      RAWINPUT* raw = (RAWINPUT*)lpb;

      if (raw->header.dwType == RIM_TYPEKEYBOARD)
      {
        const RAWKEYBOARD& keyboardData = raw->data.keyboard;
        _keys[keyboardData.VKey] = keyboardData.Message == WM_KEYDOWN || keyboardData.Message == WM_SYSKEYDOWN;
      }
      else if (raw->header.dwType == RIM_TYPEMOUSE)
      {
        const RAWMOUSE& mouseData = raw->data.mouse;
        
        if (mouseData.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
        {
          _mouseButtons[Input::BT_MOUSE_LEFT] = true;
        }
        if (mouseData.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
        {
          _mouseButtons[Input::BT_MOUSE_LEFT] = false;
        }

        if (mouseData.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
        {
          _mouseButtons[Input::BT_MOUSE_MIDDLE] = true;
        }
        if (mouseData.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)
        {
          _mouseButtons[Input::BT_MOUSE_MIDDLE] = false;
        }

        if (mouseData.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
        {
          _mouseButtons[Input::BT_MOUSE_RIGHT] = true;
        }
        if (mouseData.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
        {
          _mouseButtons[Input::BT_MOUSE_RIGHT] = false;
        }

        _mouseAcumX += static_cast<float>(mouseData.lLastX);
        _mouseAcumY += static_cast<float>(mouseData.lLastY);

        _wheelDeltaSteps += (short)mouseData.usButtonData / WHEEL_DELTA;
      }

      delete[] lpb;
      break;
    }
    default:
      return 0;
    ;
  }
  return 0;
}
*/
