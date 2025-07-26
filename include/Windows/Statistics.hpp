#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include <SFML/Graphics.hpp>
#include "./ReversiTitle.hpp"
#include "./Transition.hpp"
#include "../Particulars.hpp"
#include "../Setup/ResultsSetup.hpp"

namespace game
{

    /**
     * @brief Класс, отвечающий за экран статистики игрока.
     * 
     * @param backButtonMargin        Отступ кнопки "назад".
     * @param buttonSize              Размер кнопки.
     * @param buttonRadius            Радиус скругления углов кнопки.
     * @param stepBetweenTitleAndText Расстояние между заголовком и текстом статистики.
     * @param stepBetweenStatistcs    Расстояние между статистиками.
     * @param margin                  Отступ от края экрана до статистики.
     * @param _back                   Кнопка "назад".
     * @param _statistics             Вектор с текстом статистики.
     */
    class Statistics : public ReversiTitle
    {
    private:
        struct Decor
        {
            float backButtonMargin = 30.f;
            sf::FloatRect buttonSize = sf::FloatRect({0.f, 0.f, 90.f, 90.f});
            float buttonRadius = 15.f;

            float stepBetweenTitleAndText = 100.f;
            float stepBetweenStatistcs = 50.f;
            float margin = 550.f;
        } Decor;

        ButtonWithIcon _back;

        std::vector<sf::Vector2<game::Text>> _statistics;

        /**
         * @brief Метод для инициализации объектов и загрузки настроек.
         */
        void init() {}

        /**
         * @brief Метод для выравнивания элементов интерфейса.
         */
        void Align();

    public:
        /**
         * @brief Конструктор класса Statistics.
         * 
         * @param gameStack Указатель на игровой стек.
         */
        Statistics(game::GameStack* gameStack);

        /**
         * @brief Деструктор класса Statistics.
         */
        ~Statistics() override {}

        /**
         * @brief Метод для отрисовки элементов интерфейса.
         * 
         * @param target Указатель на целевой объект отрисовки.
         */
        void Draw(sf::RenderTarget* target) override;

        /**
         * @brief Метод для обновления состояния объектов.
         * 
         * @param dt Время, прошедшее с предыдущего кадра.
         */
        void Update(float dt) override {}

        /**
         * @brief Метод для обработки событий мыши.
         * 
         * @param event         Событие мыши.
         * @param mousePosition Позиция курсора мыши.
         * 
         * @return true, если событие было обработано, иначе false
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) override;
    };
}
    
#endif