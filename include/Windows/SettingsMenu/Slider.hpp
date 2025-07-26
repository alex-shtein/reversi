#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>


namespace game
{
    /**
     * @brief Класс Slider, представляющий интерактивную полосу-слайдер.
     */
    class Slider : public sf::RectangleShape
    {
    private:

        /**
         * @brief Структура Decor для хранения декоративных параметров слайдера.
         */
        struct Decor
        {
            sf::Color markDefaultColor = sf::Color::White;              ///< Цвет обычной метки
            sf::Color markSelectedColor = sf::Color(24, 110, 151);      ///< Цвет выбранной метки
            sf::Color sliderColor = sf::Color::White;                   ///< Цвет слайдера
            sf::Color markSelectedOutlineColor = sf::Color(14, 52, 74); ///< Цвет обводки выбранной метки
            sf::Color markDefaultOutlineColor = sf::Color::White;       ///< Цвет обводки обычной метки
            float markSelectedOutlineThickness = 4.f;                   ///< Толщина обводки выбранной метки
            float markDefaultOutlineThickness = 0.f;                    ///< Толщина обводки обычной метки
            float markRadius = 15.f;                                    ///< Радиус обычной метки
            float selectedMarkRadius = 20.f;                            ///< Радиус выбранной метки
            float sliderHeight = 10.f;                                  ///< Высота слайдера
        } Decor;

        int _begin;                          ///< Начальное значение
        int _valueStep;                      ///< Шаг значений
        int _total;                          ///< Общее количество значений
        float _step;                         ///< Шаг слайдера
        int _currentIndex;                   ///< Текущий индекс
        std::vector<sf::CircleShape> _marks; ///< Вектор меток
        mutable bool _locked = false;        ///< Флаг блокировки

        /**
         * @brief Инициализация слайдера.
         *        Устанавливает размер, цвет и отметки слайдера с их стандартными параметрами,
         *        а также задает активную отметку.
         */
        void init();
        
        /**
         * @brief Выравнивание слайдера и его отметок.
         *        Устанавливает позицию слайдера и отметок на экране так, чтобы они были выровнены по горизонтали.
         */
        void Align();

        /**
         * @brief Обновление состояния слайдера на основе позиции мыши
         *        Если слайдер заблокирован (например, зажата левая кнопка мыши), обновляет активную отметку в зависимости от положения мыши.
         *        Если положение мыши находится вне пределов слайдера, активной становится крайняя отметка.
         * 
         * @param OXMousePosition Позиция мыши по горизонтали.
         */
        void Update(float OXMousePosition);

    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Slider() = default;
        
        /**
         * @brief Конструктор класса Slider.
         * 
         * @param begin        Начальное значение слайдера.
         * @param valueStep    Шаг изменения значения.
         * @param total        Общее количество отметок.
         * @param step         Ширина шага между отметками.
         * @param currentIndex Индекс активной отметки.
         */
        Slider(int begin, int valueStep, int total, float step, int currentIndex = 0);

        /**
         * @brief Заблокировать слайдер.
         */
        void Lock() const { _locked = true; }

        /**
         * @brief Разблокировать слайдер.
         */
        void Unlock() const { _locked = false; }

        /**
         * @brief Получить текущее значение слайдера.
         * 
         * @return Текущее значение.
         */
        int GetValue() const { return _begin + _currentIndex * _valueStep; }
        
        /**
         * @brief Установить позицию.
         * 
         * @param x Координата по оси X.
         * @param y Координата по оси Y.
         */
        void SetPosition(float x, float y)
        {
            SetOffset(x - getPosition().x, y - getPosition().y);
        }

        /**
         * @brief Установить смещение.
         * 
         * @param OXOffset Смещение по оси OX.
         * @param OYOffset Смещение по оси OY.
         */
        void SetOffset(float OXOffset, float OYOffset);

        /**
         * @brief Получить размер слайдера.
         * 
         * @return Размер слайдера.
         */
        sf::Vector2f GetSize() const
        {
            return {getSize().x + 2 * Decor.markRadius, std::max(getSize().y, 2 * Decor.selectedMarkRadius)};
        }

        /**
         * @brief Сброс настроек отметок слайдера.
         *        Устанавливает отметкам слайдера их стандартный вид (радиус, цвет и толщина контура).
         */
        void ResetMarks();

        /**
         * @brief Установка активной отметки на слайдере.
         * 
         * @param index Индекс отметки, которую нужно сделать активной.
         */
        void SetActiveMark(int index);

        /**
         * @brief Отрисовка слайдера и его отметок.
         * 
         * @param target Цель для отрисовки.
         */
        void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Обновление состояния слайдера при взаимодействии пользователя.
         * 
         * @param event        Событие, вызванное пользовательским взаимодействием.
         * @param mousePositon Текущая позиция курсора.
         * 
         * @return true, если состояние слайдера обновлено, в противном случае - false.
         */
        bool Update(const sf::Event& event, const sf::Vector2f& mousePositon);
    };
}

#endif