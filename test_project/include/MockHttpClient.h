#pragma once
#include <gmock/gmock.h>
#include "IHttpClient.h"

class MockHttpClient : public IHttpClient {
public:
    MOCK_METHOD(bool, sendLog, (const std::string& url, const std::string& data), (override));
};
