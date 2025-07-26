#ifndef GAME_INFORMATION_HPP
#define GAME_INFORMATION_HPP

#include <SFML/Graphics.hpp>
#include "./GameField.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/PlayerSetup.hpp"
#include "../../Setup/GameSetup.hpp"
#include "../../ResourceLoader.hpp"

namespace game
{

    /**
     * @brief Класс, представляющий счет игроков.
     */
    class Score
    {
    private:

        /**
         * @brief Структура, содержащая декоративные опции.
         */
        struct Decor
        {
            float stepBetweenTitleAndTextFields = 80.f; ///< Расстояние между заголовком и текстовыми полями
            float stepBetweenTextFields = 40.f;         ///< Расстояние между текстовыми полями
            float stepBetweenAvatarAndName = 20.f;      ///< Расстояние между аватаром и именем
        } Decor;

    protected:
        Text _title;                ///< Заголовок
        Text _playerScoreText;      ///< Текст счета игрока
        Text _opponentScoreText;    ///< Текст счета противника
        sf::Sprite _playerAvatar;   ///< Аватар игрока
        Text _playerName;           ///< Имя игрока
        Text _opponentName;         ///< Имя противника
        sf::Sprite _opponentAvatar; ///< Аватар противника
        float _fieldWidth = 500.f;  ///< Ширина поля

        /**
         * @brief Инициализация элементов счета.
         */
        void init();

        /**
         * @brief Выравнивание элементов счета.
         */
        void Align();

    public:
        /**
         * @brief Конструктор с параметрами.
         * 
         * @param title                         Заголовок.
         * @param playerScoreText               Текст счета игрока.
         * @param opponentScoreText             Текст счета противника.
         * @param fieldWidth                    Ширина поля.
         * @param stepBetweenTitleAndTextFields Расстояние между заголовком и текстовыми полями.
         * @param stepBetweenTextFields         Расстояние между текстовыми полями.
         */
        Score(Text title, Text playerScoreText, Text opponentScoreText, float fieldWidth, float stepBetweenTitleAndTextFields = 80.f, float stepBetweenTextFields = 40.f);

        /**
         * @brief Виртуальный деструктор класса.
         */
        virtual ~Score() {};

        /**
         * @brief Возвращает высоту.
         * 
         * @return Высота элементов счета.
         */
        float GetHeight() const
        {
            return _opponentAvatar.getPosition().y - _title.getPosition().y + _title.getGlobalBounds().height / 2.f + _opponentAvatar.getGlobalBounds().height / 2.f;
        }

        /**
         * @brief Отображает элементы счета на цели.
         * 
         * @param target Цель для отображения.
         */
        void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Устанавливает смещение элементов счета.
         * 
         * @param offset Смещение.
         */
        void SetOffset(sf::Vector2f offset);

        /**
         * @brief Устанавливает позицию элементов счета.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPosition(float x, float y)
        {
            SetOffset({x - _title.getPosition().x, y - _title.getPosition().y - GetHeight() / 2.f + _title.getGlobalBounds().height / 2.f});
        }
    };


    namespace gameInformation
    {

        /**
         * @brief Интерфейс, предоставляющий информацию об игре.
         */
        class IGameInformation
        {
        protected:
            float fieldWidth = 500.f; ///< Ширина поля информации об игре
        public:

            /**
             * @brief Виртуальный деструктор класса.
             */
            virtual ~IGameInformation() {};

            /**
             * @brief Возвращает высоту объекта информации об игре.
             * 
             * @return Высота.
             */
            virtual float GetHeight() const = 0;

            /**
             * @brief Устанавливает позицию объекта информации об игре.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            virtual void SetPosition(float x, float y) = 0;

            /**
             * @brief Отображает объект информации об игре на цели.
             * 
             * @param target Цель для отображения.
             */
            virtual void Draw(sf::RenderTarget* target) const = 0;
        };

