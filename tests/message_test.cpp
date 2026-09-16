#include "custom_middleware/message.hpp"

#include <chrono>
#include <cstddef>
#include <iostream>

int main()
{
    const auto now = std::chrono::system_clock::now();

    const custom_middleware::Message message{
        {
            "/system/status",
            1,
            now
        },
        {
            std::byte{0x4F},
            std::byte{0x4B}
        }
    };

    if (message.header.topic != "/system/status")
    {
        std::cerr << "Test failed: incorrect topic\n";
        return 1;
    }

    if (message.payload.size() != 2U)
    {
        std::cerr << "Test failed: incorrect payload size\n";
        return 1;
    }

    if (message.payload[0] != std::byte{0x4F})
    {
        std::cerr << "Test failed: incorrect first byte\n";
        return 1;
    }

    if (message.payload[1] != std::byte{0x4B})
    {
        std::cerr << "Test failed: incorrect second byte\n";
        return 1;
    }

    std::cout << "Message test passed\n";
    return 0;
}