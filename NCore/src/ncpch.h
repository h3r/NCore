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

#include "core/core.h"
#include "core/log.h"
#include "math/math.h"

// VENDORS ---
#include "imgui.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
// --- vendors

namespace fs = std::filesystem;

