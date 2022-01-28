#pragma once

#include "core/window.h"
#include "render/context.h"

struct GLFWwindow;
 
namespace NC {
	class GraphicsContext;
  class CWinWindow : public CWindow {

  public:
    CWinWindow(const TWindowProps& props);
    virtual ~CWinWindow();

    void OnUpdate() override;

    inline unsigned int GetWidth()  const override { return m_data.width; };
    inline unsigned int GetHeight() const override { return m_data.width; };

    // Window attributes
    inline void SetEventCallback(const FnEventCallback& _callback) override { m_data.callback = _callback; };
    void SetVSync(bool _enabled) override;
    bool IsVSync() const override;
    void* GetNativeWindow() const { return m_window; };

  private:
    virtual void Init(const TWindowProps& _props);
    virtual void Stop();
  
  private:
    GLFWwindow* m_window;
		GraphicsContext* m_context;

    struct TWindowData {
      std::string title;
      unsigned int width, height;
      bool vsync;
      FnEventCallback callback;
    };
    TWindowData m_data;
  };

}

