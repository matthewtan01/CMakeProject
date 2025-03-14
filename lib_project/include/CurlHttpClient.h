#pragma once
#include "IHttpClient.h"

class CurlHttpClient : public IHttpClient {
public:
    bool sendLog(const std::string& url, const std::string& payload) override;
};
