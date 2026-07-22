#pragma once
#include "../../renderer/renderer.h"

// NO RGB STRUCT HERE - Use from renderer.h instead

struct SkeletonConfig {
    bool enabled = true;
    float line_thickness = 1.5f;            // 0.5 to 3.0
    RGB line_color = { 0, 255, 255, 255 }; // Cyan
    RGB joint_color = { 255, 255, 0, 255 }; // Yellow
    int joint_size = 2;
    bool draw_joints = true;
    bool draw_lines = true;
};
