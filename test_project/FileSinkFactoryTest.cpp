#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <FileSinkFactory.h>

namespace fs = std::filesystem;

class FileSinkFactoryTest : public ::testing::Test {
protected:
	std::string logDir = "logs";
	std::string logFile = logDir + "/tcp_logs.log";
	std::string anotherLogFile = logDir + "/http_logs.log";
	std::shared_ptr<spdlog::sinks::basic_file_sink_mt> fileSink;

	void SetUp() override {
		FileSinkFactory::ClearFileSinks();
		if (fs::exists(logFile)) fs::remove(logFile);
		if (fs::exists(anotherLogFile)) fs::remove(anotherLogFile);
		if (fs::exists(logDir)) fs::remove(logDir);
	}
};

TEST_F(FileSinkFactoryTest, CreatesLogDirectoryAndFile) {
	EXPECT_NO_THROW(fileSink =FileSinkFactory::GetFileSink("logs/tcp_logs.log")) << "Exception when creating File Sink";
	EXPECT_TRUE(fs::exists(logDir)) << "Log directory not created";
	EXPECT_TRUE(fs::exists(logFile)) << "Log file was not created";
}


TEST_F(FileSinkFactoryTest, ReturnsSameSinkForSameFile) {
    auto sink1 = FileSinkFactory::GetFileSink(logFile);
    auto sink2 = FileSinkFactory::GetFileSink(logFile);
    ASSERT_EQ(sink1, sink2) << "Expected the same sink instance for the same file";
}

TEST_F(FileSinkFactoryTest, ReturnsDifferentSinkForDifferentFiles) {
    auto sink1 = FileSinkFactory::GetFileSink(logFile);
    auto sink2 = FileSinkFactory::GetFileSink(anotherLogFile);
    ASSERT_NE(sink1, sink2) << "Expected different sink instances for different log files";
}

TEST_F(FileSinkFactoryTest, WritesLogMessageToFile) {
	auto sink = FileSinkFactory::GetFileSink(logFile);
	sink->log(spdlog::details::log_msg(spdlog::source_loc{}, "test_logger", spdlog::level::info, "test message"));
	sink->flush();
	std::ifstream file(logFile);
	ASSERT_TRUE(file.is_open()) << "Failed to open log file";

	std::string content;
	std::getline(file, content);
	file.close();
	// content.find(msg) returns std::string::npos if msg is not found in content
	EXPECT_NE(content.find("test message"), std::string::npos)
		<< "Log message was not written to file";
}