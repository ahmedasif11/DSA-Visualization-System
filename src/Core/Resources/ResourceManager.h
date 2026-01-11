

#pragma once

#include "ResourceIDs.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace DSA {


class ResourceManager {
public:
    
    static ResourceManager& getInstance();
    
    
    bool loadFont(FontID id, const std::string& filepath);
    
    
    const sf::Font& getFont(FontID id) const;
    
    
    bool hasFont(FontID id) const;
    
    
    bool loadTexture(TextureID id, const std::string& filepath);
    
    
    const sf::Texture& getTexture(TextureID id) const;
    
    
    bool hasTexture(TextureID id) const;
    
    
    void setBasePath(const std::string& path);
    
    
    void clear();
    
    
    void clearFont(FontID id);
    
    
    void clearTexture(TextureID id);

private:
    
    ResourceManager() = default;
    
    
    ResourceManager(const ResourceManager&) = delete;
    
    
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    std::string m_basePath = "assets/";
    std::unordered_map<FontID, std::unique_ptr<sf::Font>> m_fonts;
    std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> m_textures;
};

} 
