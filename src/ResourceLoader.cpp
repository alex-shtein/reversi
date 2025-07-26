#include "../include/ResourceLoader.hpp"

ResourceLoader* ResourceLoader::sInstance = nullptr;

ResourceLoader::ResourceLoader()
{
	if(sInstance)
        throw std::logic_error("Trying to create an already existing class ResourceLoader");

	sInstance = this;
}

sf::Texture& ResourceLoader::GetTexture(const std::string& filename)
{
	if (sInstance->textures.find(filename) != sInstance->textures.end())
		return sInstance->textures[filename];

    auto& texture = sInstance->textures[filename];
    texture.loadFromFile(filename);

    return texture;
}

sf::Font& ResourceLoader::GetFont(const std::string& filename)
{
    if (sInstance->fonts.find(filename) != sInstance->fonts.end())
		  return sInstance->fonts[filename];

    auto& font = sInstance->fonts[filename];
    font.loadFromFile(filename);

    return font;
}
