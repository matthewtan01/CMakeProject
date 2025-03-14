#include "TCPLogger.h"
#include "LogHelper.h"


TCPLogger::TCPLogger(std::shared_ptr<spdlog::logger> logger, const std::string& hostname, const std::string& ipaddress) : logger(logger), hostname(hostname), ipaddress(ipaddress) {
    if (!logger) {
        throw std::invalid_argument("Logger instance cannot be null");
    }
}

void TCPLogger::log(const std::string& level, const std::string& message) {
    if (!logger) return;

    std::string formattedMessage = LogHelper::formatLogMessage(level, message, hostname, ipaddress);
    if (level == "error") {
        logger->error(formattedMessage);
    }
    else {
        logger->info(formattedMessage);
    }
}
