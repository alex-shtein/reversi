#ifndef TIME_AND_SCORE_HPP
#define TIME_AND_SCORE_HPP

#include <SFML/Graphics.hpp>
#include "./GameField.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/PlayerSetup.hpp"
#include "../../Setup/GameSetup.hpp"
#include "../../ResourceLoader.hpp"

namespace game
{
    /**
     * @brief Класс TimeAndScore представляет собой компонент для отображения счета в игре.
     */
    class TimeAndScore
    {
    private:

        /**
         * @brief Вложенный класс RoundScore представляет собой счет для одного раунда игры.
         */
        class RoundScore
        {
        private:

            /**
             * @brief Структура Decor содержит визуальные свойства для отображения счета.
             */
            struct Decor
            {
                sf::FloatRect backgroundSize = sf::FloatRect(0.f, 0.f, 600.f, 90.f); ///< Размер фона
                sf::Color blurColor = sf::Color(80, 80, 80, 140);                    ///< Цвет размытия

                float backgroundRadius = 0.f;                     ///< Радиус фона
                float backgroundOutlineThickness = 0.f;           ///< Толщина контура фона
                float stepBetweenChipAndScore = 20.f;             ///< Шаг между фишкой и счетом
                float margin = 50.f;                              ///< Отступ
            } Decor;

            GameField& _gameField;   ///< Ссылка на игровое поле
            Rectangle _background;   ///< Фон
            sf::Sprite _blackChip;   ///< Спрайт черной фишки
            sf::Sprite _whiteChip;   ///< Спрайт белой фишки
            Text _playerScoreText;   ///< Текст для отображения счета игрока
            Text _opponentScoreText; ///< Текст для отображения счета оппонента
            Rectangle _blur;         ///< Размытие

            int _playerScore;   ///< Счет игрока
            int _opponentScore; ///< Счет оппонента

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
             * @brief Конструктор по умолчанию.
             */
            RoundScore() = default;

            /**
             * @brief Конструктор с параметрами.
             * 
             * @param gameField Ссылка на игровое поле.
             */
            RoundScore(GameField& gameField);

            /**
             * @brief Деструктор.
             */
            ~RoundScore() {};

            /**
             * @brief Сброс счета.
             */
            void Reset();

            /**
             * @brief Обновление счета.
             */
            void Update();

            /**
             * @brief Установка позиции элементов счета.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y)
            {
                SetOffset({x - _background.GetPosition().x, y - _background.GetPosition().y});
            }

            /**
             * @brief Установка смещения элементов счета.
             * 
             * @param offset Смещение по осям X и Y.
             */
            void SetOffset(sf::Vector2f offset);

            /**
             * @brief Отрисовка элементов счета на экране.
             * 
             * @param target Указатель на объект отрисовки.
             */
            void Draw(sf::RenderTarget* target) const;

            /**
             * @brief Получение границ элементов счета.
             * 
             * @return Прямоугольник, представляющий границы элементов счета.
             */
            sf::FloatRect GetBounds() const { return _background.getBounds(); }

            /**
             * @brief Получение счета игрока.
             * 
             * @return Счет игрока.
             */
            int GetPlayerScore() const { return _playerScore; }

            /**
             * @brief Получение счета оппонента.
             * 
             * @return Счет оппонента.
             */
            int GetOpponentScore() const { return _opponentScore; }

        };

        /**
         * @brief Вложенный класс RoundTime представляет собой компонент для отображения времени в игре.
         */
        class RoundTime
        {
        private:

            /**
             * @brief Структура Decor содержит визуальные свойства для отображения времени.
             */
            struct Decor
            {
                sf::FloatRect backgroundSize = sf::FloatRect(0.f, 0.f, 140.f, 140.f); ///< Размер фона
                float backgroundRadius = 15.f;                                        ///< Радиус фона
                float backgroundOutlineThickness = 4.f;                               ///< Толщина контура фона
                float padding = 15.f;                                                 ///< Отступ
            } Decor;

            sf::String ConvertSecondToStringTime() const; ///< Преобразование времени в формат строки

            Rectangle _background; ///< Фон
            sf::Sprite _timeIcon;  ///< Спрайт иконки времени
            float _time;           ///< Время
            Text _timeText;        ///< Текст для отображения времени

            /**
             * @brief Инициализация элементов времени.
             */
            void init()
            {
                _timeIcon.setOrigin(_timeIcon.getGlobalBounds().width / 2.f, _timeIcon.getGlobalBounds().height / 2.f);
            }

            /**
             * @brief Выравнивание элементов времени.
             */
            void Align();
        public:

            /**
             * @brief Конструктор по умолчанию.
             */
            RoundTime();

            /**
             * @brief Получение времени в виде строки.
             * 
             * @return Время в формате строки.
             */
            sf::String GetTime() const { return ConvertSecondToStringTime(); }

            /**
             * @brief Сброс времени.
             */
            void Reset();

            /**
             * @brief Обновление времени.
             * 
             * @param dt Прошедшее время.
             */
            void Update(float dt);

            /**
             * @brief Установка позиции элементов времени.
             * 
             * @param x Координата X.
             * @param y Координата Y.
             */
            void SetPosition(float x, float y)
            {
                SetOffset({x - _background.GetPosition().x, y - _background.GetPosition().y - Decor.backgroundOutlineThickness});
            }

            /**
             * @brief Установка смещения элементов времени.
             * 
             * @param offset Смещение по осям X и Y.
             */
            void SetOffset(sf::Vector2f offset);

            /**
             * @brief Отрисовка элементов времени на экране.
             * 
             * @param target Указатель на объект отрисовки.
             */
            void Draw(sf::RenderTarget* target) const;

            /**
             * @brief Получение границ элементов времени.
             * 
             * @return Прямоугольник, представляющий границы элементов времени.
             */
            sf::FloatRect GetBounds() const { return _background.getBounds(); }
        };

    private:
        RoundScore _score; ///< Компонент для отображения счета
        RoundTime _time;   ///< Компонент для отображения времени

        void init() {}  ///< Инициализация элементов времени и счета
        void Align() {} ///< Выравнивание элементов времени и счета

    public:
        /**
         * @brief Конструктор компонента TimeAndScore.
         * 
         * @param gameField Ссылка на игровое поле.
         */
        TimeAndScore(GameField& gameField) : _score(gameField) {} 

        ~TimeAndScore() {} ///< Деструктор компонента TimeAndScore

        /**
         * @brief Установка позиции компонента TimeAndScore.
         * 
         * @param x Координата X.
         * @param y Координата Y.
         */
        void SetPostion(float x, float y);

        /**
         * @brief Отрисовка компонента TimeAndScore на экране.
         * 
         * @param target Указатель на объект отрисовки.
         */
        void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Обновление компонента TimeAndScore.
         * 
         * @param dt Прошедшее время.
         */
        void Update(float dt) { _time.Update(dt); }

        /**
         * @brief Обновление компонента TimeAndScore.
         */
        void Update() { _score.Update(); }

        /**
         * @brief Сброс компонента TimeAndScore.
         */
        void Reset();

        /**
         * @brief Получение счета игрока.
         * 
         * @return Счет игрока.
         */
        int GetPlayerScore() const { return _score.GetPlayerScore(); }

        /**
         * @brief Получение счета оппонента.
         * 
         * @return Счет оппонента.
         */
        int GetOpponentScore() const { return _score.GetOpponentScore(); }

        /**
         * @brief Получение времени в виде строки.
         * 
         * @return Время в формате строки.
         */
        sf::String GetTime() const { return _time.GetTime(); }
    };
}

#endif