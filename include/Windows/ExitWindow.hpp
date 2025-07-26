#ifndef EXIT_WINDOW_HPP
#define EXIT_WINDOW_HPP

#include <iostream>
#include "./GameStack.hpp"
#include "./PopWindow.hpp"
#include "../Particulars.hpp"

namespace game
{

    /**
     * @brief Вложенный класс ExitWindow представляет собой окно выхода из игры.
     */
    class ExitWindow : public PopWindow
    {
    private:

        /**
         * @brief Структура DesignSettings содержит настройки дизайна окна выхода.
         */
        struct DesignSettings
        {
            const float stepBetweenTitleAndButtons = 60.f;     ///< Шаг между заголовком и кнопками
            sf::FloatRect buttonSize = {0.f, 0.f, 90.f, 90.f}; ///< Размер кнопок
            float buttonRadius = 15.f;                         ///< Радиус кнопок
            float titlePositionOnOY = 45.f;                    ///< Позиция заголовка по оси OY
            float margin = 300.f;                              ///< Отступ
        } Decor;

        game::Rectangle _background;          ///< Задний фон окна
        Text _title;                          ///< Заголовок окна
        std::vector<ButtonWithText> _buttons; ///< Кнопки с текстом

        void init();  ///< Инициализация элементов окна выхода
        void Align(); ///< Выравнивание элементов окна выхода

    public:
        ExitWindow() = default; ///< Конструктор по умолчанию для класса ExitWindow

        /**
         * @brief Конструктор класса ExitWindow.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        ExitWindow(game::GameStack* gameStack);

        /**
         * @brief Получение размера окна выхода.
         * 
         * @return Размер окна в виде вектора.
         */
        sf::Vector2f GetSize() const override
        {
            return {_background.getBounds().width, _background.getBounds().height};
        }

        /**
         * @brief Установка позиции окна выхода.
         * 
         * @param position Позиция окна в виде вектора.
         */
        void SetPosition(const sf::Vector2f& position) override
        {
            SetOffset(position.x - _background.GetPosition().x, position.y - _background.GetPosition().y);
        }

        /**
         * @brief Отрисовка заднего фона окна выхода.
         * 
         * @param target Указатель на объект отрисовки.
         */
        void DrawBackWindow(sf::RenderTarget* target) override
        {
            GetGameStack()->Penultimate()->Draw(target);
        }

        /**
         * @brief Отрисовка всплывающего окна выхода.
         * 
         * @param target Указатель на объект отрисовки.
         */
        void DrawPopupWindow(sf::RenderTarget* target) override;

        /**
         * @brief Отрисовка окна выхода.
         * 
         * @param target Указатель на объект отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;
        
        /**
         * @brief Обновление окна выхода.
         * 
         * @param dt Прошедшее время.
         */
        void Update(float dt) override { return; }

        /**
         * @brief Обработка событий для окна выхода.
         * 
         * @param event        Событие ввода от пользователя.
         * @param mousePositon Позиция указателя мыши.
         * 
         * @return true, если событие было обработано, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;

        /**
         * @brief Установка смещения для окна выхода по осям OX и OY.
         * 
         * @param OXOffset Смещение по оси OX.
         * @param OYOffset Смещение по оси OY.
         */
        void SetOffset(float OXOffset, float OYOffset);
    };
}

#endif