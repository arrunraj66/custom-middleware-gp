#pragma once

#include "custom_middleware/message.hpp"

#include <functional>

namespace custom_middleware
{

using MessageCallback = std::function<void(const Message&)>;

}