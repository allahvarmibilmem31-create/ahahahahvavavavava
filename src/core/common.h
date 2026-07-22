#pragma once

// Standard Library Includes
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <algorithm>
#include <mutex>
#include <queue>
#include <thread>
#include <chrono>
#include <ctime>
#include <array>
#include <map>
#include <unordered_map>

// Suppress MSVC deprecation warnings
#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

// ============================================================================
// Type Definitions
// ============================================================================

// RGB Color Structure - SINGLE DEFINITION
struct RGB {
    float r, g, b;
    
    RGB() : r(1.0f), g(1.0f), b(1.0f) {}
    RGB(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
};

// Vector3 Type Definition
using Vector3 = float[3];

// ============================================================================
// Math Utility Functions
// ============================================================================

namespace math {
    // Clamp function for C++11 compatibility (std::clamp is C++17)
    template<typename T>
    inline T clamp(T value, T minVal, T maxVal) {
        return std::max(minVal, std::min(value, maxVal));
    }

    // Square root wrapper
    inline float sqrt(float value) {
        return std::sqrt(value);
    }

    // Distance calculation
    inline float distance(const Vector3& a, const Vector3& b) {
        float dx = a[0] - b[0];
        float dy = a[1] - b[1];
        float dz = a[2] - b[2];
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
}

// ============================================================================
// Logging Utility
// ============================================================================

#define LOG_ERROR(format, ...) \
    do { \
        printf("[ERROR] " format "\n", ##__VA_ARGS__); \
    } while(0)

#define LOG_INFO(format, ...) \
    do { \
        printf("[INFO] " format "\n", ##__VA_ARGS__); \
    } while(0)

#define LOG_WARNING(format, ...) \
    do { \
        printf("[WARNING] " format "\n", ##__VA_ARGS__); \
    } while(0)

// ============================================================================
// Configuration Structures
// ============================================================================

struct GlowSettings {
    RGB enemy_color;
    RGB ally_color;
    RGB visible_color;
    float opacity;
    
    GlowSettings() 
        : enemy_color(1.0f, 0.0f, 0.0f),      // Red
          ally_color(0.0f, 1.0f, 0.0f),       // Green
          visible_color(0.0f, 0.0f, 1.0f),    // Blue
          opacity(1.0f) {}
};

struct SkeletonConfig {
    RGB line_color;
    RGB joint_color;
    float line_width;
    
    SkeletonConfig()
        : line_color(1.0f, 1.0f, 1.0f),      // White
          joint_color(1.0f, 0.5f, 0.0f),     // Orange
          line_width(1.0f) {}
};

// ============================================================================
// Memory Types
// ============================================================================

using uintptr_t = unsigned long long;
using EntityDataPtr = void*;

// ============================================================================
// Forward Declarations
// ============================================================================

namespace render {
    struct EntityData;
    struct GameData;
}

class ESP;
class Aimbot;
class Glow;
class Skeleton;
class EntityCache;

#endif // COMMON_H
