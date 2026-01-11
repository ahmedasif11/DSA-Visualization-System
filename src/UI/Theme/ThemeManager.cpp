/**
 * @file ThemeManager.cpp
 * @brief Implementation of ThemeManager
 */

#include "ThemeManager.h"
#include "../../Core/Resources/ResourceManager.h"
#include "../../Core/Resources/ResourceIDs.h"
#include "../../App/Config.h"
#include <stdexcept>
#include <iostream>

namespace DSA {
namespace UI {

ThemeManager& ThemeManager::getInstance() {
    static ThemeManager instance;
    return instance;
}

ThemeManager::ThemeManager() {
    // Theme is initialized with default values in its constructor
}

void ThemeManager::setTheme(const Theme& theme) {
    m_theme = theme;
    m_fontsLoaded = false; // Invalidate fonts when theme changes
}

const Theme& ThemeManager::getTheme() const {
    return m_theme;
}

bool ThemeManager::loadFonts() {
    if (m_fontsLoaded) {
        return true; // Already loaded
    }
    
    ResourceManager& rm = ResourceManager::getInstance();
    std::string basePath = Config::ASSETS_BASE_PATH;
    
    // Try to load main font
    if (!rm.hasFont(FontID::Main)) {
        if (!rm.loadFont(FontID::Main, m_theme.fontMainPath)) {
            std::cerr << "Warning: Failed to load main font: " << m_theme.fontMainPath << std::endl;
            // Continue without font - text won't display but app won't crash
        }
    }
    
    // Try to load monospace font (optional)
    if (!rm.hasFont(FontID::Monospace)) {
        rm.loadFont(FontID::Monospace, m_theme.fontMonospacePath);
    }
    
    // Try to load title font (optional)
    if (!rm.hasFont(FontID::Title)) {
        rm.loadFont(FontID::Title, m_theme.fontTitlePath);
    }
    
    // Check if fonts are loaded
    if (rm.hasFont(FontID::Main)) {
        m_fontsLoaded = true;
        return true;
    } else {
        std::cerr << "Warning: No main font available. Text may not display." << std::endl;
        m_fontsLoaded = false;
        return false;
    }
}

const sf::Font& ThemeManager::getMainFont() const {
    ResourceManager& rm = ResourceManager::getInstance();
    if (!rm.hasFont(FontID::Main)) {
        throw std::runtime_error("Main font not loaded. Call loadFonts() first.");
    }
    return rm.getFont(FontID::Main);
}

const sf::Font& ThemeManager::getMonospaceFont() const {
    ResourceManager& rm = ResourceManager::getInstance();
    if (rm.hasFont(FontID::Monospace)) {
        return rm.getFont(FontID::Monospace);
    }
    // Fallback to main font
    return getMainFont();
}

const sf::Font& ThemeManager::getTitleFont() const {
    ResourceManager& rm = ResourceManager::getInstance();
    if (rm.hasFont(FontID::Title)) {
        return rm.getFont(FontID::Title);
    }
    // Fallback to main font
    return getMainFont();
}

bool ThemeManager::areFontsLoaded() const {
    ResourceManager& rm = ResourceManager::getInstance();
    return m_fontsLoaded && rm.hasFont(FontID::Main);
}

} // namespace UI
} // namespace DSA
