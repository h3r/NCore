#include "ncpch.h"
#include "layers/layer.h"

#include "input/input.h"
#include "events/event.h"
#include "core/log.h"
#include "core/application.h"



using namespace NC;

class CControllerLayer : public Layer
{
public:
	CControllerLayer() : Layer("ControllerLayer") {}
	~CControllerLayer() {}

	void OnEvent(NC::TEvent& _event) {

	}

	void OnAttach() {
		Input::CInputController* p1 = EngineInput.CreateInputControl("Player1"); //Configuracion A
		p1->RegisterDevice(new CDeviceKeyboard("keyboard"));
		p1->RegisterDevice(new CDeviceMouse("mouse"));
		//p1->RegisterDevice(new CDevicePadXbox("gamepad", 0));
		p1->AssignMapping("data/input/mapping.json");

		Input::CInputController* p2 = EngineInput.CreateInputControl("Player2"); //Configuracion B
		p2->RegisterDevice(new CDeviceKeyboard("keyboard"));
		p2->RegisterDevice(new CDeviceMouse("mouse"));
		//p2->RegisterDevice(new CDevicePadXbox("gamepad", 1));
		p2->AssignMapping("data/input/mapping.json");
	}

	void OnDetach() {

	}

	void OnInspect() override {

	}

};


REGISTER_LAYER("ControllerLayer", CControllerLayer)
