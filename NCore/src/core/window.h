#pragma once

#include "ncpch.h"
#include "events/event.h"

namespace NC {

  struct TWindowProps
  {
      std::string title;
      unsigned int width;
      unsigned int height;

      TWindowProps(const std::string& _title = "NCore Engine",
                   unsigned int _width = 1280,
                   unsigned int _height = 720)
          : title(_title), width(_width), height(_height) 
      {}
  };

  class NC_API CWindow {
  public:
      using FnEventCallback = std::function<void(Event&)>;
    
      virtual ~CWindow() {}

      virtual void OnUpdate() = 0;

      virtual unsigned int GetWidth()  const = 0;
      virtual unsigned int GetHeight() const = 0;

      // Window attributes
      virtual void SetEventCallback(const FnEventCallback& _callback) = 0;
      virtual void SetVSync(bool _enabled) = 0;
      virtual bool IsVSync() const = 0;
      virtual void* GetNativeWindow() const = 0;

      static CWindow* Create(const TWindowProps& props = TWindowProps());
  };

}
