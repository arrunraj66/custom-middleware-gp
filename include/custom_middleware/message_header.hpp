#pragma once

#include <chrono>
#include <cstdint>
#include <string>

namespace custom_middleware
{

struct MessageHeader
{
    std::string topic;
    std::uint64_t sequence_number{0};
    std::chrono::system_clock::time_point timestamp{};
};

}