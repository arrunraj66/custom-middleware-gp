#include "custom_middleware/message_header.hpp"

#include <chrono>
#include <iostream>

int main()
{
    const auto now = std::chrono::system_clock::now();

    const custom_middleware::MessageHeader header{
        "/system/status",
        1,
        now
    };

    if (header.topic != "/system/status")
    {
        std::cerr << "Test failed: incorrect topic\n";
        return 1;
    }

    if (header.sequence_number != 1)
    {
        std::cerr << "Test failed: incorrect sequence number\n";
        return 1;
    }

    if (header.timestamp != now)
    {
        std::cerr << "Test failed: incorrect timestamp\n";
        return 1;
    }

    std::cout << "MessageHeader test passed\n";
    return 0;
}