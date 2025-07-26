#ifndef REVERSI_TITLE_HPP
#define REVERSI_TITLE_HPP

#include <SFML/Graphics.hpp>
#include "../GameStack.hpp"
#include "../ResourceLoader.hpp"
#include "../Particulars.hpp"

namespace game
{

    /**
     * @brief Класс ReversiTitle представляет собой состояние игры "Реверси" с заголовком.
     */
    class ReversiTitle : public State
    {
    private:
        struct Decor
        {
            float titlePositionOnOY = 80.f; ///< Позиция заголовка по оси OY
            int titleFontSize = 128;        ///< Размер шрифта заголовка
        } Decor;

        Title _title;                ///< Заголовок игры
        sf::Sprite _mountainOfChips; ///< Спрайт "горы фишек"

        /**
         * @brief Инициализация объекта ReversiTitle.
         */
        void init()
        {
            _mountainOfChips.setOrigin(_mountainOfChips.getGlobalBounds().width / 2.f, _mountainOfChips.getGlobalBounds().height / 2.f);
        }

        /**
         * @brief Выровнять элементы на экране.
         */
        void Align();
    public:

        /**
         * @brief Конструктор класса ReversiTitle.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        ReversiTitle(GameStack* gameStack);

        /**
         * @brief Получить позицию заголовка.
         * 
         * @return Позиция заголовка.
         */
        sf::Vector2f GetTitlePosition() const { return _title.GetPosition(); }

        /**
         * @brief Получить высоту заголовка.
         * 
         * @return Высота заголовка.
         */
        float GetTitleHeight() const { return _title.GetHeight(); }

        /**
         * @brief Отрисовать состояние игры "Реверси" с заголовком.
         * 
         * @param target Цель для отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target);

        virtual ~ReversiTitle() {} ///< Виртуальный деструктор класса ReversiTitle
    };
}

#endif