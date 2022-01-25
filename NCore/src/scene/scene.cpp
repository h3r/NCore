#include "ncpch.h"
#include "scene.h"
#include "entity.h"
#include "components.h"

namespace NC {

CScene::CScene() {}

CEntity CScene::CreateEntity(const std::string &_name) {
  CEntity entity = { m_registry.create(), this };
  entity.AddComponent<IDComponent>();
  entity.AddComponent<TransformComponent>();
  auto& tag = entity.AddComponent<TagComponent>();
  tag.tag = _name.empty() ? "Entity" : _name;
  return entity;
}

CEntity CScene::CreateEntityWithUUID(const std::string& _name, CUUID _uuid) {
  CEntity entity = { m_registry.create(), this };
  entity.AddComponent<IDComponent>(_uuid);
  entity.AddComponent<TransformComponent>();
  auto& tag = entity.AddComponent<TagComponent>();
  tag.tag = _name.empty() ? "Entity" : _name;
  return entity;
}

void CScene::DestroyEntity(CEntity _entity)
{
  m_registry.destroy(_entity);
}


CScene::~CScene() {}

} // namespace NC
