#include "custom_middleware/message_callback.hpp"

#include <chrono>
#include <iostream>
#include <string>

int main()
{
    bool callback_called = false;
    std::string received_topic;

    custom_middleware::MessageCallback callback =
        [&callback_called, &received_topic](
            const custom_middleware::Message& message)
        {
            callback_called = true;
            received_topic = message.header.topic;
        };

    const custom_middleware::Message message{
        {
            "/lidar/scan",
            1,
            std::chrono::system_clock::now()
        },
        {}
    };

    callback(message);

    if (!callback_called)
    {
        std::cerr << "Test failed: callback was not called\n";
        return 1;
    }

    if (received_topic != "/lidar/scan")
    {
        std::cerr << "Test failed: callback received wrong topic\n";
        return 1;
    }

    std::cout << "MessageCallback test passed\n";
    return 0;
}