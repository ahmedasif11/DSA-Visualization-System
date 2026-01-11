#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

namespace DSA {
namespace UI {

struct Theme {
    sf::Color primaryColor;
    sf::Color secondaryColor;
    sf::Color accentColor;
    sf::Color backgroundColor;
    sf::Color textColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    sf::Color disabledColor;
    sf::Color successColor;
    sf::Color warningColor;
    
    std::string fontMainPath;
    std::string fontMonospacePath;
    std::string fontTitlePath;
    
    unsigned int fontSizeNormal;
    unsigned int fontSizeLarge;
    unsigned int fontSizeSmall;
    unsigned int fontSizeTitle;
    
    float buttonHeight;
    float buttonPadding;
    
    Theme();
    static Theme createDefault();
};

}
}
