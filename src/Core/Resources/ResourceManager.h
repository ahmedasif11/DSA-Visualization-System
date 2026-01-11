/**
 * @file ResourceManager.h
 * @brief Resource manager for fonts, textures, and other assets
 */

#pragma once

#include "ResourceIDs.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <string>
#include <memory>

namespace DSA {

/**
 * @class ResourceManager
 * @brief Manages loading and caching of resources (fonts, textures)
 * 
 * Singleton pattern ensures single instance throughout the application.
 * Resources are loaded lazily and cached for reuse.
 */
class ResourceManager {
public:
    /**
     * @brief Get the singleton instance
     * @return ResourceManager& Reference to the resource manager
     */
    static ResourceManager& getInstance();
    
    /**
     * @brief Load a font from file
     * @param id The font identifier
     * @param filepath Path to the font file
     * @return true if font was loaded successfully
     */
    bool loadFont(FontID id, const std::string& filepath);
    
    /**
     * @brief Get a font by ID
     * @param id The font identifier
     * @return Reference to the font
     * @throws std::runtime_error if font is not loaded
     */
    const sf::Font& getFont(FontID id) const;
    
    /**
     * @brief Check if a font is loaded
     * @param id The font identifier
     * @return true if font is loaded
     */
    bool hasFont(FontID id) const;
    
    /**
     * @brief Load a texture from file
     * @param id The texture identifier
     * @param filepath Path to the texture file
     * @return true if texture was loaded successfully
     */
    bool loadTexture(TextureID id, const std::string& filepath);
    
    /**
     * @brief Get a texture by ID
     * @param id The texture identifier
     * @return Reference to the texture
     * @throws std::runtime_error if texture is not loaded
     */
    const sf::Texture& getTexture(TextureID id) const;
    
    /**
     * @brief Check if a texture is loaded
     * @param id The texture identifier
     * @return true if texture is loaded
     */
    bool hasTexture(TextureID id) const;
    
    /**
     * @brief Set the base path for resources
     * @param path The base path (e.g., "assets/")
     */
    void setBasePath(const std::string& path);
    
    /**
     * @brief Clear all loaded resources
     */
    void clear();
    
    /**
     * @brief Clear a specific font
     * @param id The font identifier
     */
    void clearFont(FontID id);
    
    /**
     * @brief Clear a specific texture
     * @param id The texture identifier
     */
    void clearTexture(TextureID id);

private:
    /**
     * @brief Private constructor for singleton pattern
     */
    ResourceManager() = default;
    
    /**
     * @brief Deleted copy constructor
     */
    ResourceManager(const ResourceManager&) = delete;
    
    /**
     * @brief Deleted assignment operator
     */
    ResourceManager& operator=(const ResourceManager&) = delete;
    
    std::string m_basePath = "assets/";  ///< Base path for resources
    std::unordered_map<FontID, std::unique_ptr<sf::Font>> m_fonts;
    std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> m_textures;
};

} // namespace DSA
