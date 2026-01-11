/**
 * @file Theme.h
 * @brief Theme data structure
 */

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

namespace DSA {
namespace UI {

/**
 * @struct Theme
 * @brief Theme data structure containing colors, fonts, and sizes
 */
struct Theme {
    // Colors
    sf::Color primaryColor;        ///< Primary color (buttons, highlights)
    sf::Color secondaryColor;      ///< Secondary color (backgrounds)
    sf::Color accentColor;         ///< Accent color (warnings, errors)
    sf::Color backgroundColor;     ///< Background color
    sf::Color textColor;           ///< Text color
    sf::Color hoverColor;          ///< Hover state color
    sf::Color pressedColor;        ///< Pressed state color
    sf::Color disabledColor;       ///< Disabled state color
    sf::Color successColor;        ///< Success color (green)
    sf::Color warningColor;        ///< Warning color (yellow)
    
    // Fonts (paths - loaded by ThemeManager)
    std::string fontMainPath;      ///< Main UI font path
    std::string fontMonospacePath; ///< Monospace font path
    std::string fontTitlePath;     ///< Title font path
    
    // Sizes
    unsigned int fontSizeNormal;   ///< Normal font size
    unsigned int fontSizeLarge;    ///< Large font size
    unsigned int fontSizeSmall;    ///< Small font size
    unsigned int fontSizeTitle;    ///< Title font size
    
    // Button dimensions
    float buttonHeight;            ///< Standard button height
    float buttonPadding;           ///< Button padding
    
    /**
     * @brief Default constructor with default theme
     */
    Theme();
    
    /**
     * @brief Create default theme
     * @return Theme with default values
     */
    static Theme createDefault();
};

} // namespace UI
} // namespace DSA
