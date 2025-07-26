#ifndef COMPUTER_START_COLOR_HPP
#define COMPUTER_START_COLOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "./IGameSetting.hpp"
#include "../../Particulars.hpp"
#include "../../Setup/GameSetup.hpp"

namespace game
{
    class ComputerStartColor : public IGameSetting
    {
    private:

        /**
         * @brief Класс ButtonWithColor, представляющий кнопку с цветом
         */
        class ButtonWithColor : public ButtonWithIcon
        {
        private:

            /**
             * @brief Структура Decor для хранения декоративных параметров кнопки с цветом
             */
            struct Decor
            {
                sf::Color blurColor = sf::Color(80, 80, 80, 140); ///< Цвет размытия
            } Decor;

            Rectangle _blur;          ///< Объект прямоугольника для размытия
            bool _isSelected = false; ///< Флаг, указывающий выбран ли цвет

            /**
             * @brief Инициализация
             */
            void init() {}

            /**
             * @brief Выравнивание
             */
            void Align() { _blur.SetPosition(GetPosition()); }

        public:

            /**
             * @brief Конструктор по умолчанию
             */
            ButtonWithColor() = default; 

            /**
             * @brief Конструктор класса ButtonWithColor с параметрами
             * 
             * @param rectangle          Прямоугольник типа sf::FloatRect
             * @param radius             Радиус
             * @param icon               Иконка типа sf::Sprite
             * @param function           Функция-обработчик кнопки
             * @param topDefaultColor    Цвет верхней части кнопки по умолчанию
             * @param bottomDefaultColor Цвет нижней части кнопки по умолчанию
             * @param topHoverColor      Цвет верхней части кнопки при наведении
             * @param bottomHoverColor   Цвет нижней части кнопки при наведении
             * @param shadowColor        Цвет тени кнопки
             * @param outlineColor       Цвет обводки
             * @param outlineThickness   Толщина обводки
             */
            ButtonWithColor(
                const sf::FloatRect& rectangle,
                const float& radius,
                const sf::Sprite& icon,
                const std::function<void()>& function = [](){},
                sf::Color topDefaultColor = sf::Color(68, 164, 208),
                sf::Color bottomDefaultColor = sf::Color(11, 86, 125),
                sf::Color topHoverColor = sf::Color(24, 110, 151),
                sf::Color bottomHoverColor = sf::Color(7, 50, 73),
                sf::Color shadowColor = sf::Color(94, 140, 164, 160),
                sf::Color outlineColor = sf::Color(14, 52, 74),
                float outlineThickness = 4.f
            );

            /**
             * @brief Отрисовать кнопку с цветом на целевом объекте
             * 
             * @param target Указатель на объект отрисовки
             */
            void Draw(sf::RenderTarget* target) const;

            /**
             * @brief Установить позицию кнопки
             * 
             * @param x Координата x
             * @param y Координата y
             */
            void SetPosition(float x, float y);

            /**
             * @brief Получить флаг, указывающий на выбор кнопки
             * 
             * @return true, если кнопка выбрана, в противном случае - false
             */
            bool& GetSelected() { return _isSelected; }
        };


    private:

        /**
         * @brief Структура Decor для хранения декоративных параметров
         */
        struct Decor
        {
            sf::FloatRect sizeofButton = sf::FloatRect{0.f, 0.f, 90.f, 90};      ///< Размер кнопки
            float buttonRadius = 15.f;                                           ///< Радиус кнопки
            float sizeBetweenButtons = 127.5f;                                   ///< Расстояние между кнопками
            float stepBetweenTitleAndColor = 20.f;                               ///< Шаг между заголовком и цветом
            const int fontSize = 40;                                             ///< Размер шрифта
            sf::Color titleColor = sf::Color::White;                             ///< Цвет заголовка
            std::vector<sf::String> colors = {L"белые", L"случайно", L"черные"}; ///< Набор цветов
            float margin = 280.f;                                                ///< Отступ
        } Decor;

        int _position;     ///< Позиция
        Text _currentText; ///< Текущий текст

        std::vector<ButtonWithColor> _colorButtons; ///< Вектор кнопок с цветом

        void UpdateColor();  ///< Обновление цвета
        void ResetButtons(); ///< Сброс кнопок
        void init();         ///< Инициализация
        void Align();        ///< Выравнивание

    public:
        ComputerStartColor() = default;                       ///< Конструктор по умолчанию
        ComputerStartColor(sf::RenderTexture* renderTexture); ///< Конструктор с параметром

        ~ComputerStartColor() {} ///< Деструктор

        /**
         * @brief Получить высоту настройки
         * 
         * @return Высота настройки
         */
        float GetHeight() const override
        {
            return std::max(_settingName.getGlobalBounds().height, Decor.sizeofButton.height);
        }

        /**
         * @brief Получить цвет для хода компьютера
         * 
         * @return Цвет для хода компьютера
         */
        MoveColor GetOpponentMoveColor() const
        {
            return _position == 0 ? MoveColor::Black : _position == 2 ? MoveColor::White : ((rand() % 2) * 2 ? MoveColor::Black : MoveColor::White);
        }

        void SetPositionOnOY(float positionOnOY) override;                          ///< Установить позицию по OY
        void Draw(sf::RenderTarget* target) override;                               ///< Отрисовать
        void Update(const sf::Vector2f& mousePos, const sf::Event& event) override; ///< Обновить
    };
}

#endif