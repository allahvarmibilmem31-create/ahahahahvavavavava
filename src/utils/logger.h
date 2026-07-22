#pragma once
#include "../../renderer/renderer.h"
#include <fstream>

// Fix logger - was trying to call methods on string
class Logger {
private:
    std::string log_file_path;
    std::ofstream file_stream;
    std::mutex log_mutex;
    bool console_logging_enabled = true;
    bool file_logging_enabled = false;

public:
    static Logger& Instance() {
        static Logger instance;
        return instance;
    }

    void Initialize(const std::string& log_file) {
        log_file_path = log_file;
        if (file_logging_enabled) {
            file_stream.open(log_file_path, std::ios::app);
        }
    }

    void Shutdown() {
        if (file_stream.is_open()) {
            file_stream.close();
        }
    }

    void Log(const std::string& message) {
        std::lock_guard<std::mutex> lock(log_mutex);
        if (console_logging_enabled) {
            OutputDebugStringA((message + "\n").c_str());
        }
        if (file_logging_enabled && file_stream.is_open()) {
            file_stream << message << "\n";
            file_stream.flush();
        }
    }
};

#define LOG_DEBUG(msg) Logger::Instance().Log(msg)
#define LOG_INFO(msg) Logger::Instance().Log(msg)
#define LOG_WARNING(msg) Logger::Instance().Log(msg)
#define LOG_CRITICAL(msg) Logger::Instance().Log(msg)
#define LOG_ERROR(msg) Logger::Instance().Log(msg)
