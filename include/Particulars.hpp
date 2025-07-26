#ifndef PARTICULARS_HPP
#define PARTICULARS_HPP

#include <SFML/Graphics.hpp>
#include "./ResourceLoader.hpp"

namespace game
{
    struct TextOptions
    {
        sf::String message;    ///< Сообщение текста
        int sizeFont;          ///< Размер шрифта
        sf::Color textColor;   ///< Цвет текста
        std::string fontFile;  ///< Файл шрифта
        float bord;            ///< Толщина границы
        sf::Color borderColor; ///< Цвет границы

        /**
         * @brief Конструктор структуры TextOptions.
         * 
         * @param message     Сообщение текста.
         * @param sizeFont    Размер шрифта.
         * @param textColor   Цвет текста.
         * @param fontFile    Путь к файлу шрифта.
         * @param bord        Толщина границы.
         * @param borderColor Цвет границы.
         */
        TextOptions(const sf::String& message = "", int sizeFont = 64, sf::Color textColor = sf::Color::White, const std::string& fontFile = "../ponterpc.ttf", float bord = 0.f, sf::Color borderColor = sf::Color::Black)
            : message(message), sizeFont(sizeFont), textColor(textColor), fontFile(fontFile), bord(bord), borderColor(borderColor)
        {};
    };

    class Text : public sf::Text
    {
    public:

        /**
         * @brief Конструктор класса Text.
         */
        Text() = default;

        /**
         * @brief Конструктор класса Text с использованием опций текста.
         * 
         * @param textOptions Настройки текста.
         */
        Text(const game::TextOptions& textOptions);

        /**
         * @brief Установка строки текста.
         * 
         * @param string Строка текста.
         */
        void SetString(const sf::String& string);
    };

    class Title
    {
    private:

        /**
         * @brief Внутренняя структура для оформления особенностей заголовка.
         */
        struct Decor
        {
            float lineWidth = 150.f;                 ///< Ширина линии
            float lineHeight = 10.f;                 ///< Высота линии
            float stepBetweenLinesAndTitle = 40.f;   ///< Шаг между линиями и заголовком
            sf::Color linesColor = sf::Color::White; ///< Цвет линий
        } Decor;

        Text _title;                            ///< Текст заголовка
        std::vector<sf::RectangleShape> _lines; ///< Линии декорации
        sf::Sprite _chips;                      ///< Спрайт "фишек"

        /**
         * @brief Инициализация элементов заголовка.
         */
        void init();

        /**
         * @brief Выровнять элементы внутри заголовка.
         */
        void Align();

    public:
        /**
         * @brief Конструктор заголовка по умолчанию.
         */
        Title() = default;

        /**
         * @brief Конструктор заголовка с указанием текста и спрайта.
         * 
         * @param title Текст заголовка.
         * @param chips Спрайт "фишек".
         */
        Title(Text title, sf::Sprite chips);

        /**
         * @brief Деструктор заголовка.
         */
        ~Title() {}

        /**
         * @brief Установить позицию заголовка с учётом смещения.
         * 
         * @param x Координата по оси X.
         * @param y Координата по оси Y.
         */
        void SetPosition(float x, float y)
        {
            SetOffset(sf::Vector2f(x, y) - sf::Vector2f(_title.getPosition().x, _lines[0].getPosition().y + GetHeight() / 2.f));
        }

        /**
         * @brief Установить смещение заголовка.
         * 
         * @param offset Вектор смещения.
         */
        void SetOffset(sf::Vector2f offset);

        /**
         * @brief Получить текущую позицию заголовка.
         * 
         * @return Текущая позиция заголовка.
         */
        sf::Vector2f GetPosition() const
        {
            return _title.getPosition();
        }

        /**
         * @brief Получить высоту заголовка.
         * 
         * @return Высота заголовка.
         */
        float GetHeight() const
        {
            return _lines.back().getPosition().y - _lines[0].getPosition().y + _lines.back().getSize().y;
        }

        /**
         * @brief Отрисовать заголовок.
         * 
         * @param target Цель для отрисовки.
         */
        void Draw(sf::RenderTarget* target);
    };

