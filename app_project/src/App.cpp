#include "LoggerFactory.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <random>

// Global flag to control logging
std::atomic<bool> running(true);


std::shared_ptr<TCPLogger> tcpLogger;
std::shared_ptr<HTTPLogger> httpLogger;

// Function to generate random log messages
void simulateContinuousLogging() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 99); // Range 0-99

    while (running) {
        int x = dist(gen);

        if (x < 40) {
            tcpLogger->log("DEBUG", "This is a debug message.");
        }
        else if (x < 70) {
            tcpLogger->log("INFO", "This is an info message.");
        }
        else if (x < 85) {
            tcpLogger->log("WARNING", "This is a warning message.");
        }
        else {
            tcpLogger->log("ERROR", "This is an error message.");
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));  // Log every 2 seconds
    }
}

// Function to listen for user input to stop logging
void waitForExit() {
    std::cout << "Press 'x' to exit the program: ";
    std::string input;
    while (true) {
        std::cin >> input;
        if (input == "x") {
            tcpLogger->log("INFO", "Program Exiting ...");
            running = false;  // Stop logging
            break;
        }
    }
}

int main() {
    // Initialize loggers
    tcpLogger = LoggerFactory::createTCPLogger("192.168.159.136", 5000, "logs.log");
    httpLogger = LoggerFactory::createHTTPLogger("http://192.168.159.136:8080", "logs.log");

    if (!tcpLogger || !httpLogger){
        std::cerr << "Failed to create loggers." << std::endl;
        return 1;
    }

    // Start logging thread
    std::thread logThread(simulateContinuousLogging);

    // Start user input thread
    waitForExit();  // Blocks main thread until user enters 'x'

    // Ensure logging stops before exiting
    if (logThread.joinable()) {
        logThread.join();
    }
    
    httpLogger->log("INFO", "Program ended...");
    // Flush and shutdown loggers before exit
    LoggerFactory::shutDown();
 
    std::cout << "Logging stopped. Program exiting." << std::endl;
    return 0;
}