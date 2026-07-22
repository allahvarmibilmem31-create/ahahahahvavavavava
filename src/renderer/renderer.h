#pragma once
#include <vector>
#include <functional>
#include <mutex>
#include <algorithm>
#include <cmath>
#include "../math/vector.h"
#include "../core/entity_cache.h"

// Single RGB struct definition - ONLY HERE
struct RGB {
    int R, G, B, A;
};

namespace render {
    void DrawRect(int x, int y, int w, int h, RGB color, float thickness);
    void DrawFilledRect(int x, int y, int w, int h, RGB color);
    void DrawLine(float x1, float y1, float x2, float y2, RGB color, float thickness);
    void DrawText(int x, int y, RGB color, const char* text);
    void DrawCircle(int x, int y, int radius, RGB color, float thickness, int segments = 12);
    void DrawFilledCircle(int x, int y, int radius, RGB color, int segments = 12);
    // FIXED: Use global EntityData and GameData, not render:: namespace
    void DrawESP(const std::vector<EntityData>& entities, const GameData& game_data);
    void DrawDebugInfo(const GameData& game_data, size_t entity_count);
}

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void QueueRender(std::function<void()> task);
    void ProcessRenderQueue();
    void ClearQueue();
    
    size_t GetQueueSize() const { return render_queue.size(); }
    
private:
    std::vector<std::function<void()>> render_queue;
    mutable std::mutex queue_mtx;
};
