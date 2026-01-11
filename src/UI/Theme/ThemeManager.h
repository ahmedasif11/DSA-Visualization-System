/**
 * @file ThemeManager.h
 * @brief Theme manager for managing themes
 */

#pragma once

#include "Theme.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <unordered_map>

namespace DSA {
namespace UI {

/**
 * @class ThemeManager
 * @brief Manages themes and provides font access
 * 
 * Singleton pattern ensures single theme manager throughout the application.
 */
class ThemeManager {
public:
    /**
     * @brief Get the singleton instance
     * @return ThemeManager& Reference to the theme manager
     */
    static ThemeManager& getInstance();
    
    /**
     * @brief Set the current theme
     * @param theme The theme to use
     */
    void setTheme(const Theme& theme);
    
    /**
     * @brief Get the current theme
     * @return Reference to the current theme
     */
    const Theme& getTheme() const;
    
    /**
     * @brief Load fonts from theme
     * @return true if fonts loaded successfully
     */
    bool loadFonts();
    
    /**
     * @brief Get main font (from ResourceManager)
     * @return Reference to the main font
     * @throws std::runtime_error if font is not loaded
     */
    const sf::Font& getMainFont() const;
    
    /**
     * @brief Get monospace font (from ResourceManager)
     * @return Reference to the monospace font
     * @throws std::runtime_error if font is not loaded
     */
    const sf::Font& getMonospaceFont() const;
    
    /**
     * @brief Get title font (from ResourceManager)
     * @return Reference to the title font
     * @throws std::runtime_error if font is not loaded
     */
    const sf::Font& getTitleFont() const;
    
    /**
     * @brief Check if fonts are loaded
     * @return true if fonts are loaded
     */
    bool areFontsLoaded() const;

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    ThemeManager();
    
    /**
     * @brief Deleted copy constructor
     */
    ThemeManager(const ThemeManager&) = delete;
    
    /**
     * @brief Deleted assignment operator
     */
    ThemeManager& operator=(const ThemeManager&) = delete;
    
    Theme m_theme;                              ///< Current theme
    bool m_fontsLoaded = false;                 ///< Fonts loaded flag (fonts are in ResourceManager)
};

} // namespace UI
} // namespace DSA
