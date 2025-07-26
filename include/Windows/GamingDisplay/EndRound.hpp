#ifndef END_ROUND_HPP
#define END_ROUND_HPP

#include <SFML/Graphics.hpp>
#include "./GameInformation.hpp"
#include "../PopWindow.hpp"
#include "../../Particulars.hpp"
#include "../../Transition.hpp"

namespace game
{
    class GamingDisplay;

    /**
     * @brief Класс, представляющий всплывающее окно с информацией о завершении раунда игры.
     */
    class EndRound : public PopWindow
    {
    private:

        /**
         * @brief Вложенная структура, содержащая параметры оформления всплывающего окна.
         */
        struct Decor
        {
            float titlePositionOnOY = 40.f;                          ///< Положение заголовка по оси OY 
            float stepBetweenTextFields = 40.f;                      ///< Шаг между текстовыми полями 
            float margin = 80.f;                                     ///< Внешний отступ 
            float stepBetweenAvatarAndName = 20.f;                   ///< Шаг между аватаром и именем победителя 
            sf::FloatRect backgroundSize = {0.f, 0.f, 900.f, 900.f}; ///< Размер фона 
            float backgroundRadius = 30.f;                           ///< Радиус закругления углов фона 
            sf::FloatRect buttonSize = {0.f, 0.f, 600.f, 70.f};      ///< Размер кнопки 
            float buttonRadius = 15.f;                               ///< Радиус закругления углов кнопки 
        } Decor;

        GamingDisplay* _gamingDisplay; ///< Указатель на экран игры
        Rectangle _background;         ///< Фон всплывающего окна 
        Text _title;                   ///< Заголовок окна
        Text _winnerText;              ///< Текст с информацией о победителе 
        sf::Sprite _winnerAvatar;      ///< Аватар победителя 
        Text _winnerName;              ///< Имя победителя 
        Text _timeTitle;               ///< Заголовок времени раунда 
        Text _timeText;                ///< Текущее время раунда 
        Score _roundScore;             ///< Счет в текущем раунде 
        Score _gameScore;              ///< Общий счет в игре 
        ButtonWithText _button;        ///< Кнопка всплывающего окна 

        void init();  ///< Метод инициализации окна
        void Align(); ///< Метод выравнивания элементов в окне
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        EndRound() = default;

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param gameStack     Указатель на стек игры.
         * @param gamingDisplay Указатель на экран игры.
         */
        EndRound(game::GameStack* gameStack, GamingDisplay* gamingDisplay);

        /**
         * @brief Деструктор.
         */
        ~EndRound();

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
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}

#endif