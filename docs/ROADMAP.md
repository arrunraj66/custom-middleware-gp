# Incremental Roadmap

Every milestone must compile, run, and be understood before the next milestone begins.

## 0. Repository foundation

Goal: establish the project rules and empty structure.

Acceptance:

- The repository can be cloned.
- The purpose and boundaries are documented.
- Generated build output is excluded from Git.

## 1. Build system

Goal: build one minimal C++17 executable.

Topics:

- Source file
- Executable target
- Compiler
- Linker
- Build directory
- CMake target

Acceptance:

- Configure succeeds.
- Compilation succeeds without warnings.
- The executable runs successfully.

Alternative to compare:

- Direct g++ command
- Makefile
- CMake target

## 2. Message representation

Goal: represent one middleware message without networking.

Initial information:

- Topic
- Sequence number
- Timestamp
- Payload

Acceptance:

- A message can be constructed.
- Its values can be printed and validated.
- Invalid inputs are rejected or reported.

Alternatives to compare:

- struct versus class
- string payload versus byte payload
- runtime message type versus templates

## 3. Publisher and subscriber contracts

Goal: expose simple public APIs without implementing network transport.

Acceptance:

- A publisher knows its topic.
- A subscriber registers a callback.
- Application code does not depend on transport details.

## 4. In-memory topic bus

Goal: route a published message to matching subscribers in one process.

Acceptance:

- One publisher reaches one subscriber.
- One publisher reaches multiple subscribers.
- Unrelated topics do not receive the message.
- Subscription removal is tested.

## 5. Queues and event loop

Goal: separate publishing from callback execution.

Acceptance:

- Messages enter a bounded queue.
- `spin_once()` processes one unit of work.
- `spin()` processes until shutdown.
- Queue overflow behavior is documented.

## 6. Thread safety and lifecycle

Goal: support producers and consumers safely.

Acceptance:

- Shared state is protected.
- Waiting threads wake correctly.
- Shutdown does not deadlock.
- Thread sanitizer testing is introduced.

## 7. Serialization

Goal: convert normalized messages to bytes and back.

Acceptance:

- Round-trip reconstruction succeeds.
- Version and length fields are validated.
- Corrupt input is rejected safely.

## 8. Transport abstraction

Goal: keep application APIs independent of communication method.

Implementations:

- In-process transport
- ZeroMQ/TCP transport
- UDP transport

Acceptance:

- The same publisher and subscriber application works with different configured transports.

## 9. Recording and playback

Goal: preserve messages for inspection and replay.

Acceptance:

- Metadata is stored in SQLite.
- Large payloads can be stored efficiently.
- Recorded order and timestamps are retained.
- Playback can reproduce the message sequence.

## 10. Simulated 2D LiDAR

Goal: publish normalized scans through the middleware.

Initial profile:

- 276-degree field of view
- 15 Hz
- 1-degree angular resolution
- 0.05 m to 25 m range
- One echo per beam

Acceptance:

- A subscriber receives scans.
- A recorder stores scans.
- A GUI adapter converts polar points into Cartesian coordinates.

## 11. SICK picoScan150 adapter

Goal: replace the simulator source without changing subscribers.

Phases:

- Device commissioning and packet capture
- Ethernet receiver
- Protocol decoder
- Scan-segment assembler
- Timestamp and sequence handling
- Multi-echo and RSSI support
- Comparison with the official SICK driver

Acceptance:

- Simulator and real sensor produce the same normalized public scan type.
