#pragma once
#include "core/core.h"

//#define GLM_ENABLE_EXPERIMENTAL
//#include "gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace NC {

  class NC_API CLog {

  public: 
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }

  private:
    static std::shared_ptr<spdlog::logger> s_logger;

  };

}
#pragma warning(pop)


/*template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector) {
  return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix) {
  return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion) {
  return os << glm::to_string(quaternion);
}*/

#ifdef NC_DEBUG
  #define log_trace(...)         ::NC::CLog::GetLogger()->trace(__VA_ARGS__)
  #define log_info(...)          ::NC::CLog::GetLogger()->info(__VA_ARGS__)
  #define log_warn(...)          ::NC::CLog::GetLogger()->warn(__VA_ARGS__)
  #define log_error(...)         ::NC::CLog::GetLogger()->error(__VA_ARGS__)
  #define log_critical(...)      ::NC::CLog::GetLogger()->critical(__VA_ARGS__)
#else
  #define log_trace(...)   
  #define log_info(...)    
  #define log_warn(...)    
  #define log_error(...)   
  #define log_critical(...)
#endif
