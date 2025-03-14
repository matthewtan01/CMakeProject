#include <gtest/gtest.h>
#include "TCPSinkFactory.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/tcp_sink.h>
#include <sstream>

class TCPSinkFactoryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset before each test to ensure a fresh state
        TCPSinkFactory::reset();
    }
};

TEST_F(TCPSinkFactoryTest, GetTCPSink_ValidHostPort_ReturnsSink) {
    auto sink = TCPSinkFactory::GetTCPSink("127.0.0.1", 5000);
    ASSERT_NE(sink, nullptr) << "Expected a valid TCP sink but got nullptr";
}

TEST_F(TCPSinkFactoryTest, GetTCPSink_InvalidPort_ReturnsNullptr) {
    testing::internal::CaptureStderr();  // Capture error messages
    auto sink = TCPSinkFactory::GetTCPSink("127.0.0.1", 9999);  // Invalid port
    std::string consoleOutput = testing::internal::GetCapturedStderr();

    ASSERT_EQ(sink, nullptr) << "Expected nullptr for an invalid TCP connection";
    EXPECT_NE(consoleOutput.find("Warning: Failure to create TCP Sink"), std::string::npos)
        << "Expected a warning message when TCP Sink creation fails";
}

// Invalid host and port for TCP Connection
TEST_F(TCPSinkFactoryTest, InvalidTCPHostAndPort) {
    EXPECT_NO_THROW(auto sink = TCPSinkFactory::GetTCPSink("127.0.0.1", 1000));
}

TEST_F(TCPSinkFactoryTest, GetTCPSink_ReturnsSameInstance) {
    auto sink1 = TCPSinkFactory::GetTCPSink("127.0.0.1", 5000);
    auto sink2 = TCPSinkFactory::GetTCPSink("127.0.0.1", 5000);

    ASSERT_EQ(sink1, sink2) << "Expected the same TCP sink instance but got different objects";
}


