#pragma once
#include "core/log.h"
#include "core/core.h"

namespace NC {

  enum EventCategory
  {
    None = 0,
    EventCategoryApplication = BIT(0),
    EventCategoryInput = BIT(1),
    EventCategoryKeyboard = BIT(2),
    EventCategoryMouse = BIT(3),
    EventCategoryMouseButton = BIT(4),
    EventCategoryImGui = BIT(5),
  };

  static uint32_t GetNextUniqueTypeID() {
    static uint32_t unique_msg_id = 0;
    ++unique_msg_id;
    return unique_msg_id;
  }

  typedef uint32_t EventType;
  struct NC_API Event {
    bool m_handled = false;

    virtual ~Event() = default;

    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual EventType GetEventType() const = 0;

    virtual std::string ToString() const {
      return GetName();
    }

    bool IsInCategory(EventCategory _category) {
      return GetCategoryFlags() & _category;
    }
  };

  inline std::ostream& operator<<(std::ostream& _os, const Event& _e) {
    return _os << _e.ToString();
  }

#define DECLARE_EVENT(type, category)          		                           \
		static EventType GetStaticType() {                                       \
			static uint32_t msg_id = GetNextUniqueTypeID();                        \
			return msg_id;                                                         \
		}                                                                        \
		virtual EventType GetEventType()const override { return GetStaticType();}\
		virtual const char* GetName()   const override { return #type; } 	       \
		virtual int GetCategoryFlags()  const override { return category; }      \


  class NC_API CEventDispatcher {
  public:
    CEventDispatcher(Event& _event)
      : m_event(_event) {}

    // F will be deduced by the compiler
    template<typename T, typename F>
    bool Dispatch(const F& _func) {
      if (m_event.GetEventType() == T::GetStaticType()) {
        m_event.m_handled |= _func(static_cast<T&>(m_event));
        return true;
      }
      return false;
    }

  private:
    Event& m_event;

  };

  class EventManager {

    //Hacks para guardarme un puntero a una clase templatizada
    struct IMsgBaseCallback {
      virtual void trigger(const void* msg) = 0;
    };

    struct TCallbackSlot {
      std::string m_sender = "";
      std::string m_observer = "";
      IMsgBaseCallback* m_callback = nullptr;
    };

    template< typename TMsg >
    struct TMsgCallback : public IMsgBaseCallback {
      // La signature de un metodo de la class TComp que recibe
      // como argumento una referencia a una instancia de TMsg
      // y que no devuelve nada.
      typedef void (*TMethodCallback)(const TMsg&);
      using Signature = std::function<void(const TMsg&)>;

      // Una instancia de un puntero a uno de esos metodos
      Signature m_method;
      TMsgCallback(Signature new_method) : m_method(new_method){}

      void trigger(const void* generic_msg) override {
        const TMsg* msg = static_cast<const TMsg*>(generic_msg);
        //nc_assert( (int)m_method !=nullptr, " ");
        m_method(*msg);
      }
    };

    inline static std::unordered_map < std::string, std::unordered_multimap<uint32_t, TCallbackSlot> > all_events;

  public:
    EventManager() {}

    template< typename TMsg, typename TMethod >
    static void bind(std::string sender, std::string observer, TMethod method)
    {
      auto it = all_events.find(sender);
      if (it == all_events.end())
        all_events.emplace(sender, std::unordered_multimap<uint32_t, TCallbackSlot>());

      auto id = TMsg::GetStaticType();
      all_events[sender].emplace(
        id,
        TCallbackSlot({ sender, observer, new TMsgCallback<TMsg>(method) })
      );
    }

    template< typename TMsg >
    static void unbind(std::string sender, std::string observer)
    {
      auto it = all_events.find(sender);
      if (it == all_events.end())
        return;

      //remove all if observer not provided
      if (observer.empty()) {
        all_events[sender].clear();
        all_events.erase(sender);
        return;
      }

      auto result = all_events[sender].equal_range(TMsg::GetStaticType());
      auto iter = result.first;
      for (; iter != result.second; )
        iter = (iter->second.m_observer == observer) ? all_events[sender].erase(iter) : ++iter;

    }

    template< typename TMsg >
    static void trigger(std::string sender, const void* generic_msg = nullptr) {
      const auto id = TMsg::GetStaticType();
      #ifndef NDEBUG
      //Special tracking to avoid callback hell issues
      static bool msg_being_triggered = false;
      static std::pair< uint32_t, std::string > msg;

      if (!msg_being_triggered) {
        msg_being_triggered = true;
        msg = std::make_pair(id, sender);
      }
      else {
        //nc_assert(msg.first != id && msg.second != sender, "[Error] Triggering same event from same origin while resolving an event trigger!");
      }
      #endif

      auto it = all_events.find(sender);
      if (it != all_events.end()) {
        auto result = it->second.equal_range(id);
        for (auto& it = result.first; it != result.second; it++) {
          it->second.m_callback->trigger(generic_msg);
        }
      }
      #ifndef NDEBUG
            msg_being_triggered = false;
      #endif
    }

  };

}
