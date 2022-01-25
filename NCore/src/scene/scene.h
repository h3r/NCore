#pragma once
// This ignores all warnings raised inside External headers
#include "core/uuid.h"

#pragma warning(push, 0)
#include <entt/entt.hpp>
#pragma warning(pop)


namespace NC {

class CEntity;

class CScene {

public:
  CScene();
  ~CScene();

  CEntity CreateEntity(const std::string& _name = std::string());
  CEntity CreateEntityWithUUID(const std::string& _name, CUUID _uuid);

  void DestroyEntity(CEntity _entity);

  template<typename T>
  static void OnComponentAdded(CEntity _entity, T& _component);

  entt::registry &Reg() { return m_registry; }

private:
  entt::registry m_registry;
  friend class CEntity;
};

} // namespace NC