    /**
     * @brief Класс, представляющий прямоугольник, унаследованный от sf::VertexArray.
     */
    class Rectangle : public sf::VertexArray
    {
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Rectangle() = default;

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param rectangle        Прямоугольник типа sf::FloatRect.
         * @param radius           Радиус скругления углов.
         * @param outlineThickness Толщина обводки.
         * @param outlineColor     Цвет обводки.
         * @param topColor         Цвет верхней части прямоугольника.
         * @param bottomColor      Цвет нижней части прямоугольника.
         */
        Rectangle(const sf::FloatRect& rectangle, const float& radius, 
        float outlineThickness = 4.f, sf::Color outlineColor = sf::Color(14, 52, 74), 
        sf::Color topColor = sf::Color(68, 164, 208), sf::Color bottomColor = sf::Color(11, 86, 125));

        virtual ~Rectangle() {}

        /**
         * @brief Установить позицию прямоугольника по координатам (x, y).
         * 
         * @param x Координата x.
         * @param y Координата y.
         */
        virtual void SetPosition(float x, float y) 
        { 
            SetPosition({x, y});
        }

        /**
         * @brief Установить позицию прямоугольника.
         * 
         * @param position Позиция типа sf::Vector2f.
         */
        void SetPosition(const sf::Vector2f& position);

        /**
         * @brief Установить толщину обводки.
         * 
         * @param thickness Толщина обводки.
         */
        void SetOutlineThickness(float thickness);

        /**
         * @brief Получить позицию прямоугольника.
         * 
         * @return Позиция типа sf::Vector2f.
         */
        sf::Vector2f GetPosition() const 
        {
            return _center;
        }

        /**
         * @brief Установить цвет верхней части прямоугольника.
         * 
         * @param topColor Цвет верхней части.
         */
        void SetTopColor(sf::Color topColor);

        /**
         * @brief Установить цвет нижней части прямоугольника.
         * 
         * @param bottomColor Цвет нижней части.
         */
        void SetBottomColor(sf::Color bottomColor);

        /**
         * @brief Отрисовать прямоугольник на целевом объекте.
         * 
         * @param target Указатель на объект отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target) const;
    private:
        sf::Vector2f _center;
        sf::ConvexShape _outline;
        sf::Color _outlineColor;
        float _outlineThickness;
    };

    /**
     * @brief Класс Shadow, унаследованный от Rectangle.
     */
    class Shadow : public Rectangle
    {
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Shadow() : Rectangle() {}

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param rectangle Прямоугольник типа sf::FloatRect.
         * @param radius    Радиус скругления углов.
         * @param color     Цвет тени.
         * @param offset    Смещение тени.
         */
        Shadow(const sf::FloatRect& rectangle, const float& radius, sf::Color color, float offset = 6.f);

        ~Shadow() {};
        
        /**
         * @brief Установить цвет заливки тени.
         * 
         * @param color Цвет заливки.
         */
        void SetFillColor(sf::Color color);

        /**
         * @brief Получить цвет заливки тени.
         * 
         * @return Цвет заливки.
         */
        sf::Color GetFillColor() const 
        { 
            return _color;
        }

        /**
         * @brief Установить позицию тени.
         * 
         * @param x Координата x.
         * @param y Координата y.
         */
        void SetPosition(float x, float y) 
        { 
            Rectangle::SetPosition(x, y + _offset); 
        }

        /**
         * @brief Отрисовать тень на целевом объекте.
         * 
         * @param target Указатель на объект отрисовки.
         */
        void Draw(sf::RenderTarget* target) const 
        { 
            Rectangle::Draw(target); 
        }
    private:
        sf::Color _color; ///< Цвет заливки тени
        float _offset;    ///< Смещение тени
    };

    /**
     * @brief Класс Button, унаследованный от Rectangle.
     */
    class Button : public Rectangle
    {
    private:
        Shadow _shadow;                  ///< Тень кнопки
        std::function<void()> _function; ///< Функция, связанная с нажатием кнопки
        sf::Color _topDefaultColor;      ///< Цвет верхней части кнопки по умолчанию
        sf::Color _bottomDefaultColor;   ///< Цвет нижней части кнопки по умолчанию
        sf::Color _topHoverColor;        ///< Цвет верхней части кнопки при наведении
        sf::Color _bottomHoverColor;     ///< Цвет нижней части кнопки при наведении
        mutable bool _pointed = false;   ///< Флаг, указывающий на то, находится ли указатель мыши над кнопкой
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        Button() : Rectangle() {}

