#include "TCPSinkFactory.h"
#include <iostream>

std::shared_ptr<spdlog::sinks::tcp_sink_mt> TCPSinkFactory::tcpSink;

std::shared_ptr<spdlog::sinks::tcp_sink_mt> TCPSinkFactory::GetTCPSink(const std::string& host, int port) {
	if (!tcpSink) {
		try {
			spdlog::sinks::tcp_sink_config tcp_config(host, port);
			tcpSink = std::make_shared<spdlog::sinks::tcp_sink_mt>(tcp_config);
		}
		catch (const spdlog::spdlog_ex& e) {
			std::cerr << "Warning: Failure to create TCP Sink: " << e.what() << std::endl;
			tcpSink = nullptr;
		}
	}
	return tcpSink;
}

void TCPSinkFactory::reset() {
	tcpSink.reset();
}