        /**
         * @brief Класс, представляющий информацию о раунде игры.
         */
        class RoundScore : public IGameInformation, public Score
        {
        private:
            int _playerScore;   ///< Счет игрока
            int _opponentScore; ///< Счет противника

            /**
             * @brief Выравнивает счета игрока и противника.
             */
            void AlignScores();

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            RoundScore();

            /**
             * @brief Виртуальный деструктор класса.
             */
            ~RoundScore() {};

            /**
             * @brief Обновляет счет игрока и противника.
             * 
             * @param playerScore   Счет игрока.
             * @param opponentScore Счет противника.
             */
            void Update(int playerScore, int opponentScore);

            /**
             * @brief Сбрасывает текущий счет до начального состояния.
             */
            void Reset();

            /**
             * @brief Возвращает счет игрока.
             * 
             * @return Счет игрока.
             */
            int GetPlayerScore() const { return _playerScore; }

            /**
             * @brief Возвращает счет противника.
             * 
             * @return Счет противника.
             */
            int GetOpponentScore() const { return _opponentScore; }

            /**
             * @brief Возвращает высоту объекта информации об игре.
             * 
             * @return Высота.
             */
            float GetHeight() const { return Score::GetHeight(); }

            /**
             * @brief Устанавливает позицию объекта информации об игре.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y) { Score::SetPosition(x, y); }

            /**
             * @brief Отображает объект информации об игре на цели.
             * 
             * @param target Цель для отображения.
             */
            void Draw(sf::RenderTarget* target) const { Score::Draw(target); }
        };

        /**
         * @brief Класс, представляющий информацию о цветах игры.
         */
        class GameColors : public IGameInformation
        {
        private:
            /**
             * @brief Структура, содержащая декоративные опции.
             */
            struct Decor
            {
                float sizeBetweenAvatarAndName = 20.f; ///< Расстояние между аватаром и именем
                float sizeBetweenMoveColors = 40.f;    ///< Расстояние между цветами ходов
            } Decor;

            sf::Sprite _playerAvatar;                   ///< Аватар игрока
            Text _playerName;                           ///< Имя игрока
            sf::Sprite _opponentAvatar;                 ///< Аватар противника
            Text _opponentName;                         ///< Имя противника
            Text _playerColor = TextOptions{L"", 40};   ///< Цвет игрока
            Text _opponentColor = TextOptions{L"", 40}; ///< Цвет противника

            /**
             * @brief Инициализирует элементы информации о цветах игры.
             */
            void init();

            /**
             * @brief Выравнивает элементы информации о цветах игры.
             */
            void Align();

            /**
             * @brief Выравнивает цвета игроков.
             */
            void AlignColors();

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            GameColors();

            /**
             * @brief Виртуальный деструктор класса.
             */
            ~GameColors() {};

            /**
             * @brief  Возвращает высоту объекта информации о цветах игры.
             * @return Высота.
             */
            float GetHeight() const
            {
                return _playerAvatar.getGlobalBounds().height + Decor.sizeBetweenMoveColors + _opponentAvatar.getGlobalBounds().height;
            }   

            /**
             * @brief Обновляет информацию о цветах игры.
             */
            void Update();

            /**
             * @brief Устанавливает смещение объекта информации о цветах игры.
             * 
             * @param offset Смещение.
             */
            void SetOffset(sf::Vector2f offset);

            /**
             * @brief Устанавливает позицию объекта информации о цветах игры.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y);

            /**
             * @brief Отображает объект информации о цветах игры на цели.
             * 
             * @param target Цель для отображения.
             */
            void Draw(sf::RenderTarget* target) const;
        };


        /**
         * @brief Класс, представляющий параметры игры.
         */
        class GameParameters : public IGameInformation
        {
        private:
            /**
             * @brief Структура, содержащая декоративные опции.
             */
            struct Decor
            {
                float sizeBetweenTitleAndTextField = 80.f; ///< Расстояние между заголовком и текстовым полем
            } Decor;

