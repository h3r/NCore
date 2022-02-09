#pragma once
#include <xhash>

namespace NC
{
  class CUUID
  {
  public:
    CUUID();
    CUUID(uint64_t uuid);
    CUUID(const CUUID&) = default;

    operator uint64_t() const { return m_uuid; }
  private:
    uint64_t m_uuid;
  };
}

namespace std {
  
  template<>
  struct hash<NC::CUUID> {
     
    std::size_t operator()(const NC::CUUID& _uuid) const {
      return hash<uint64_t>()((uint64_t)_uuid);
    }

  };

}
