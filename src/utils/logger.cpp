#define _CRT_SECURE_NO_WARNINGS
#include "logger.h"
#include <Windows.h>
#include <filesystem>

void Logger::Initialize(const std::string& log_file_path) {
    std::lock_guard<std::mutex> lock(log_mutex);

    // Create logs directory if it doesn't exist
    std::filesystem::path log_path(log_file_path);
    std::filesystem::create_directories(log_path.parent_path());

    // Open log file in append mode
    file_stream.open(log_file_path, std::ios::app);
    if (!file_stream.is_open()) {
        OutputDebugStringA("[Logger] Failed to open log file\n");
        file_logging_enabled = false;
    }
    else {
        Log("===== CS2 External ESP Log Started =====");
        file_logging_enabled = true;
    }
}

void Logger::Shutdown() {
    std::lock_guard<std::mutex> lock(log_mutex);
    if (file_stream.is_open()) {
        Log("===== CS2 External ESP Log Ended =====");
        file_stream.close();
    }
}

void Logger::Log(const std::string& message) {
    std::lock_guard<std::mutex> lock(log_mutex);

    // Get timestamp
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&time));

    std::ostringstream oss;
    oss << "[" << buffer << "." << std::to_string(ms.count()).substr(0, 3) << "] " << message;
    std::string formatted = oss.str();

    // Log to console
    if (console_logging_enabled) {
        OutputDebugStringA((formatted + "\n").c_str());
    }

    // Log to file
    if (file_logging_enabled && file_stream.is_open()) {
        file_stream << formatted << "\n";
        file_stream.flush();
    }
}
