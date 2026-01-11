

#pragma once

#include "Theme.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include <unordered_map>

namespace DSA {
namespace UI {


class ThemeManager {
public:
    
    static ThemeManager& getInstance();
    
    
    void setTheme(const Theme& theme);
    
    
    const Theme& getTheme() const;
    
    
    bool loadFonts();
    
    
    const sf::Font& getMainFont() const;
    
    
    const sf::Font& getMonospaceFont() const;
    
    
    const sf::Font& getTitleFont() const;
    
    
    bool areFontsLoaded() const;

private:
    
    ThemeManager();
    
    
    ThemeManager(const ThemeManager&) = delete;
    
    
    ThemeManager& operator=(const ThemeManager&) = delete;
    
    Theme m_theme;
    bool m_fontsLoaded = false;
};

}
} 
