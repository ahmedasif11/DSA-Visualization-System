

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <string>
#include <optional>

namespace DSA {
namespace UI {


class Label {
public:
    
    Label(const sf::Vector2f& position = sf::Vector2f(0, 0), const std::string& text = "");
    
    
    virtual ~Label() = default;
    
    
    void setText(const std::string& text);
    
    
    std::string getText() const;
    
    
    void setPosition(const sf::Vector2f& position);
    
    
    sf::Vector2f getPosition() const;
    
    
    void setFontSize(unsigned int size);
    
    
    unsigned int getFontSize() const;
    
    
    void setColor(const sf::Color& color);
    
    
    sf::Color getColor() const;
    
    
    void render(sf::RenderTarget& target) const;
    
    
    sf::FloatRect getLocalBounds() const;

private:
    std::optional<sf::Text> m_text;
};

}
} 
