#pragma once
using namespace glm;
mat4 camera(float _translate, vec2 const& rotate)
{
  mat4 projection = perspective(radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  mat4 view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -_translate)) *
     rotate(mat4(1.0f), radians(rotate.x), vec3(1.0f, 0.0f, 0.0f)) *
     rotate(mat4(1.0f), radians(rotate.y), vec3(0.0f, 1.0f, 0.0f));
  mat4 model = scale(mat4(1.0f), vec3(0.5f));
  return projection * view * model;
}