        virtual ~Button() {}

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param rectangle          Прямоугольник типа sf::FloatRect.
         * @param radius             Радиус скругления углов.
         * @param function           Функция, связанная с нажатием кнопки.
         * @param topDefaultColor    Цвет верхней части кнопки по умолчанию.
         * @param bottomDefaultColor Цвет нижней части кнопки по умолчанию.
         * @param topHoverColor      Цвет верхней части кнопки при наведении.
         * @param bottomHoverColor   Цвет нижней части кнопки при наведении.
         * @param shadowColor        Цвет тени кнопки.
         * @param outlineColor       Цвет обводки.
         * @param outlineThickness   Толщина обводки.
         */
        Button(const sf::FloatRect rectangle, const float radius, std::function<void()> function, 
                sf::Color topDefaultColor, 
                sf::Color bottomDefaultColor,
                sf::Color topHoverColor,
                sf::Color bottomHoverColor,
                sf::Color shadowColor,
                sf::Color outlineColor,
                float outlineThickness            
            );

        /**
         * @brief Получить цвет верхней части кнопки по умолчанию.
         * 
         * @return Цвет верхней части кнопки.
         */
        sf::Color GetTopDefaultColor() const { return _topDefaultColor; }

        /**
         * @brief Получить цвет нижней части кнопки по умолчанию.
         * 
         * @return Цвет нижней части кнопки.
         */
        sf::Color GetBottomDefaultColor() const { return _bottomDefaultColor; }

        /**
         * @brief Получить цвет верхней части кнопки при наведении.
         * 
         * @return Цвет верхней части кнопки.
         */
        sf::Color GetTopHoverColor() const { return _topHoverColor; }

        /**
         * @brief Получить цвет нижней части кнопки при наведении.
         * 
         * @return Цвет нижней части кнопки.
         */
        sf::Color GetBottomHoverColor() const { return _bottomHoverColor; }

        /**
         * @brief Установить позицию кнопки.
         * 
         * @param x Координата x.
         * @param y Координата y.
         */
        virtual void SetPosition(float x, float y);

        /**
         * @brief Отрисовать кнопку на целевом объекте.
         * 
         * @param target Указатель на объект отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Проверить, находится ли указатель мыши над кнопкой.
         * 
         * @param position Позиция указателя мыши.
         * 
         * @return true, если указатель мыши находится над кнопкой, в противном случае - false.
         */
        bool IsMouseOver(const sf::Vector2f& position) const
        {
            return Rectangle::getBounds().contains(position);
        }

        /**
         * @brief Проверить, была ли нажата кнопка.
         * 
         * @param event    Событие мыши.
         * @param position Позиция указателя мыши.
         * 
         * @return true, если кнопка была нажата, в противном случае - false.
         */
        bool IsPressed(const sf::Event& event, const sf::Vector2f& position) const;

        /**
         * @brief Обновить состояние кнопки в зависимости от позиции указателя мыши.
         * 
         * @param mousePos Позиция указателя мыши.
         * 
         * @return true, если состояние было изменено, в противном случае - false.
         */
        bool Update(const sf::Vector2f& mousePos);

        /**
         * @brief Обновить состояние кнопки в зависимости от позиции указателя мыши и события мыши.
         * 
         * @param mousePos Позиция указателя мыши.
         * @param event    Событие мыши.
         * 
         * @return true, если состояние было изменено, в противном случае - false.
         */
        bool Update(const sf::Vector2f& mousePos, const sf::Event& event);

        /**
         * @brief Установить функцию, связанную с нажатием кнопки.
         * 
         * @param function Функция, связанная с нажатием кнопки.
         */
        void SetFunction(std::function<void()> function)
        { 
            _function = function; 
        }
        
        /**
         * @brief Получить функцию, связанную с нажатием кнопки.
         * 
         * @return Функция, связанная с нажатием кнопки.
         */
        std::function<void()> GetFunction() const
        { 
            return _function; 
        }

        /**
         * @brief Получить флаг, указывающий на то, находится ли указатель мыши над кнопкой.
         * 
         * @return Флаг, указывающий на наличие указателя мыши.
         */
        bool& GetPointed() 
        { 
            return _pointed; 
        }
    };
    
