#ifndef POP_WINDOW_HPP
#define POP_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include "./GameStack.hpp"
#include "../Transition.hpp"

namespace game
{

    /**
     * @brief Класс PopWindow представляет собой абстрактное всплывающее окно.
     */
    class PopWindow : public State
    {
    protected:
        sf::RectangleShape _blur; ///< Прямоугольник для размытия заднего фона
    public:
        /**
         * @brief Конструктор класса PopWindow.
         * @param gameStack Указатель на игровой стек.
         */
        PopWindow(game::GameStack* gameStack);

        virtual ~PopWindow() {}; ///< Виртуальный деструктор класса PopWindow

        /**
         * @brief Получить размер всплывающего окна.
         * 
         * @return Размер всплывающего окна.
         */
        virtual sf::Vector2f GetSize() const = 0;

        /**
         * @brief Установить позицию всплывающего окна.
         * 
         * @param position Новая позиция всплывающего окна.
         */
        virtual void SetPosition(const sf::Vector2f& position) = 0;

        /**
         * @brief Отрисовать задний фон всплывающего окна.
         * 
         * @param target Цель для отрисовки.
         */
        virtual void DrawBackWindow(sf::RenderTarget* target) = 0;

        /**
         * @brief Отрисовать всплывающее окно.
         * 
         * @param target Цель для отрисовки.
         */
        virtual void DrawPopupWindow(sf::RenderTarget* target) = 0;

        /**
         * @brief Выполнить анимацию перехода.
         * 
         * @param direction Направление анимации.
         */
        void TransitAnimation(Direction direction);
    };
}

#endif