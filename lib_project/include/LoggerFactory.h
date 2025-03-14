#pragma once
#include <memory>
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/tcp_sink.h>
#include "TCPLogger.h"
#include "HTTPLogger.h"
#include "IHttpClient.h"
#include "CurlHttpClient.h"

class LoggerFactory {
public:
    static std::shared_ptr<TCPLogger> createTCPLogger(
        const std::string& host, 
        int port, 
        const std::string& logFile);

    static std::shared_ptr<HTTPLogger> createHTTPLogger(
        const std::string& serverUrl, 
        const std::string& logFile);

    static void shutDown();
};

