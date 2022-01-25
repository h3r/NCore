#include "ncpch.h"
#include "uuid.h"

namespace NC
{
  static std::random_device s_random_device;
  static std::mt19937_64 s_engine(s_random_device());
  static std::uniform_int_distribution<uint64_t> s_uniform_distribution;

  CUUID::CUUID()
    : m_uuid(s_uniform_distribution(s_engine))
  {
  }

  CUUID::CUUID(uint64_t _uuid)
    : m_uuid(_uuid)
  {
  
  }
}
