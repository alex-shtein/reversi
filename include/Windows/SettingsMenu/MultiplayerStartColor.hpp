#ifndef MULTIPLAYER_START_COLOR_HPP
#define MULTIPLAYER_START_COLOR_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "./IGameSetting.hpp"
#include "../../Particulars.hpp"
#include "../../ResourceLoader.hpp"
#include "../../Setup/GameSetup.hpp"
#include "../../Setup/PlayerSetup.hpp"

namespace game
{
    /**
     * @brief Класс TextBox, представляющий текстовое поле
     * 
     * @details Унаследован от Rectangle
     */
    class TextBox : public Rectangle
    {
    private:
        Text _currentText;               ///< Текущий текст
        Text _hintText;                  ///< Текст-подсказка
        float _elapsedTime = 0.f;        ///< Прошедшее время
        bool _isUpdate = true;           ///< Флаг обновления
        bool _isActive = false;          ///< Флаг активности
        bool _isHover = false;           ///< Флаг наведения
        Text _cursor = Text({L"I", 40}); ///< Текущий курсор

        void init() ///< Инициализация
        {
            SetPosition(0.f, 0.f);
        }
    public:
        TextBox(); ///< Конструктор

        TextBox(const sf::String& text) ///< Конструктор с параметром
            : TextBox()
        {
            _currentText.SetString(text);
        }

        ~TextBox() {} ///< Деструктор

        /**
         * @brief Обновить позицию курсора
         */
        void UpdateCursorPosition() 
        {
            _cursor.setPosition(_currentText.getPosition().x + _currentText.getGlobalBounds().width / 2.f + _cursor.getGlobalBounds().width, GetPosition().y);
        }

        /**
         * @brief Установить позицию
         * 
         * @param x Координата x
         * @param y Координата y
         */
        void SetPosition(float x, float y);

        /**
         * @brief Обновить текстовое поле
         * 
         * @param mousePos Позиция мыши
         * @param event Событие
         */
        void Update(const sf::Vector2f& mousePos, const sf::Event& event);

        /**
         * @brief Проверить, заполнено ли текстовое поле
         * 
         * @return true, если текстовое поле заполнено, в противном случае - false
         */
        bool IsFill() const
        {
            return _currentText.getString().getSize() > 0;
        }

        /**
         * @brief Обновить текстовое поле
         * 
         * @param dt Время с последнего обновления
         */
        void Update(float dt);

        /**
         * @brief Отрисовать текстовое поле
         * 
         * @param target Цель отрисовки
         */
        void Draw(sf::RenderTarget* target);

         /**
         * @brief Получить текст из текстового поля
         * 
         * @return Текущий текст
         */
        sf::String GetText() const { return _currentText.getString(); }

        /**
         * @brief Установить текст в текстовом поле
         * 
         * @param text Текст для установки
         */
        void SetText(const sf::String& text) { _currentText.SetString(text); }
    };

    /**
     * @brief Класс MultiplayerStartColor, представляющий настройку выбора цвета для мультиплеера
     * 
     * @details Унаследован от IGameSetting
     */
    class MultiplayerStartColor : public IGameSetting
    {
    private:
        /**
         * @brief Структура Decor для хранения декоративных параметров
         */
        struct Decor
        {
            sf::FloatRect sizeofButton = sf::FloatRect{0.f, 0.f, 90.f, 90}; ///< Размер кнопки
            float buttonRadius = 15.f;                                      ///< Радиус кнопки
            float sizeBetweenButtons = 80.f;                                ///< Расстояние между кнопками
            float stepBetweenAvatarAndName = 30.f;                          ///< Шаг между аватаром и именем
            const int fontSize = 40;                                        ///< Размер шрифта
            sf::Color color = sf::Color::White;                             ///< Цвет
            float margin = 280.f;                                           ///< Отступ
        } Decor;

        sf::Sprite _avatar;            ///< Аватар
        sf::Sprite _opponentAvatar;    ///< Аватар противника
        Text _name;                    ///< Имя игрока
        TextBox _opponentName;         ///< Поле ввода имени противника
        ButtonWithIcon _opponentColor; ///< Кнопка выбора цвета противника
        ButtonWithIcon _color;         ///< Кнопка выбора цвета
        ButtonWithIcon _changeButton;  ///< Кнопка смены цвета

        MoveColor _currentOpponentColor = MoveColor::Black; ///< Текущий цвет противника

        void UpdateColor(); ///< Обновление цвета
        void init(); ///< Инициализация

    public:
        MultiplayerStartColor() = default;                       ///< Конструктор по умолчанию
        MultiplayerStartColor(sf::RenderTexture* renderTexture); ///< Конструктор с параметром

        ~MultiplayerStartColor() {} ///< Деструктор

        /**
         * @brief Выравнивание элементов
         * 
         */
        void Align();

        /**
         * @brief Получить высоту блока
         * 
         * @return Высота блока
         */
        float GetHeight() const
        {
            return std::max({_changeButton.getBounds().height, _opponentAvatar.getGlobalBounds().height, _opponentName.getBounds().height});
        }

        /**
         * @brief Установить позицию по OY
         * 
         * @param positionOnOY Позиция по OY
         */
        void SetPositionOnOY(float positionOnOY) override;

        /**
         * @brief Установить смещение по OY
         * 
         * @param OYOffset Смещение по OY
         */
        void SetOffsetOnOY(float OYOffset)
        {
            SetPositionOnOY(_name.getPosition().y + OYOffset);
        }

        /**
         * @brief Получить имя противника
         * 
         * @return Имя противника
         */
        sf::String GetOpponentName() const { return _opponentName.GetText(); }

        /**
         * @brief Получить цвет для хода противника
         * 
         * @return Цвет для хода противника
         */
        MoveColor GetOpponentMoveColor() const { return _currentOpponentColor; }

        /**
         * @brief Отрисовать настройку
         * 
         * @param target Цель отрисовки
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Обновить настройку
         * 
         * @param mousePos Позиция мыши
         * @param event    Событие
         */
        void Update(const sf::Vector2f& mousePos, const sf::Event& event) override;

        /**
         * @brief Обновить настройку
         * 
         * @param dt Время с последнего обновления
         */
        void Update(float dt) { _opponentName.Update(dt); }
    };

}

#endif