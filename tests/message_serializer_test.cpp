#include "custom_middleware/serialization/message_serializer.hpp"

#include "message_envelope.pb.h"

#include <chrono>
#include <cstddef>
#include <iostream>
#include <string>

int main()
{
    using namespace std::chrono;

    const auto timestamp =
        system_clock::time_point{} +
        seconds{1'700'000'000} +
        nanoseconds{123'456'789};

    const custom_middleware::Message message{
        {
            "/lidar/scan",
            42,
            timestamp
        },
        {
            std::byte{0x01},
            std::byte{0x7F},
            std::byte{0xFF}
        }
    };

    const custom_middleware::ByteBuffer bytes =
        custom_middleware::MessageSerializer::serialize(message);

    if (bytes.empty())
    {
        std::cerr << "Test failed: serialized buffer is empty\n";
        return 1;
    }

    custom_middleware::proto::MessageEnvelope envelope;

    const bool parsed = envelope.ParseFromArray(
        bytes.data(),
        static_cast<int>(bytes.size())
    );

    if (!parsed)
    {
        std::cerr << "Test failed: Protobuf parsing failed\n";
        return 1;
    }

    if (!envelope.has_header())
    {
        std::cerr << "Test failed: header is missing\n";
        return 1;
    }

    if (envelope.header().topic() != "/lidar/scan")
    {
        std::cerr << "Test failed: incorrect topic\n";
        return 1;
    }

    if (envelope.header().sequence_number() != 42)
    {
        std::cerr << "Test failed: incorrect sequence number\n";
        return 1;
    }

    if (!envelope.header().has_timestamp())
    {
        std::cerr << "Test failed: timestamp is missing\n";
        return 1;
    }

    if (envelope.header().timestamp().seconds() != 1'700'000'000)
    {
        std::cerr << "Test failed: incorrect timestamp seconds\n";
        return 1;
    }

    if (envelope.header().timestamp().nanos() != 123'456'789)
    {
        std::cerr << "Test failed: incorrect timestamp nanoseconds\n";
        return 1;
    }

    const std::string expected_payload{
        "\x01\x7F\xFF",
        3
    };

    if (envelope.payload() != expected_payload)
    {
        std::cerr << "Test failed: incorrect binary payload\n";
        return 1;
    }

      const auto restored_message =
        custom_middleware::MessageSerializer::deserialize(bytes);

    if (!restored_message.has_value())
    {
        std::cerr << "Test failed: deserialization failed\n";
        return 1;
    }

    if (restored_message->header.topic != message.header.topic)
    {
        std::cerr << "Test failed: round-trip topic mismatch\n";
        return 1;
    }

    if (restored_message->header.sequence_number !=
        message.header.sequence_number)
    {
        std::cerr
            << "Test failed: round-trip sequence number mismatch\n";
        return 1;
    }

    if (restored_message->header.timestamp !=
        message.header.timestamp)
    {
        std::cerr << "Test failed: round-trip timestamp mismatch\n";
        return 1;
    }

    if (restored_message->payload != message.payload)
    {
        std::cerr << "Test failed: round-trip payload mismatch\n";
        return 1;
    }

    const custom_middleware::ByteBuffer empty_bytes;

    if (custom_middleware::MessageSerializer::deserialize(
            empty_bytes).has_value())
    {
        std::cerr << "Test failed: empty data was accepted\n";
        return 1;
    }

    const custom_middleware::ByteBuffer corrupted_bytes{
        std::byte{0xFF}
    };

    if (custom_middleware::MessageSerializer::deserialize(
            corrupted_bytes).has_value())
    {
        std::cerr << "Test failed: corrupted data was accepted\n";
        return 1;
    }

    std::cout << "MessageSerializer round-trip test passed\n";
    return 0;
}