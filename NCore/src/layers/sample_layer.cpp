#include "ncpch.h"
#include "layer.h"
#include "core/core.h"
#include "events/event.h"


class CSampleLayer : public Layer
{
public:
  CSampleLayer(): Layer("SampleLayer") {
    log_info("Constructor");
  }
  ~CSampleLayer() {}

  void OnUpdate() override
  {
    log_info(m_name);
  }

  void OnEvent(NC::Event& event) {
    //log_trace("Event: {}", event);
  }

};


REGISTER_LAYER("sample", CSampleLayer)
