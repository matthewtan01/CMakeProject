#pragma once

#include <memory>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/logger.h>

class TCPLogger {
public:
    TCPLogger(std::shared_ptr<spdlog::logger> logger, const std::string& hostname, const std::string& ipaddress);
    void log(const std::string& level, const std::string& message);

private:
    std::shared_ptr<spdlog::logger> logger;
    std::string hostname;
    std::string ipaddress;
};
