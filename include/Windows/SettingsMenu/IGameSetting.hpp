#ifndef I_GAME_SETTING_HPP
#define I_GAME_SETTING_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../Particulars.hpp"

namespace game
{
    /**
     * @brief Интерфейс IGameSetting для представления настроек в игре
     */
    class IGameSetting
    {
    protected:
        sf::RenderTexture* _renderTexture; ///< Указатель на RenderTexture
        game::Text _settingName;           ///< Название настройки
    public:
        /**
         * @brief Конструктор интерфейса IGameSetting
         * 
         * @param renderTexture Указатель на RenderTexture
         * @param settingName   Название настройки
         */
        IGameSetting(sf::RenderTexture* renderTexture,  const game::Text& settingName)
            : _renderTexture(renderTexture), _settingName(settingName) {}

        virtual ~IGameSetting() {} ///< Виртуальный деструктор

        /**
         * @brief Отрисовать настройку
         * 
         * @param target Цель отрисовки
         */
        virtual void Draw(sf::RenderTarget* target) = 0;

        /**
         * @brief Установить позицию по OY
         * 
         * @param OYOffset Смещение по OY
         */
        virtual void SetPositionOnOY(float OYOffset) = 0;

        /**
         * @brief Обновить состояние настройки
         * 
         * @param mousePos Позиция мыши
         * @param event    Событие
         */
        virtual void Update(const sf::Vector2f& mousePos, const sf::Event& event) = 0;

        /**
         * @brief Получить высоту настройки
         * 
         * @return Высота настройки
         */
        virtual float GetHeight() const = 0;
    };
}

#endif