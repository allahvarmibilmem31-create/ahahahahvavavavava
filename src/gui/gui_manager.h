#pragma once
#include "../imgui/imgui.h"
#include "../features/esp/esp_styles.h"
#include "../features/aimbot/aimbot.h"
#include "../features/bhop/bhop.h"
#include "../features/glow/glow.h"
#include "../features/skeleton/skeleton.h"
#include "../core/entity_cache.h"
#include <memory>

// Forward declarations - no need for ESP class
class Aimbot;
class BunnyHop;
class Glow;
class SkeletonRenderer;

class GUIManager {
public:
    GUIManager();
    ~GUIManager() = default;
    
    void Render();
    void Update();
    bool IsVisible() const { return visible; }
    void ToggleVisibility() { visible = !visible; }
    
    void SetPointers(Aimbot* aim, BunnyHop* bhop, Glow* glow, SkeletonRenderer* skel) {
        aimbot_ptr = aim;
        bhop_ptr = bhop;
        glow_ptr = glow;
        skeleton_ptr = skel;
    }
    
private:
    // GUI State - Member variables instead of static
    bool visible = true;
    ImVec2 window_size = { 550, 700 };
    int active_tab = 0;
    
    // ESP Settings
    bool esp_enabled = true;
    float esp_distance = 300.0f;
    int box_style = 2;
    bool draw_health = true;
    bool draw_skeleton = false;
    bool draw_name = true;
    bool draw_distance = false;
    float enemy_color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float ally_color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    
    // Aimbot Settings
    bool aimbot_enabled = false;
    int aim_mode = 0;
    float smoothness = 0.5f;
    float fov = 20.0f;
    bool prediction = false;
    bool visible_only = true;
    
    // Bhop Settings
    bool bhop_enabled = false;
    bool auto_strafe = true;
    float jump_height = 65.0f;
    
    // Glow Settings
    bool glow_enabled = false;
    float glow_intensity = 1.0f;
    bool glow_visible_only = false;
    bool glow_through_walls = true;
    float enemy_glow[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    float ally_glow[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    
    // Skeleton Settings
    bool skeleton_enabled = true;
    float line_thickness = 1.5f;
    bool draw_joints = true;
    float skeleton_color[4] = { 0.0f, 1.0f, 1.0f, 1.0f };
    
    // General Settings
    int fps_limit = 120;
    bool show_debug = false;
    
    // Feature pointers
    Aimbot* aimbot_ptr = nullptr;
    BunnyHop* bhop_ptr = nullptr;
    Glow* glow_ptr = nullptr;
    SkeletonRenderer* skeleton_ptr = nullptr;
    
    // Tab render functions
    void RenderESPTab();
    void RenderAimbotTab();
    void RenderBhopTab();
    void RenderGlowTab();
    void RenderSkeletonTab();
    void RenderSettingsTab();
    void RenderAboutTab();
    
    // Helper functions
    void ApplyStyle();
};
