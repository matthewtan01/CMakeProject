#pragma once
#include <gmock/gmock.h>
#include <spdlog/sinks/sink.h>

class MockSink : public spdlog::sinks::sink {
public:
    MOCK_METHOD(void, log, (const spdlog::details::log_msg& msg), (override));
    MOCK_METHOD(void, flush, (), (override));

    // Override the `set_pattern` and `set_formatter` methods to prevent abstract class errors
    MOCK_METHOD(void, set_pattern, (const std::string& pattern), (override));
    MOCK_METHOD(void, set_formatter, (std::unique_ptr<spdlog::formatter> formatter), (override));
};
