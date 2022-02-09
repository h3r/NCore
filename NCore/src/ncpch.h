#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <functional>

#include <map>
#include <vector>
#include <unordered_map>

#include <spdlog/fmt/fmt.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

#include <limits>
#include <random>

// VENDORS ---
#include "imgui.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#pragma warning(push, 0)
#include <entt/entt.hpp>
#pragma warning(pop)

// --- vendors

namespace fs = std::filesystem;

#include "math/math.h"
#include "utils/log.h"
#include "utils/time.h"
