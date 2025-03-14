#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <mutex>
#include <unordered_map>

class FileSinkFactory {
public:
	static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> GetFileSink(const std::string& logFilePath);
	static void ClearFileSinks();

private:
	static std::mutex mutex_;
	static std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::basic_file_sink_mt>> fileSinks_;
};