            Text _title = game::TextOptions{L"Режим игры"}; ///< Заголовок
            Text _text;                                     ///< Текстовое поле

            /**
             * @brief Инициализирует элементы параметров игры.
             */
            void init();

            /**
             * @brief Выравнивает элементы параметров игры.
             */
            void Align();

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            GameParameters();

            /**
             * @brief Виртуальный деструктор класса.
             */
            ~GameParameters() {}

            /**
             * @brief Возвращает высоту объекта информации о параметрах игры.
             * 
             * @return Высота.
             */
            float GetHeight() const
            {
                return _title.getGlobalBounds().height + Decor.sizeBetweenTitleAndTextField + _text.getGlobalBounds().height;
            }

            /**
             * @brief Устанавливает позицию объекта информации о параметрах игры.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y);

            /**
             * @brief Отображает объект информации о параметрах игры на цели.
             * 
             * @param target Цель для отображения.
             */
            void Draw(sf::RenderTarget* target) const;
        };

        /**
         * @brief Класс, представляющий информацию о сложности игры.
         */
        class Difficulty : public IGameInformation
        {
        private:
            game::Text _title = TextOptions(L"Сложность:", 40); ///< Заголовок
            game::Text _difficulty = TextOptions(L"", 40);      ///< Уровень сложности

            /**
             * @brief Инициализирует элементы информации о сложности игры.
             */
            void init();

            /**
             * @brief Выравнивает элементы информации о сложности игры.
             */
            void Align();

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            Difficulty();

            /**
             * @brief Виртуальный деструктор класса.
             */
            ~Difficulty() {};

            /**
             * @brief Возвращает высоту объекта информации о сложности игры.
             * 
             * @return Высота.
             */
            float GetHeight() const { return _title.getGlobalBounds().height; }

            /**
             * @brief Устанавливает позицию объекта информации о сложности игры.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y);

            /**
             * @brief Отображает объект информации о сложности игры на цели.
             * 
             * @param target Цель для отображения.
             */
            void Draw(sf::RenderTarget* target) const;
        };

        /**
         * @brief Класс, представляющий информацию о раунде игры.
         */
        class Round : public IGameInformation
        {
        private:

            /**
             * @brief Структура, содержащая декоративные опции.
             */
            struct Decor
            {
                float sizeBetweenTitleAndTextField = 80.f; ///< Расстояние между заголовком и текстовым полем
            } Decor;

            int& _currentRound; ///< Текущий раунд

            game::Text _title = TextOptions(L"Раунд"); ///< Заголовок
            game::Text _text = TextOptions(L"", 40);   ///< Текстовое поле

            /**
             * @brief Инициализирует элементы информации о раунде игры.
             */
            void init()
            {
                _text.SetString(std::to_string(_currentRound) + " / " + std::to_string(GameSetup::GetNumberOfRounds()));
            }

            /**
             * @brief Выравнивает элементы информации о раунде игры.
             */
            void Align();

        public:
            /**
             * @brief Конструктор по умолчанию.
             */
            Round() = default;

            /**
             * @brief Конструктор с параметром.
             * 
             * @param currentRound Текущий раунд.
             */
            Round(int& currentRound);

            /**
             * @brief Виртуальный деструктор класса.
             */
            ~Round() {};

            /**
             * @brief Возвращает высоту объекта информации о раунде игры.
             * 
             * @return Высота.
             */
            float GetHeight() const
            {
                return _title.getGlobalBounds().height + Decor.sizeBetweenTitleAndTextField + _text.getGlobalBounds().height;
            }

            /**
             * @brief Обновляет информацию о раунде игры.
             */
            void Update() { init(); }

            /**
             * @brief Устанавливает позицию объекта информации о раунде игры.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y);

            /**
             * @brief Отображает объект информации о раунде игры на цели.
             * 
             * @param target Цель для отображения.
             */
            void Draw(sf::RenderTarget* target) const;
        };
    }
}

#endif