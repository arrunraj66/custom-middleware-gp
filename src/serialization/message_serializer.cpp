#include "custom_middleware/serialization/message_serializer.hpp"

#include "message_envelope.pb.h"

#include <chrono>
#include <cstdint>
#include <cstring>
#include <limits>
#include <string>


namespace custom_middleware
{

ByteBuffer MessageSerializer::serialize(const Message& message)
{
    proto::MessageEnvelope envelope;

    auto* protobuf_header = envelope.mutable_header();

    protobuf_header->set_topic(message.header.topic);

    protobuf_header->set_sequence_number(
        message.header.sequence_number
    );

    const auto time_since_epoch =
        message.header.timestamp.time_since_epoch();

    const auto seconds =
        std::chrono::duration_cast<std::chrono::seconds>(
            time_since_epoch
        );

    const auto nanoseconds =
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            time_since_epoch - seconds
        );

    auto* protobuf_timestamp =
        protobuf_header->mutable_timestamp();

    protobuf_timestamp->set_seconds(seconds.count());

    protobuf_timestamp->set_nanos(
        static_cast<std::int32_t>(nanoseconds.count())
    );

    if (!message.payload.empty())
    {
        envelope.set_payload(
            message.payload.data(),
            message.payload.size()
        );
    }

    const std::string serialized =
        envelope.SerializeAsString();

    ByteBuffer bytes(serialized.size());

    if (!serialized.empty())
    {
        std::memcpy(
            bytes.data(),
            serialized.data(),
            serialized.size()
        );
    }

    return bytes;
}
std::optional<Message> MessageSerializer::deserialize(
    const ByteBuffer& bytes)
{
    if (bytes.empty())
    {
        return std::nullopt;
    }

    if (bytes.size() >
        static_cast<std::size_t>(
            std::numeric_limits<int>::max()))
    {
        return std::nullopt;
    }

    proto::MessageEnvelope envelope;

    const bool parsed = envelope.ParseFromArray(
        bytes.data(),
        static_cast<int>(bytes.size())
    );

    if (!parsed)
    {
        return std::nullopt;
    }

    if (!envelope.has_header())
    {
        return std::nullopt;
    }

    if (!envelope.header().has_timestamp())
    {
        return std::nullopt;
    }

    const auto& protobuf_timestamp =
        envelope.header().timestamp();

    if ((protobuf_timestamp.nanos() < 0) ||
        (protobuf_timestamp.nanos() >= 1'000'000'000))
    {
        return std::nullopt;
    }

    using ClockDuration =
        std::chrono::system_clock::duration;

    const auto maximum_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(
            ClockDuration::max()
        ).count();

    const auto minimum_seconds =
        std::chrono::duration_cast<std::chrono::seconds>(
            ClockDuration::min()
        ).count();

    if ((protobuf_timestamp.seconds() >= maximum_seconds) ||
        (protobuf_timestamp.seconds() <= minimum_seconds))
    {
        return std::nullopt;
    }

    const auto timestamp_duration =
        std::chrono::duration_cast<ClockDuration>(
            std::chrono::seconds{
                protobuf_timestamp.seconds()
            }
        ) +
        std::chrono::duration_cast<ClockDuration>(
            std::chrono::nanoseconds{
                protobuf_timestamp.nanos()
            }
        );

    Message message;

    message.header.topic =
        envelope.header().topic();

    message.header.sequence_number =
        envelope.header().sequence_number();

    message.header.timestamp =
        std::chrono::system_clock::time_point{
            timestamp_duration
        };

    const std::string& protobuf_payload =
        envelope.payload();

    message.payload.resize(protobuf_payload.size());

    if (!protobuf_payload.empty())
    {
        std::memcpy(
            message.payload.data(),
            protobuf_payload.data(),
            protobuf_payload.size()
        );
    }

    return message;
}

}