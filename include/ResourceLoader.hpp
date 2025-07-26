#ifndef RESOURCE_LOADER_HPP
#define RESOURCE_LOADER_HPP

#include <SFML/Graphics.hpp>
#include <exception>
#include <map>
#include <assert.h>

class ResourceLoader
{
public:

    /**
     * @brief Конструктор класса ResourceLoader.
     */
    ResourceLoader();

    /**
     * @brief Получение ссылки на текстуру по имени файла.
	 * 
     * @param filename Имя файла текстуры.
	 * 
     * @return Ссылка на объект текстуры.
     */
    static sf::Texture& GetTexture(const std::string& filename);

    /**
     * @brief Получение ссылки на шрифт по имени файла.
	 * 
     * @param filename Имя файла шрифта.
	 * 
     * @return Ссылка на объект шрифта.
     */
    static sf::Font& GetFont(const std::string& filename);
private:
    std::map<std::string, sf::Texture> textures; ///< Карта текстур с их именами
    std::map<std::string, sf::Font> fonts;       ///< Карта шрифтов с их именами
    static ResourceLoader* sInstance;            ///< Статический экземпляр класса ResourceLoader
};


#endif
