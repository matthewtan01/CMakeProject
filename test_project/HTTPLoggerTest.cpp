#include <gtest/gtest.h>
#include "HTTPLogger.h"
#include "MockHttpClient.h"
#include "MockSink.h"

using ::testing::_;
using ::testing::Return;

class HTTPLoggerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockHttpClient> mockHttpClient;
    std::shared_ptr<MockSink> mockSink;
    std::shared_ptr<spdlog::logger> testLogger;
    std::shared_ptr<HTTPLogger> httpLogger;

    void SetUp() override {
        mockHttpClient = std::make_shared<MockHttpClient>();
        mockSink = std::make_shared<MockSink>();
        testLogger = std::make_shared<spdlog::logger>("test_logger", mockSink);
        httpLogger = std::make_shared<HTTPLogger>(testLogger, mockHttpClient, "http://localhost/logs", "TestHost", "127.0.0.1");
    }
};

TEST_F(HTTPLoggerTest, Constructor_ThrowsOnNullLogger) {
    EXPECT_THROW(HTTPLogger(nullptr, mockHttpClient, "http://localhost/logs", "TestHost", "127.0.0.1"), std::invalid_argument);
}

TEST_F(HTTPLoggerTest, Constructor_ThrowsOnNullHttpClient) {
    EXPECT_THROW(HTTPLogger(testLogger, nullptr, "http://localhost/logs", "TestHost", "127.0.0.1"), std::invalid_argument);
}

TEST_F(HTTPLoggerTest, Log_SuccessfulHttpCall) {
    EXPECT_CALL(*mockHttpClient, sendLog("http://localhost/logs", _))
        .Times(1)
        .WillOnce(Return(true)); // Simulate HTTP success

    EXPECT_CALL(*mockSink, log(_)).Times(1); // Log should be forwarded

    httpLogger->log("info", "Test log message");
}

TEST_F(HTTPLoggerTest, Log_FailedHttpCall) {
    EXPECT_CALL(*mockHttpClient, sendLog("http://localhost/logs", _))
        .Times(1)
        .WillOnce(Return(false)); // Simulate HTTP failure

    EXPECT_CALL(*mockSink, log(_)).Times(2); // One for log message, one for error

    httpLogger->log("info", "Test log message");
}