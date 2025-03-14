#include <gtest/gtest.h>
#include "LogHelper.h"
#include <regex>
#include <nlohmann/json.hpp>


// Test if getUtcTime() returns a valid ISO 8601 UTC timestamp with a 'Z'
TEST(LogHelperTest, GetUtcTimeReturnsValidISO8601Format) {
    std::string utcTime = LogHelper::getUtcTime();

    // Regular expression for ISO 8601 format: YYYY-MM-DDTHH:MM:SSZ
    std::regex iso8601Regex(R"(\d{4}-\d{2}-\d{2}T\d{2}:\d{2}:\d{2}(\.\d+)?Z)");

    // Check if the generated timestamp matches the expected format
    EXPECT_TRUE(std::regex_match(utcTime, iso8601Regex));
}

// Test if getHostName() returns a valid Host Name
TEST(LogHelperTest, GetValidHostName) {
    std::string hostName = LogHelper::getHostName();
    EXPECT_FALSE(hostName.empty());
    EXPECT_NE(hostName, "Error retrieving host");
}

// Test if getIpAddress() returns a valid IP Address
TEST(LogHelperTest, GetValidIpAddress) {
    std::string ipAddress = LogHelper::getIpAddress();
    EXPECT_FALSE(ipAddress.empty());
    EXPECT_NE(ipAddress, "Error retrieving IP");
}

// Test if formatLogMessage() includes all the required fields
TEST(LogHelperTest, FormatLogMessage_ContainsAllFields) {
    std::string level = "info";
    std::string message = "Test log message";
    std::string hostname = "TestHost";
    std::string ipaddress = "192.168.1.1";

    std::string formattedJson = LogHelper::formatLogMessage(level, message, hostname, ipaddress);

    // Parse the JSON string
    nlohmann::json parsedJson = nlohmann::json::parse(formattedJson);

    // Verify all required fields exist
    EXPECT_TRUE(parsedJson.contains("@timestamp"));
    EXPECT_TRUE(parsedJson.contains("level"));
    EXPECT_TRUE(parsedJson.contains("service"));
    EXPECT_TRUE(parsedJson.contains("message"));
    EXPECT_TRUE(parsedJson.contains("hostname"));
    EXPECT_TRUE(parsedJson.contains("ipaddress"));

    // Check if values match
    EXPECT_EQ(parsedJson["level"], level);
    EXPECT_EQ(parsedJson["service"], "c++_service");
    EXPECT_EQ(parsedJson["message"], message);
    EXPECT_EQ(parsedJson["hostname"], hostname);
    EXPECT_EQ(parsedJson["ipaddress"], ipaddress);
}

// Test if formatLogMessage() handles empty values correctly
TEST(LogHelperTest, FormatLogMessage_HandlesEmptyValues) {
    std::string formattedJson = LogHelper::formatLogMessage("", "", "", "");

    nlohmann::json parsedJson = nlohmann::json::parse(formattedJson);

    // Check if empty values are correctly handled
    EXPECT_EQ(parsedJson["level"], "");
    EXPECT_EQ(parsedJson["message"], "");
    EXPECT_EQ(parsedJson["hostname"], "");
    EXPECT_EQ(parsedJson["ipaddress"], "");
}

