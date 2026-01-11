#pragma once

#include <string>

namespace DSA {
namespace Config {

constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr const char* WINDOW_TITLE = "DSA Visualization System";
constexpr unsigned int FPS_LIMIT = 60;
constexpr bool VSYNC_ENABLED = true;

constexpr std::size_t ARRAY_MAX_SIZE = 100;
constexpr int ARRAY_MIN_VALUE = 1;
constexpr int ARRAY_MAX_VALUE = 100;
constexpr std::size_t ARRAY_DEFAULT_SIZE = 10;

constexpr float ANIMATION_SWAP_DURATION_MS = 1200.0f;
constexpr float ANIMATION_COMPARE_DURATION_MS = 800.0f;
constexpr float ANIMATION_MIN_SPEED = 0.25f;
constexpr float ANIMATION_MAX_SPEED = 4.0f;
constexpr float ANIMATION_DEFAULT_SPEED = 0.5f;

constexpr const char* FONT_MAIN_PATH = "fonts/main.ttf";
constexpr const char* FONT_MONOSPACE_PATH = "fonts/monospace.ttf";
constexpr const char* FONT_TITLE_PATH = "fonts/title.ttf";
constexpr const char* ASSETS_BASE_PATH = "assets/";

struct Colors {
    static constexpr unsigned int PRIMARY_R = 44;
    static constexpr unsigned int PRIMARY_G = 62;
    static constexpr unsigned int PRIMARY_B = 80;
    
    static constexpr unsigned int SECONDARY_R = 52;
    static constexpr unsigned int SECONDARY_G = 152;
    static constexpr unsigned int SECONDARY_B = 219;
    
    static constexpr unsigned int ACCENT_R = 231;
    static constexpr unsigned int ACCENT_G = 76;
    static constexpr unsigned int ACCENT_B = 60;
    
    static constexpr unsigned int BACKGROUND_R = 236;
    static constexpr unsigned int BACKGROUND_G = 240;
    static constexpr unsigned int BACKGROUND_B = 241;
    
    static constexpr unsigned int TEXT_R = 44;
    static constexpr unsigned int TEXT_G = 62;
    static constexpr unsigned int TEXT_B = 80;
    
    static constexpr unsigned int SUCCESS_R = 46;
    static constexpr unsigned int SUCCESS_G = 204;
    static constexpr unsigned int SUCCESS_B = 113;
    
    static constexpr unsigned int WARNING_R = 241;
    static constexpr unsigned int WARNING_G = 196;
    static constexpr unsigned int WARNING_B = 15;
};

} 
} 
