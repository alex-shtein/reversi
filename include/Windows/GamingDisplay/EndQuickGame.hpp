#ifndef END_QUICK_GAME_HPP
#define END_QUICK_GAME_HPP

#include <SFML/Graphics.hpp>
#include "./EndGame.hpp"
#include "../PopWindow.hpp"
#include "../../Transition.hpp"
#include "../../Particulars.hpp"

namespace game
{
    class GamingDisplay;

    /**
     * @brief Класс для отображения окна завершения быстрой игры.
     */
    class EndQuickGame : public PopWindow
    {
    private:

        /**
         * @brief Внутренняя структура для хранения декоративных параметров отображения окна
         */
        struct Decor
        {
            float titlePositionOnOY = 40.f;                     ///< Вертикальное положение заголовка
            float stepBetweenTextFields = 40.f;                 ///< Отступ между текстовыми полями
            float margin = 80.f;                                ///< Внешний отступ окна
            float stepBetweenAvatarAndName = 20.f;              ///< Отступ между аватаром и именем
            float backgroundWidth = 1000.f;                     ///< Ширина фона окна
            float backgroundRadius = 30.f;                      ///< Радиус закругления углов фона окна
            sf::FloatRect buttonSize = {0.f, 0.f, 375.f, 60.f}; ///< Размер кнопки
            float buttonRadius = 15.f;                          ///< Радиус закругления углов кнопки
        } Decor;                                                ///< Экземпляр структуры для хранения декоративных параметров

        GamingDisplay* _gamingDisplay;  ///< Указатель на игровой дисплей
        Rectangle _background;          ///< Объект класса "Rectangle" для отображения фона
        Text _title;                    ///< Заголовок окна
        Winner _winner;                 ///< Объект класса "Winner" представляющий победителя
        Text _draw;                     ///< Текст для отображения ничьей
        Text _timeTitle;                ///< Заголовок времени
        Text _timeText;                 ///< Текущее время
        Score _gameScore;               ///< Объект класса "Score" для отображения счета игры
        ButtonWithText _backToMainMenu; ///< Кнопка "Вернуться в меню"
        ButtonWithText _retry;          ///< Кнопка "Рестарт"

        void init();  ///< Метод инициализации окна
    
        void Align(); ///< Метод выравнивания элементов в окне
    public:

        /**
         * @brief Конструктор класса EndQuickGame по умолчанию.
         */
        EndQuickGame() = default;

        /**
         * @brief Конструктор класса EndQuickGame.
         * 
         * @param gameStack     Указатель на стек игры.
         * @param gamingDisplay Указатель на игровой дисплей.
         */
        EndQuickGame(game::GameStack* gameStack, GamingDisplay* gamingDisplay);

        /**
         * @brief Деструктор класса EndQuickGame.
         */
        ~EndQuickGame();

        /**
         * @brief Метод получения размера окна.
         * 
         * @return Возвращает размер окна в виде вектора (ширина, высота).
         */
        sf::Vector2f GetSize() const override;

        /**
         * @brief Метод установки смещения для всех компонентов окна.
         * 
         * @param offset Вектор смещения (x, y).
         */
        void SetOffset(sf::Vector2f offset);

        /**
         * @brief Метод установки позиции окна.
         * 
         * @param position Позиция окна.
         */
        void SetPosition(const sf::Vector2f& position) override;

        /**
         * @brief Метод отрисовки окна.
         * 
         * @param target Цель отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Метод отрисовки заднего окна из стека игры.
         * 
         * @param target Цель отрисовки.
         */
        void DrawBackWindow(sf::RenderTarget* target) override;

        /**
         * @brief Метод отрисовки плавающего окна.
         * 
         * @param target Цель отрисовки.
         */
        void DrawPopupWindow(sf::RenderTarget* target) override;

        /**
         * @brief Метод обновления плавающего окна.
         * 
         * @param dt Время прошедшее с последнего обновления.
         */
        void Update(float dt) override;

        /**
         * @brief Метод обработки событий для плавающего окна.
         * 
         * @param event         Событие.
         * @param mousePosition Позиция курсора.
         * 
         * @return Возвращает true, если обработка события прошла успешно, иначе false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePosition) override;
    };
}

#endif