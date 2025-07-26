#ifndef BOARD_SETUP_HPP
#define BOARD_SETUP_HPP

#include <SFML/Graphics.hpp>
#include <exception>
#include "./GameSetup.hpp"

namespace game
{
    /**
     * @brief Класс, отвечающий за конфигурацию доски игры. 
     *        Содержит информацию о выбранной теме, настройках подсказок и настройках координат.
     */
    class BoardSetup
    {
    public:

    /// Перечисление, представляющее тему доски.
    enum class Theme
    {
        Сolorful, ///< Разноцветная тема.
        Solid     ///< Стандартная тема.
    };

    private:
        Theme _theme; ///< Выбранная тема.
        bool _tips;   ///< Флаг использования подсказок.

        /**
         * @brief Приватная константная переменная _colors
         *        Карта (_colors) сопоставляет каждой теме доски (game::BoardSetup::Theme) набор цветов (sf::Vector3<sf::Color>). 
         *        Каждый набор цветов представлен тремя компонентами: основной цвет, фон и выделение.
         */
        const std::map<game::BoardSetup::Theme, sf::Vector3<sf::Color>> _colors = 
        {
            {game::BoardSetup::Theme::Сolorful, {sf::Color(0, 75, 114), sf::Color(10, 52, 92), sf::Color(0, 67, 110)}},
            {game::BoardSetup::Theme::Solid, {sf::Color(0, 75, 114), sf::Color(10, 52, 92), sf::Color(10, 52, 92)}}
        };

        /**
         * @brief Статическая приватная константная переменная _themes
         *        _themes хранит карту (std::map), которая сопоставляет каждую тему доски (game::BoardSetup::Theme) со строковым представлением этой темы.
         * 
         */
        const std::map<game::BoardSetup::Theme, std::string> _themes
        {
            {game::BoardSetup::Theme::Сolorful, "Сolorful"},
            {game::BoardSetup::Theme::Solid, "Solid"}
        };

        static BoardSetup*  _boardSetupPtr; ///< Указатель на единственный объект класса.

        /**
         * @brief Инициализация объекта.
         *        Создаёт директорию для файлов конфигурации.
         *        Если файл "BoardSetup.txt" не открывается, устанавливаются значения по умолчанию (тема - Solid, подсказки - включены).
         *        Если файл открывается успешно, извлекаются сохранённые значения темы и настроек подсказок.
         */
        void init();

    public:

        /**
         * @brief Конструктор класса BoardSetup.
         *        Проверяет наличие уже существующего объекта класса BoardSetup. 
         *        Если указатель уже не пуст, выбрасывается исключение. 
         *        В противном случае, указатель _boardSetupPtr устанавливается на текущий объект, инициализируются поля объекта методом init().
         */
        BoardSetup();

        /// Деструктор.
        ~BoardSetup() {};

        /**
         * @brief  Получение карты цветов для темы доски.
         * @return Карта цветов для темы доски.
         */ 
        static std::map<game::BoardSetup::Theme, sf::Vector3<sf::Color>> GetColors() { return _boardSetupPtr->_colors; }

        /**
         * @brief  Получение карты тем для доски.
         * @return Карта тем для доски.
         */ 
        static std::map<game::BoardSetup::Theme, std::string> GetThemes() { return _boardSetupPtr->_themes; }

        /**
         * @brief  Получение выбранной темы доски.
         * @return Ссылка на выбранную тему.
         */ 
        static Theme& GetTheme();

        /**
         * @brief  Получение значения флага использования подсказок.
         * @return Ссылка на флаг использования подсказок.
         */ 
        static bool& GetTips();
        
        /**
         * @brief Сохранение конфигурации доски.
         *        Открывается файл "BoardSetup.txt" для записи.
         *        Если файл не открывается, выбрасывается исключение.
         *        Записываются выбранная тема и настройки подсказок в файл.
         */
        static void Save();
    };
}

#endif