#pragma once

#include "ncpch.h"
#include "core/application.h"
#include "device_mouse.h"
#include "input/interfaces/mouse.h"
//#include <Windowsx.h>         // GET_Y_LPARAM

CDeviceMouse::CDeviceMouse(const std::string& _name)
  : Input::IDevice(_name)
{
  StartRawInputData();
}

void CDeviceMouse::Update(Input::TMouseData& _data)
{
	_data.pos_x = static_cast<float>(m_pos_x);
	_data.pos_y = static_cast<float>(m_pos_y);
	_data.scroll = static_cast<float>(m_scroll);
	_data.delta_x = static_cast<float>(m_delta_x);
	_data.delta_y = static_cast<float>(m_delta_y);
  for (int i = 0; i < Input::BT_MOUSE_COUNT; ++i)
  {
		_data.buttons[i] = m_buttons[i];
  }
  //reset
	m_scroll = m_delta_x = m_delta_y = 0;
}


void CDeviceMouse::StartRawInputData() {
/*
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

  RAWINPUTDEVICE Rid[1];
  Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
  Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE;
  Rid[0].dwFlags = RIDEV_INPUTSINK;
  Rid[0].hwndTarget = Game.g_window_handle;
  RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));
*/
}

void CDeviceMouse::FlushDevice() {
	memset(m_buttons, 0, sizeof(bool) * Input::BT_MOUSE_COUNT);
}

/*
int CDeviceMouse::processWindowMsg(UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
  case WM_INPUT: {
    UINT dwSize = 64;
    static BYTE lpb[64];

    int rc = ::GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER));
    if (rc == -1)
      return 0;

    RAWINPUT* raw = (RAWINPUT*)lpb;
    if (raw->header.dwType == RIM_TYPEMOUSE)
    {
      // Save mouse relative movement!
      _deltaX = raw->data.mouse.lLastX;
      _deltaY = raw->data.mouse.lLastY;
      //dbg("Mouse delta is %d,%d\n", _deltaX, _deltaY);
      return 1;
    }
    break;
  }
  case WM_MOUSEMOVE:
  {
    _posX = GET_X_LPARAM(lParam);
    _posY = GET_Y_LPARAM(lParam);
    break;
  }
  case WM_MOUSEWHEEL:
  {
    _wheelDeltaSteps = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
    break;
  }
  case WM_MBUTTONDOWN:
  {
    _buttons[Input::BT_MOUSE_MIDDLE] = true;
    break;
  }
  case WM_MBUTTONUP:
  {
    _buttons[Input::BT_MOUSE_MIDDLE] = false;
    break;
  }
  case WM_LBUTTONDOWN:
  {
    _buttons[Input::BT_MOUSE_LEFT] = true;
    break;
  }
  case WM_LBUTTONUP:
  {
    _buttons[Input::BT_MOUSE_LEFT] = false;
    break;
  }
  case WM_RBUTTONDOWN:
  {
    _buttons[Input::BT_MOUSE_RIGHT] = true;
    break;
  }
  case WM_RBUTTONUP:
  {
    _buttons[Input::BT_MOUSE_RIGHT] = false;
    break;
  }
  default:;
  }
  return 0;
}
*/
