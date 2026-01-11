/**
 * @file ResourceManager.cpp
 * @brief Implementation of the ResourceManager class
 */

#include "ResourceManager.h"
#include "ResourceIDs.h"
#include <stdexcept>
#include <vector>

namespace DSA {

ResourceManager& ResourceManager::getInstance() {
    static ResourceManager instance;
    return instance;
}

bool ResourceManager::loadFont(FontID id, const std::string& filepath) {
    std::string fullPath = m_basePath + filepath;
    
    // Try to load from specified path first
    auto font = std::make_unique<sf::Font>();
    if (font->openFromFile(fullPath)) {
        m_fonts[id] = std::move(font);
        return true;
    }
    
    // Fallback: Try system fonts on Windows
    // Common Windows system font paths
    std::vector<std::string> systemFontPaths = {
        "C:/Windows/Fonts/arial.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
        "C:/Windows/Fonts/calibri.ttf",
        "C:/Windows/Fonts/segoeui.ttf"
    };
    
    // For monospace, prefer Consolas
    if (id == FontID::Monospace) {
        systemFontPaths.insert(systemFontPaths.begin(), "C:/Windows/Fonts/consola.ttf");
    }
    
    // Try system fonts (create new font object for each attempt)
    for (const auto& sysPath : systemFontPaths) {
        auto sysFont = std::make_unique<sf::Font>();
        if (sysFont->openFromFile(sysPath)) {
            m_fonts[id] = std::move(sysFont);
            return true;
        }
    }
    
    // All attempts failed
    return false;
}

const sf::Font& ResourceManager::getFont(FontID id) const {
    auto it = m_fonts.find(id);
    if (it == m_fonts.end() || !it->second) {
        throw std::runtime_error("Font not loaded: " + std::to_string(static_cast<int>(id)));
    }
    return *it->second;
}

bool ResourceManager::hasFont(FontID id) const {
    return m_fonts.find(id) != m_fonts.end() && m_fonts.at(id) != nullptr;
}

bool ResourceManager::loadTexture(TextureID id, const std::string& filepath) {
    auto texture = std::make_unique<sf::Texture>();
    std::string fullPath = m_basePath + filepath;
    
    if (!texture->loadFromFile(fullPath)) {
        return false;
    }
    
    m_textures[id] = std::move(texture);
    return true;
}

const sf::Texture& ResourceManager::getTexture(TextureID id) const {
    auto it = m_textures.find(id);
    if (it == m_textures.end() || !it->second) {
        throw std::runtime_error("Texture not loaded: " + std::to_string(static_cast<int>(id)));
    }
    return *it->second;
}

bool ResourceManager::hasTexture(TextureID id) const {
    return m_textures.find(id) != m_textures.end() && m_textures.at(id) != nullptr;
}

void ResourceManager::setBasePath(const std::string& path) {
    m_basePath = path;
    // Ensure trailing slash
    if (!m_basePath.empty() && m_basePath.back() != '/' && m_basePath.back() != '\\') {
        m_basePath += '/';
    }
}

void ResourceManager::clear() {
    m_fonts.clear();
    m_textures.clear();
}

void ResourceManager::clearFont(FontID id) {
    m_fonts.erase(id);
}

void ResourceManager::clearTexture(TextureID id) {
    m_textures.erase(id);
}

} // namespace DSA
