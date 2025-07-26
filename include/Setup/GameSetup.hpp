#ifndef GAME_SETUP_HPP
#define GAME_SETUP_HPP

#include <exception>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>

namespace game
{
    /**
     * @brief Перечисление индентификаторов типов игры
     */
    enum GameTypeID
    {
        Computer,   ///< Игра с компьютером
        Multiplayer ///< Многопользовательская игра
    };

    /**
     * @brief Перечисление цветов ходов игры
     */
    enum MoveColor
    {
        White, ///< Белый цвет
        Black ///< Чёрный цвет
    };

    /**
     * @brief Перечисление индентификаторов режимов игры
     */
    enum GameParametersID
    {
        DefaultReversi,      ///< Реверси по умолчанию
        Antireversi,         ///< Антиреверси
        ReversiWithBlackHole ///< Реверси с чёрной дырой
    };

    /**
     * @brief Перечисление индентификаторов аватаров
     */
    enum AvatarID
    {
        Player, ///< Игрок
        Robot   ///< Робот
    };

    /**
     * @brief Класс для конфигурации игры.
     */
    class GameSetup
    {
    private:
        GameTypeID _gameTypeID = GameTypeID::Multiplayer;                      ///< Тип игры (по умолчанию: многопользовательская игра)
        unsigned _computerDifficulty = 0u;                                     ///< Уровень сложности компьютера
        sf::String _opponentName;                                              ///< Имя оппонента
        AvatarID _opponentAvatarID = AvatarID::Player;                         ///< Идентификатор аватара оппонента
        MoveColor _opponentMoveColor = MoveColor::Black;                       ///< Цвет, которым будет играть оппонент
        GameParametersID _gameParametersID = GameParametersID::DefaultReversi; ///< Режим игры
        unsigned _numberOfRounds = 1;                                          ///< Количество раундов
        unsigned _fieldSize = 8;                                               ///< Размер поля
        sf::Vector2i _blackHolePosition = {0, 0};                              ///< Позиция чёрной дыры
        std::vector<sf::Vector2i> _gameScore;                                  ///< Счёт игры
        static GameSetup*  _gameSetupPtr;                                      ///< Указатель на текущий объект конфигурации игры

    public:

        /**
         * @brief Конструктор класса GameSetup.
         *        Инициализирует новый объект типа GameSetup. Если уже существует объект _gameSetupPtr, то генерируется исключение типа std::logic_error.
         *        После инициализации, указатель _gameSetupPtr указывает на текущий объект.
         */
        GameSetup();

        /// Деструктор
        ~GameSetup() = default;

        /**
         * @brief  Метод получения индентификатора типа игры.
         * @return Ссылка на значение _gameTypeID.
         */ 
        static GameTypeID& GetGameTypeID();

        /**
         * @brief  Метод получения уровня сложности игры.
         * @return Ссылка на значение _computerDifficulty.
         */
        static unsigned& GetComputerDifficulty();

        /**
         * @brief  Метод получения имени оппонента.
         * @return Ссылка на значение _opponentName.
         */
        static sf::String& GetOpponentName();

        /**
         * @brief  Метод получения аватара оппонента.
         * @return Ссылка на значение _opponentAvatarID.
         */
        static AvatarID& GetOpponentAvatarID();

        /**
         * @brief  Метод получения цвета, которым будет играть оппонент.
         * @return Ссылка на значение _opponentMoveColor.
         */
        static MoveColor& GetOpponentMoveColor();

        /**
         * @brief  Метод получения индентификатора режима игры.
         * @return Ссылка на значение _gameParametersID.
         */
        static GameParametersID& GetGameParametersID();

        /**
         * @brief  Метод получения количества раундов.
         * @return Ссылка на значение  _numberOfRounds.
         */
        static unsigned& GetNumberOfRounds();

        /**
         * @brief  Метод получения размера поля.
         * @return Ссылка на значение  _fieldSize.
         */
        static unsigned& GetFieldSize();

        /**
         * @brief  Метод получения позиции чёрной дыры.
         * @return Ссылка на значение  _blackHolePosition.
         */
        static sf::Vector2i& GetBlackHolePosition();

        /**
         * @brief  Метод получения счёта игры.
         * @return Ссылка на значение  _gameScore.
         */
        static std::vector<sf::Vector2i>& GetGameScore();
    };
}

#endif