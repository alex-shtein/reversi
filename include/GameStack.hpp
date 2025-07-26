#ifndef GAME_STACK_HPP
#define GAME_STACK_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <vector>

namespace game
{
    class State;

    /**
     * @brief Класс GameStack, управляющий стеком игровых состояний.
     * 
     */
    class GameStack : private sf::NonCopyable
    {
    public:

        /**
         * @brief Перечисление для определения действий над стеком игровых состояний.
         * 
         */
        enum Action
        {
            Push,  ///< Добавить состояние в стек
            Pop,   ///< Удалить последнее состояние из стека
            Clear, ///< Очистить весь стек состояний
        };

        /**
         * @brief Структура для предстоящих изменений в стеке.
         * 
         */
        struct PendingChange
        {
            Action action; ///< Действие над стеком
            State* state;  ///< Указатель на состояние

            ~PendingChange() {}; ///< Деструктор
        };

    public:
        /**
         * @brief Конструктор класса GameStack.
         * 
         * @param renderTexture Указатель на RenderTexture.
         * @param window        Указатель на окно приложения.
         */
        explicit GameStack(sf::RenderTexture* renderTexture, sf::RenderWindow* window);

        ~GameStack();

        /**
         * @brief Обновить стек игровых состояний.
         * 
         * @param dt Время с последнего обновления.
         */
        void Update(float dt);

        /**
         * @brief Отрисовать стек игровых состояний.
         * 
         * @param target Цель отрисовки.
         */
        void Draw(sf::RenderTarget* target);

        /**
         * @brief Получить размер стека игровых состояний.
         * 
         * @return Размер стека.
         */
        int Size() { return _stackOfStates.size(); }

        /**
         * @brief Применить предстоящие изменения к стеку. 
         */
        void ApplyPendingChanges();

        /**
         * @brief Обработать событие.
         * 
         * @param event        Событие.
         * @param mousePositon Позиция указателя мыши.
         * 
         * @return true, если событие обработано, в противном случае - false.
         */
        bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon);

        /**
         * @brief Добавить состояние в стек.
         * 
         * @param state Указатель на состояние.
         */
        void PushState(State* state);

        /**
         * @brief Убрать последнее состояние из стека.
         */
        void PopState();

        /**
         * @brief Удалить все состояния из стека.
         */
        void ClearStates();

        /**
         * @brief Получить последнее состояние из стека.
         * 
         * @return Указатель на последнее состояние.
         */
        State* Back();

        /**
         * @brief Получить предпоследнее состояние из стека.
         * 
         * @return Указатель на предпоследнее состояние.
         */
        State* Penultimate();

        /**
         * @brief Проверить, пуст ли стек.
         * 
         * @return true, если стек пуст, в противном случае - false.
         */
        bool IsEmpty() const;

        /**
         * @brief Получить указатель на RenderTexture.
         * 
         * @return Указатель на RenderTexture.
         */
        sf::RenderTexture* GetRenderTexture();

        /**
         * @brief Получить указатель на окно приложения.
         * 
         * @return Указатель на окно.
         */
        sf::RenderWindow* GetWindow() { return _window; }

        /**
         * @brief Добавить предстоящее изменение в стек.
         * 
         * @param pendingChange Предстоящее изменение.
         */
        void AppendChange(PendingChange pendingChange);
    private:
        sf::RenderTexture* _renderTexture;       ///< Указатель на RenderTexture
        sf::RenderWindow* _window;               ///< Указатель на окно
        std::vector<State*> _stackOfStates;      ///< Стек игровых состояний
        std::vector<PendingChange> _pendingList; ///< Список предстоящих изменений
    };

    /**
     * @brief Базовый класс State, представляющий состояние в игровом стеке.
     */
    class State
    {
    public:

        /**
         * @brief Перечисление для определения направления перехода состояния.
         */
        enum class Direction
        {
            Appear = -1,  ///< Появление состояния
            Disappear = 1 ///< Исчезновение состояния
        };

        /**
         * @brief Конструктор состояния.
         * 
         * @param stack Указатель на игровой стек.
         */
        State(GameStack* stack)
            :_stack(stack) {}

        virtual ~State() {}

        /**
         * @brief Отрисовать состояние.
         * 
         * @param target Цель отрисовки.
         */
        virtual void Draw(sf::RenderTarget* target) = 0;

        /**
         * @brief Обновить состояние.
         * 
         * @param dt Время с последнего обновления.
         */
        virtual void Update(float dt) = 0;

        /**
         * @brief Обработать событие состояния.
         * 
         * @param event        Событие.
         * @param mousePositon Позиция указателя мыши.
         * 
         * @return true, если состояние обработало событие, в противном случае - false.
         */
        virtual bool HandleEvent(const sf::Event& event, const sf::Vector2f& mousePositon) = 0;

        /**
         * @brief Запросить добавление нового состояния в стек.
         */
        void RequestStackPush() { _stack->AppendChange({GameStack::Action::Push, this}); }

        /**
         * @brief Запросить удаление последнего состояния из стека.
         */
        void RequestStackPop() { _stack->AppendChange({GameStack::Action::Pop}); }

        /**
         * @brief Запросить удаление всех состояний из стека.
         */
        void RequestStateClear() { _stack->AppendChange({GameStack::Action::Clear}); }

        /**
         * @brief Получить RenderTexture из игрового стека.
         * 
         * @return Указатель на RenderTexture.
         */
        sf::RenderTexture* GetRenderTexture() { return _stack->GetRenderTexture(); }

        /**
         * @brief Получить окно из игрового стека.
         * 
         * @return Указатель на окно.
         */
        sf::RenderWindow* GetWindow() { return _stack->GetWindow(); }

        /**
         * @brief Получить указатель на игровой стек.
         * 
         * @return Указатель на игровой стек.
         */
        GameStack* GetGameStack() { return _stack; }
    private:
        GameStack* _stack; ///< Указатель на игровой стек
    };
}

#endif
