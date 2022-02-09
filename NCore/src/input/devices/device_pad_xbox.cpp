#pragma once

#include "ncpch.h"
#include "device_pad_xbox.h"
#include "input/interfaces/gamepad.h"
#include "input/interfaces/rumble.h"

//#include <Xinput.h>
//#pragma comment(lib, "xinput.lib")

/*
namespace
{
  float GetButtonState(const XINPUT_STATE& _state, int _buttonId)
  {
    return (_state.Gamepad.wButtons & _buttonId) != 0 ? 1.f : 0.f;
  }

  float GetTriggerState(const XINPUT_STATE& _state, bool _left)
  {
    BYTE value = _left ? _state.Gamepad.bLeftTrigger : _state.Gamepad.bRightTrigger;
    if (value <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
    {
      return 0.f;
    }

    return static_cast<float>(value) / std::numeric_limits<BYTE>::max();
  }

  std::pair<float,float> GetAnalogState(const XINPUT_STATE & _state, bool _left)
  {
    SHORT LX = _left ? _state.Gamepad.sThumbLX : _state.Gamepad.sThumbRX;
    SHORT LY = _left ? _state.Gamepad.sThumbLY : _state.Gamepad.sThumbRY;
    SHORT INPUT_DEADZONE = _left ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

    //literally from the xboxcontroller manual
    //https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput

    //determine how far the controller is pushed
    float magnitude = float(sqrt(LX * LX + LY * LY));

    //determine the direction the controller is pushed
    float normalizedLX;
    float normalizedLY;
    float normalizedMagnitude = 0.0f;


    //check if the controller is outside a circular dead zone
    if (magnitude > INPUT_DEADZONE)
    {
      normalizedLX = LX / magnitude;
      normalizedLY = LY / magnitude;
      //clip the magnitude at its expected maximum value
      if (magnitude > 32767) magnitude = 32767;

      //adjust magnitude relative to the end of the dead zone
      magnitude -= INPUT_DEADZONE;

      //optionally normalize the magnitude with respect to its expected range
      //giving a magnitude value of 0.0 to 1.0
      normalizedMagnitude = magnitude / (32767 - INPUT_DEADZONE);
    }
    else //if the controller is in the deadzone zero out the magnitude
    {
      magnitude = 0.0;
      normalizedMagnitude = 0.0;
      normalizedLX = 0.0f;
      normalizedLY = 0.0f;
    }


    return std::make_pair(normalizedLX * normalizedMagnitude, normalizedLY * normalizedMagnitude);

    //codigo albert
    
    // result.x = static_cast<float>(valueX) / std::numeric_limits<SHORT>::max();
    // result.y = static_cast<float>(valueY) / std::numeric_limits<SHORT>::max();
    // float deadzone = static_cast<float>(valueDeadzone) / std::numeric_limits<SHORT>::max();
		// 
    // // deal with the dead zone
    // float length = result.Length();
    // if (length <= deadzone)
    // {
    //   result = VEC2::Zero;
    // }
    // else
    // {
    //   float validLength = 1.f - deadzone;
    //   float finalLength = (length - deadzone) / validLength;
    //   result.Normalize();
    //   result = result * finalLength;
    // }
		// 
    // return result;
  }
}


void CDevicePadXbox::Update(Input::GamepadData& _data)
{
  
	XINPUT_STATE state;
  data.connected = XInputGetState(_controllerId, &state) == ERROR_SUCCESS;

  if (!data.connected)
    return;

  data.buttons[Input::BT_A] = GetButtonState(state, XINPUT_GAMEPAD_A);
  data.buttons[Input::BT_B] = GetButtonState(state, XINPUT_GAMEPAD_B);
  data.buttons[Input::BT_X] = GetButtonState(state, XINPUT_GAMEPAD_X);
  data.buttons[Input::BT_Y] = GetButtonState(state, XINPUT_GAMEPAD_Y);
  data.buttons[Input::BT_LTHUMB] = GetButtonState(state, XINPUT_GAMEPAD_LEFT_THUMB);
  data.buttons[Input::BT_RTHUMB] = GetButtonState(state, XINPUT_GAMEPAD_RIGHT_THUMB);
  data.buttons[Input::BT_LBUTTON] = GetButtonState(state, XINPUT_GAMEPAD_LEFT_SHOULDER);
  data.buttons[Input::BT_RBUTTON] = GetButtonState(state, XINPUT_GAMEPAD_RIGHT_SHOULDER);
  data.buttons[Input::BT_DPAD_DOWN] = GetButtonState(state, XINPUT_GAMEPAD_DPAD_DOWN);
  data.buttons[Input::BT_DPAD_UP] = GetButtonState(state, XINPUT_GAMEPAD_DPAD_UP);
  data.buttons[Input::BT_DPAD_LEFT] = GetButtonState(state, XINPUT_GAMEPAD_DPAD_LEFT);
  data.buttons[Input::BT_DPAD_RIGHT] = GetButtonState(state, XINPUT_GAMEPAD_DPAD_RIGHT);
  data.buttons[Input::BT_SELECT] = GetButtonState(state, XINPUT_GAMEPAD_BACK);
  data.buttons[Input::BT_START] = GetButtonState(state, XINPUT_GAMEPAD_START);

  data.buttons[Input::BT_LTRIGGER] = GetTriggerState(state, true);
  data.buttons[Input::BT_RTRIGGER] = GetTriggerState(state, false);

  float [lx, ly] = GetAnalogState(state, true);
  data.buttons[Input::BT_LANALOG_X] = lx;
  data.buttons[Input::BT_LANALOG_Y] = ly;

	float[rx, ry] = GetAnalogState(state, false);
  data.buttons[Input::BT_RANALOG_X] = rx;
  data.buttons[Input::BT_RANALOG_Y] = ry;
	
}

void CDevicePadXbox::Feedback(const Input::RumbleData& _data)
{
  XINPUT_VIBRATION vibration;
  vibration.wLeftMotorSpeed = static_cast<WORD>(data.leftVibration * std::numeric_limits<WORD>::max());
  vibration.wRightMotorSpeed = static_cast<WORD>(data.rightVibration * std::numeric_limits<WORD>::max());
  XInputSetState(_controllerId, &vibration);
}

*/
