#ifndef PLAYER_SETUP_HPP
#define PLAYER_SETUP_HPP

#include <SFML/Graphics.hpp>
#include <exception>
#include "./GameSetup.hpp"

namespace game
{
    /**
     * @brief Класс, отвечающий за конфигурацию игрока.
     */
    class PlayerSetup
    {
    private:
        sf::String _name;                     ///< Имя игрока
        static PlayerSetup*  _playerSetupPtr; ///< Указатель на текущий объект конфигурации игрока

        /**
         * @brief Инициализация конфигурации игрока.
         *        Метод создает директорию "../Files/", после чего пытается открыть файл "../Files/PlayerSetup.txt" в режиме чтения. 
         *        Если файл не удалось открыть, создается новый файл в режиме записи. 
         *        Если не удается открыть или создать файл, выбрасывается исключение типа std::runtime_error. 
         *        Если файл открыт успешно, метод считывает первую строку из файла и конвертирует ее в формат sf::String.
         */
        void init();

    public:

        /**
         * @brief Конструктор класса PlayerSetup.
         *        Конструктор инициализирует новый объект типа PlayerSetup. 
         *        Проверяет, существует ли уже объект _playerSetupPtr. Если объект уже существует, генерируется исключение типа std::logic_error. 
         *        Устанавливает указатель на текущий объект _playerSetupPtr и вызывает функцию init().
         */
        PlayerSetup();

        /// Деструктор 
        ~PlayerSetup() {};

        /**
         * @brief  Метод получения имени игрока.
         * @return Ссылка на _name, хранящуюся в объекте, на который указывает _playerSetupPtr.
         */
        static sf::String& GetName();

        /**
         * @brief Сохранение конфигурации игрока в файл.
         *        Метод открывает файл "../Files/PlayerSetup.txt" для записи. 
         *        Если не удается открыть файл, выбрасывается исключение типа std::runtime_error. 
         *        Затем метод вызывает SaveName(), чтобы сохранить имя игрока в файле в кодировке UTF-8.
         */
        static void Save();
    };
}

#endif