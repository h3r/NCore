#include "ncpch.h"
#include "layer.h"
#include "core/log.h"
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

  void OnEvent(NC::TEvent& event) {
    //log_trace("TEvent: {}", event);
  }

};


REGISTER_LAYER("sample", CSampleLayer)
