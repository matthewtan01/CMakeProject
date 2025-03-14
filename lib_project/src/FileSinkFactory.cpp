#include "FileSinkFactory.h"
#include <filesystem>

std::mutex FileSinkFactory::mutex_;
std::unordered_map<std::string, std::shared_ptr<spdlog::sinks::basic_file_sink_mt>> FileSinkFactory::fileSinks_;

std::shared_ptr<spdlog::sinks::basic_file_sink_mt> FileSinkFactory::GetFileSink(const std::string& logFilePath) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto& sink = fileSinks_[logFilePath];  // Get reference to avoid multiple lookups
    if (!sink) {
        std::filesystem::path logPath(logFilePath);
        std::filesystem::path log_dir = logPath.parent_path();

        if (!log_dir.empty()) {
            try {
                std::filesystem::create_directories(log_dir);
            }
            catch (const std::exception& e) {
                throw std::runtime_error("Failed to create log directory: " + std::string(e.what()));
            }
        }

        sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath, false);
    }
    return sink;
}

void FileSinkFactory::ClearFileSinks() {
    std::lock_guard<std::mutex> lock(mutex_);

    // Drop all registered loggers
    spdlog::drop_all();
    spdlog::shutdown();

    // Remove all file sinks from the map
    fileSinks_.clear();
}