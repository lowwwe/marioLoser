/// <summary>;
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();
	void changeCharacter();



	sf::RenderWindow m_window; // main SFML window
	sf::Font m_marioFont; // mario font 
	sf::Text m_characterName; // name of mario or luigi on scrteen
	
	sf::Texture m_marioNluigiTex; // texture for png opf the boys
	sf::Sprite m_characterSprite; // sprite fopr msrio or luigi

	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	bool m_ImMario{ true }; // is the current character mario
};

#endif // !GAME_HPP

