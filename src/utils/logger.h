#pragma once
#include <Windows.h>
#include <fstream>
#include <mutex>
#include <string>
#include <sstream>
#include <chrono>
#include <cstdio>

// Simplified logger with no duplicate definitions
class Logger {
private:
    std::ofstream file_stream;
    std::mutex log_mutex;
    bool console_logging_enabled = true;
    bool file_logging_enabled = false;

    Logger() = default;

public:
    static Logger& Instance() {
        static Logger instance;
        return instance;
    }

    // Delete copy constructor/assignment
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void Initialize(const std::string& log_file_path);
    void Shutdown();
    void Log(const std::string& message);
};

#define LOG_DEBUG(msg) Logger::Instance().Log(msg)
#define LOG_INFO(msg) Logger::Instance().Log(msg)
#define LOG_WARNING(msg) Logger::Instance().Log(msg)
#define LOG_CRITICAL(msg) Logger::Instance().Log(msg)
#define LOG_ERROR(msg) Logger::Instance().Log(msg)
