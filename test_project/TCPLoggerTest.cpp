#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <spdlog/logger.h>
#include "TCPLogger.h"
#include "MockSink.h"

using ::testing::_;
using ::testing::Invoke;

class TCPLoggerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockSink> mockSink;
    std::shared_ptr<spdlog::logger> testLogger;
    std::shared_ptr<TCPLogger> tcpLogger;

    void SetUp() override {
        mockSink = std::make_shared<MockSink>();
        testLogger = std::make_shared<spdlog::logger>("test_logger", mockSink);
        tcpLogger = std::make_shared<TCPLogger>(testLogger, "TestHost", "127.0.0.1");
    }
};

TEST_F(TCPLoggerTest, Constructor_ThrowsOnNullLogger) {
    EXPECT_THROW(TCPLogger(nullptr, "TestHost", "127.0.0.1"), std::invalid_argument);
}

TEST_F(TCPLoggerTest, LogInfo_ForwardsToSink) {
    EXPECT_CALL(*mockSink, log(_)).Times(1);

    tcpLogger->log("info", "Test message");
}

TEST_F(TCPLoggerTest, LogError_ForwardsToSink) {
    EXPECT_CALL(*mockSink, log(_)).Times(1);

    tcpLogger->log("error", "Critical error occurred");
}

