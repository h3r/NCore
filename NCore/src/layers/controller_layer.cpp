#include "ncpch.h"
#include "layers/layer.h"

#include "input/input.h"
#include "events/event.h"
#include "core/core.h"
#include "core/application.h"



using namespace NC;

class ControllerLayer : public Layer
{
public:
	ControllerLayer() : Layer("ControllerLayer") {}
	~ControllerLayer() {}

	void OnEvent(NC::Event& _event) {

	}

	void OnAttach() {
		Input::InputController* p1 = EngineInput.CreateInputControl("Player1"); //Configuracion A
		p1->RegisterDevice(new DeviceKeyboard("keyboard"));
		p1->RegisterDevice(new DeviceMouse("mouse"));
		//p1->RegisterDevice(new CDevicePadXbox("gamepad", 0));
		p1->AssignMapping("../data/input/mapping.json");

		Input::InputController* p2 = EngineInput.CreateInputControl("Player2"); //Configuracion B
		p2->RegisterDevice(new DeviceKeyboard("keyboard"));
		p2->RegisterDevice(new DeviceMouse("mouse"));
		//p2->RegisterDevice(new CDevicePadXbox("gamepad", 1));
		p2->AssignMapping("../data/input/mapping.json");
	}

	void OnDetach() {

	}

	void OnInspect() override {

	}

};


REGISTER_LAYER("ControllerLayer", ControllerLayer)
