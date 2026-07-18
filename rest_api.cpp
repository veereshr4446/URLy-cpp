#include <httplib.h>
#include <json.hpp>
#include <iostream>

using namespace httplib;
using json = nlohmann::json;

int main() {
    Server svr;

    // GET endpoint: /ping — for health checks
    svr.Get("/ping", [](const Request& req, Response& res) {
        json response;
        response["status"] = "alive";
        response["message"] = "URL Shortener is running!";
        res.set_content(response.dump(), "application/json");
    });

    // GET endpoint: /hello — a friendly greeting
    svr.Get("/hello", [](const Request& req, Response& res) {
        json response;
        response["message"] = "Hello from your URL Shortener!";
        res.set_content(response.dump(), "application/json");
    });

    std::cout << "========================================" << std::endl;
    std::cout << "🚀 Server is running on http://localhost:8080" << std::endl;
    std::cout << "🏓 Test: http://localhost:8080/ping" << std::endl;
    std::cout << "👋 Test: http://localhost:8080/hello" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;

    svr.listen("0.0.0.0", 8080);

    return 0;
}