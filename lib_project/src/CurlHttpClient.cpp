#include "CurlHttpClient.h"
#include "httplib.h"
#include <iostream>

bool CurlHttpClient::sendLog(const std::string& url, const std::string& payload) {
	httplib::Client cli(url.c_str());
	auto res = cli.Post("/", payload, "application/json");
	if (!res || res->status != 200) {
		std::cout << "HTTP Failed" << std::endl;
		return false;
	}
	return true;
}
