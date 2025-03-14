#include "HTTPLogger.h"
#include "LogHelper.h"

HTTPLogger::HTTPLogger(std::shared_ptr<spdlog::logger> logger, std::shared_ptr<IHttpClient> httpClient, const std::string& serverUrl, const std::string& hostname, const std::string& ipaddress)
    : logger(logger), httpClient(httpClient), serverUrl(serverUrl), hostname(hostname), ipaddress(ipaddress) {
    if (!logger || !httpClient) {
        throw std::invalid_argument("Logger and HttpClient instances cannot be null");
    }
}

void HTTPLogger::log(const std::string& level, const std::string& message) {
    if (!logger) return;

    std::string logMessage = LogHelper::formatLogMessage(level, message, hostname, ipaddress);

    // Send log via HTTP
    bool success = httpClient->sendLog(serverUrl, logMessage);
    if (!success) {
        logger->error("Failed to send log to HTTP server: {}", serverUrl);
    }

    // Also log to console & file
    logger->info(logMessage);
}
