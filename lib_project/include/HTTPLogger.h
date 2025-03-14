#pragma once
#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include "IHttpClient.h"

class HTTPLogger {
public:
    HTTPLogger(std::shared_ptr<spdlog::logger> logger, std::shared_ptr<IHttpClient> httpClient, const std::string& serverUrl, const std::string& hostname, const std::string& ipaddress);
    void log(const std::string& level, const std::string& message);

private:
    std::shared_ptr<spdlog::logger> logger;
    std::shared_ptr<IHttpClient> httpClient;
    std::string serverUrl;
    std::string hostname;
    std::string ipaddress;
};
