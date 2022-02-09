#pragma once
#include "core/core.h"

namespace NC {

  struct IDComponent
  {
    CUUID id;
    IDComponent() = default;
    IDComponent(const IDComponent&) = default;
  };

  struct TagComponent
  {
    std::string tag;
    TagComponent() = default;
    TagComponent(const TagComponent&) = default;
    TagComponent(const std::string& _tag)
      : tag(_tag) {}
  };

  struct TransformComponent
  {
    glm::mat4x4 transform;
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    TransformComponent(const glm::mat4& _transform)
      : transform(_transform) {}

    operator glm::mat4& () { return transform; }
    operator const glm::mat4& () const { return transform; }

    static void onUpdate(entt::registry& _registry, entt::entity _entity){}
    static void onDestroy(entt::registry& _registry, entt::entity _entity){}
    static void onConstruct(entt::registry& _registry, entt::entity _entity){}
  };
  //m_registry.on_construct<TransformComponent>().connect<&TransformComponent::onConstruct>();
  //m_registry.on_destroy<TransformComponent>().connect<&TransformComponent::onUpdate>();
  //m_registry.on_update<TransformComponent>().connect<&TransformComponent::onDestroy>();

  struct MeshComponent
  {
    std::uint32_t id;
    MeshComponent() = default;
  };


}
