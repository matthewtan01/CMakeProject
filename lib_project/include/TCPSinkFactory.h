#pragma once

#include <spdlog/sinks/tcp_sink.h>

class TCPSinkFactory {
public:
	static std::shared_ptr<spdlog::sinks::tcp_sink_mt> GetTCPSink(const std::string& host, int port);
	static void reset();
private:
	static std::shared_ptr < spdlog::sinks::tcp_sink_mt> tcpSink;
};