#pragma once

#include <string>

namespace LogHelper {
    std::string getUtcTime();
    std::string getIpAddress();
    std::string getHostName();
    std::string formatLogMessage(const std::string& level, const std::string& message, const std::string& hostname, const std::string& ipaddress);
}