    /**
     * @brief Класс ButtonWithText, унаследованный от Button.
     */
    class ButtonWithText : public Button
    {
    private:
        game::Text _text; ///< Текст на кнопке
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        ButtonWithText() = default;

        /**
         * @brief Конструктор с параметрами
         * 
         * @param rectangle          Прямоугольник типа sf::FloatRect.
         * @param radius             Радиус скругления углов.
         * @param text               Текст на кнопке.
         * @param function           Функция, связанная с нажатием кнопки.
         * @param topDefaultColor    Цвет верхней части кнопки по умолчанию.
         * @param bottomDefaultColor Цвет нижней части кнопки по умолчанию.
         * @param topHoverColor      Цвет верхней части кнопки при наведении.
         * @param bottomHoverColor   Цвет нижней части кнопки при наведении.
         * @param shadowColor        Цвет тени кнопки.
         * @param outlineColor       Цвет обводки.
         * @param outlineThickness   Толщина обводки.
         */
        ButtonWithText(const sf::FloatRect& rectangle, const float& radius, const game::Text& text, const std::function<void()>& function = [](){}, 
                sf::Color topDefaultColor = sf::Color(68, 164, 208),
                sf::Color bottomDefaultColor = sf::Color(11, 86, 125),
                sf::Color topHoverColor = sf::Color(24, 110, 151),
                sf::Color bottomHoverColor = sf::Color(7, 50, 73),
                sf::Color shadowColor = sf::Color(94, 140, 164, 160),
                sf::Color outlineColor = sf::Color(14, 52, 74),
                float outlineThickness = 4.f
            );

        virtual ~ButtonWithText() {};

        /**
         * @brief Отрисовать кнопку с текстом на целевом объекте.
         * 
         * @param target Указатель на объект отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target) const override;

        /**
         * @brief Установить позицию кнопки с текстом.
         * 
         * @param x Координата x.
         * @param y Координата y.
         */
        virtual void SetPosition(float x, float y);

        /**
         * @brief Получить текст на кнопке.
         * 
         * @return Текст на кнопке.
         */
        sf::String GetTitle() const 
        { 
            return _text.getString();
        }
    };

    /**
     * @brief Класс ButtonWithIcon, унаследованный от Button.
     */
    class ButtonWithIcon : public Button
    {
    private:
        sf::Sprite _icon; ///< Иконка на кнопке
    public:

        /**
         * @brief Конструктор по умолчанию.
         */
        ButtonWithIcon() = default;

        /**
         * @brief Конструктор с параметрами.
         * 
         * @param rectangle          Прямоугольник типа sf::FloatRect.
         * @param radius             Радиус скругления углов.
         * @param icon               Иконка на кнопке.
         * @param function           Функция, связанная с нажатием кнопки.
         * @param topDefaultColor    Цвет верхней части кнопки по умолчанию.
         * @param bottomDefaultColor Цвет нижней части кнопки по умолчанию.
         * @param topHoverColor      Цвет верхней части кнопки при наведении.
         * @param bottomHoverColor   Цвет нижней части кнопки при наведении.
         * @param shadowColor        Цвет тени кнопки.
         * @param outlineColor       Цвет обводки.
         * @param outlineThickness   Толщина обводки.
         */
        ButtonWithIcon(const sf::FloatRect& rectangle, const float& radius, const sf::Sprite& icon, const std::function<void()>& function = [](){}, 
                sf::Color topDefaultColor = sf::Color(68, 164, 208), 
                sf::Color bottomDefaultColor = sf::Color(11, 86, 125),
                sf::Color topHoverColor = sf::Color(24, 110, 151),
                sf::Color bottomHoverColor = sf::Color(7, 50, 73),
                sf::Color shadowColor = sf::Color(94, 140, 164, 160),
                sf::Color outlineColor = sf::Color(14, 52, 74),
                float outlineThickness = 4.f
            );

        virtual ~ButtonWithIcon() {};

        /**
         * @brief Отрисовать кнопку с иконкой на целевом объекте.
         * 
         * @param target Указатель на объект отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target) const;

        /**
         * @brief Установить позицию кнопки с иконкой.
         * 
         * @param x Координата x.
         * @param y Координата y.
         */
        virtual void SetPosition(float x, float y);
    };
}

#endif