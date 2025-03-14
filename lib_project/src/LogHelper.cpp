#include "LogHelper.h"
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "nlohmann/json.hpp"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // Link Winsock library
#else
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif

namespace LogHelper {
    std::string getUtcTime() {
        // Get the current system time
        auto now = std::chrono::system_clock::now();

        // Convert to time_t for UTC conversion
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm utc_tm{};

#ifdef _WIN32
        gmtime_s(&utc_tm, &now_c);  // Windows version of gmtime
#else
        gmtime_r(&now_c, &utc_tm);  // Linux/macOS version of gmtime
#endif

        // Convert to string
        std::ostringstream oss;
        oss << std::put_time(&utc_tm, "%Y-%m-%dT%H:%M:%SZ");
        return oss.str();
    }

    // Function to Retrieve Hostname
    std::string getHostName() {
        char hostnameBuffer[256];
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return "Error retrieving host";
        }
        if (gethostname(hostnameBuffer, sizeof(hostnameBuffer)) == SOCKET_ERROR) {
            std::cerr << "gethostname() failed: " << WSAGetLastError() << std::endl;
            WSACleanup();
            return "Error retrieving host";
        }
        WSACleanup();
#else
        if (gethostname(hostnameBuffer, sizeof(hostnameBuffer)) != 0) {
            perror("gethostname() failed");
            return "Error retrieving host";
        }
#endif
        return std::string(hostnameBuffer);
    }

    // Function to Retrieve IP Address
    std::string getIpAddress() {
        std::string hostname = getHostName();
        if (hostname == "Error retrieving host") {
            return "Error retrieving IP";
        }

        struct addrinfo hints {}, * res;
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return "Error retrieving IP";
        }
#endif

        if (getaddrinfo(hostname.c_str(), nullptr, &hints, &res) != 0) {
            perror("getaddrinfo failed");
#ifdef _WIN32
            WSACleanup();
#endif
            return "Error retrieving IP";
        }

        char ipStr[INET_ADDRSTRLEN];
        struct sockaddr_in* ipv4 = (struct sockaddr_in*)res->ai_addr;
        inet_ntop(AF_INET, &(ipv4->sin_addr), ipStr, INET_ADDRSTRLEN);

        freeaddrinfo(res);
#ifdef _WIN32
        WSACleanup();
#endif

        return std::string(ipStr);
    }

    std::string formatLogMessage(const std::string& level, const std::string& message, const std::string& hostname, const std::string& ipaddress) {
        nlohmann::json logJson = {
            {"@timestamp", getUtcTime()},
            {"level", level},
            {"service", "c++_service"},
            {"message", message},
            {"hostname", hostname},
            {"ipaddress", ipaddress}
         };

        return logJson.dump(); // Convert JSON to a string
    }
}