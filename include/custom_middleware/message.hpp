#pragma once

#include "custom_middleware/message_header.hpp"

#include <cstddef>
#include <vector>

namespace custom_middleware
{

using ByteBuffer = std::vector<std::byte>;

struct Message
{
    MessageHeader header;
    ByteBuffer payload;
};

}