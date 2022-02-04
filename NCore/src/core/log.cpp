#include "ncpch.h"
#include "log.h"

namespace NC {
  
  std::shared_ptr<spdlog::logger> CLog::s_logger;

  void CLog::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_logger = spdlog::stdout_color_mt("NCORE");
    s_logger->set_level(spdlog::level::trace);
  }

}
