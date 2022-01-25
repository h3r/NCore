#pragma once

#include "core/log.h"
#include "core/core.h"
#include "scene/scene.h"
#include "scene/components.h"

class CScene;

/*
  CEntity squareEntity = { square, m_active_scene};

*/

namespace NC {

  class CEntity {
  public:
    CEntity() = default;
    CEntity(entt::entity handle, CScene* scene);
    CEntity(const CEntity& other) = default;

    template <typename T, typename... Args>
    T& AddComponent(Args &&...args) {
      nc_assert(!HasComponent<T>(), "Entity already has component");
      return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
    }

    template <typename T>
    T& GetComponent() {
      nc_assert(HasComponent<T>(), "Entity does not has component");
      return m_scene->m_registry.get<T>(m_handle);
    }

    template <typename T>
    bool HasComponent() {
      return true;// m_scene->m_registry.has<T>(m_handle);
    }

    template <typename T>
    void RemoveComponent() {
      dbg_assert(HasComponent<T>(), "Entity does not has component");
      m_scene->m_registry.remove<T>(m_handle);
    }

    CUUID GetUUID() { return GetComponent<IDComponent>().id; }

    operator entt::entity() const { return m_handle; }
    operator uint32_t() const { return (uint32_t)m_handle; }
    operator bool() const { return m_handle != entt::null; }
    bool operator!=(const CEntity& other) const { return !(*this == other); }
    bool operator==(const CEntity& other) const { return m_handle == other.m_handle; }

  private:
    entt::entity m_handle{0};
    CScene* m_scene = nullptr;
  };

}  // namespace NC
