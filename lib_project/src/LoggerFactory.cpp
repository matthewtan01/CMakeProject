#include "LoggerFactory.h"
#include "LogHelper.h"
#include "FileSinkFactory.h"
#include "TCPSinkFactory.h"
#include <iostream>

std::shared_ptr<TCPLogger> LoggerFactory::createTCPLogger(
    const std::string& host, 
    int port, 
    const std::string& logFile) 
{
    auto logger = spdlog::get("tcp_logger_" + logFile);
    if (!logger) {
        
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink;
        fileSink = FileSinkFactory::GetFileSink(logFile);

        std::shared_ptr<spdlog::sinks::sink> tcpSink;
		tcpSink = TCPSinkFactory::GetTCPSink(host, port);
        
        std::vector<spdlog::sink_ptr> sinks = { fileSink };

        if (tcpSink) {
            sinks.push_back(tcpSink);
        }
        
        logger = std::make_shared<spdlog::logger>("tcp_logger_" + logFile, sinks.begin(), sinks.end());
        logger->set_pattern("%v");
        logger->set_level(spdlog::level::info);
        logger->flush_on(spdlog::level::err);
        spdlog::register_logger(logger);
    }

    std::string hostname = LogHelper::getHostName();
    std::string ipaddress = LogHelper::getIpAddress();

    return std::make_shared<TCPLogger>(logger, hostname, ipaddress);
}

std::shared_ptr<HTTPLogger> LoggerFactory::createHTTPLogger(const std::string& serverUrl, const std::string& logFile) {
    auto logger = spdlog::get("http_logger_" + logFile);
    if (!logger) {
        std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink;
        fileSink = FileSinkFactory::GetFileSink(logFile);

        std::vector<spdlog::sink_ptr> sinks = {fileSink};
        logger = std::make_shared<spdlog::logger>("http_logger", sinks.begin(), sinks.end());
        logger->set_level(spdlog::level::info);
        logger->set_pattern("%v");
        spdlog::register_logger(logger);
    }
    std::string hostname = LogHelper::getHostName();
    std::string ipaddress = LogHelper::getIpAddress();

    return std::make_shared<HTTPLogger>(logger, std::make_shared<CurlHttpClient>(), serverUrl, hostname, ipaddress);
}

void LoggerFactory::shutDown() {
    spdlog::shutdown();
}
