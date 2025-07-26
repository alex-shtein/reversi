#ifndef RUN_HPP
#define RUN_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../ResourceLoader.hpp"
#include "../Setup/GameSetup.hpp"
#include "../Setup/PlayerSetup.hpp"
#include "../Setup/BoardSetup.hpp"
#include "../Setup/ResultsSetup.hpp"
#include "../GameStack.hpp"
#include "./MainMenu.hpp"

namespace game
{

    /**
     * @brief Класс Run представляет основной игровой цикл и обрабатывает настройку игры, обновление, рендеринг и обработку событий.
     */
    class Run
    {
    public:

        /**
         * @brief settings представляет контекстные настройки для игрового окна.
         */
        sf::ContextSettings settings = sf::ContextSettings(0, 0, 4, 1, 1, 0, false);

    private:
        ResourceLoader _resourceLoader; ///< Экземпляр класса ResourceLoader для загрузки игровых ресурсов.
        Transition _transitionShader;   ///< Экземпляр класса Transition для обработки эффектов перехода.

        sf::RenderWindow* _window;         ///< Указатель на основное игровое окно.
        sf::RenderTexture* _renderTexture; ///< Указатель на текстуру для визуализации вне экрана.
        sf::Sprite _textureSprite;         ///< Спрайт для отображения текстуры.

        game::GameStack* _gameStack; ///< Указатель на стек игры для управления игровыми состояниями.

        GameSetup _gameSetup;       ///< Экземпляр класса GameSetup для настройки игры.
        PlayerSetup _playerSetup;   ///< Экземпляр класса PlayerSetup для настройки игроков.
        BoardSetup _boardSetup;     ///< Экземпляр класса BoardSetup для настройки игровой доски.
        ResultsSetup _resultsSetup; ///< Экземпляр класса ResultsSetup для настройки результатов игры.

        sf::VertexArray _background = sf::VertexArray(sf::PrimitiveType::TriangleFan); ///< Массив вершин для отрисовки фона.

        /**
         * @brief Инициализирует игру и ее компоненты.
         *        Создает текстуру рендеринга (_renderTexture), используемую для отображения содержимого игры.
         *        Загружает шейдер для реализации переходов между состояниями.
         *        Инициализирует основной игровой стек и добавляет в него главное меню.
         */
        void init();

        /**
         * @brief Обновляет логику игры на основе прошедшего времени.
         *        Обновляет состояние игрового стека и эффекты перехода между состояниями.
         * 
         * @param dt Прошедшее время с момента последнего обновления в секундах.
         */
        void Update(float dt);

        /**
         * @brief Обрабатывает события, такие как пользовательский ввод и события окна.
         */
        void ProcessEvents();

        /**
         * @brief Отрисовывает текущее состояние игры на экране.
         *        Очищает рендер-текстуру, отрисовывает задний фон, обновляет состояние игры и отображает его на рендер-текстуре.
         *        Затем отображает рендер-текстуру в основном окне с использованием шейдера переходов.
         */
        void Draw();
    public:

        /**
         * @brief Конструктор по умолчанию для класса Run.
         */
        Run();

        /**
         * @brief Деструктор для класса Run.
         */
        ~Run();
    };
}

#endif