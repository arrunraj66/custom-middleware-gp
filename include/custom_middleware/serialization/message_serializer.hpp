#pragma once

#include "custom_middleware/message.hpp"

#include <optional>

namespace custom_middleware
{

class MessageSerializer
{
public:
    [[nodiscard]]
    static ByteBuffer serialize(const Message& message);

    [[nodiscard]]
    static std::optional<Message> deserialize(const ByteBuffer& bytes);
};

}