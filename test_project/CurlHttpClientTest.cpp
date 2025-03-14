#include <gtest/gtest.h>
#include "CurlHttpClient.h"

class CurlHttpClientIntegrationTest : public ::testing::Test {
protected:
    std::shared_ptr<CurlHttpClient> httpClient;

    void SetUp() override {
        httpClient = std::make_shared<CurlHttpClient>();
    }
};


TEST_F(CurlHttpClientIntegrationTest, SendLog_InvalidURL) {
    std::string invalidUrl = "http://localhost:1234";
    std::string testPayload = R"({"level": "error", "message": "Invalid server test"})";

    bool result = httpClient->sendLog(invalidUrl, testPayload);
    EXPECT_FALSE(result) << "Expected sendLog() to fail due to invalid URL.";
}
