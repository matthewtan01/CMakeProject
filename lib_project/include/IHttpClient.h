#pragma once
#include <string>

class IHttpClient {
public:
    virtual bool sendLog(const std::string& url, const std::string& payload) = 0;
    virtual ~IHttpClient() = default;
};
