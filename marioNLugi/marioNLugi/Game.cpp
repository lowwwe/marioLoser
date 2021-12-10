/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_ImMario{true},
	m_exitGame{false} //when true game will exit
{
	m_ImMario = true;
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		changeCharacter();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	getDirection();
	move();
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	
	m_window.draw(m_logoSprite);
	m_window.draw(m_characterName);
	m_window.draw(m_characterSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_marioFont.loadFromFile("ASSETS\\FONTS\\SuperMario256.ttf"))
	{
		std::cout << "problem with mario font" << std::endl;
	}
	
	m_characterName.setFont(m_marioFont);
	m_characterName.setString("Mario");
	m_characterName.setCharacterSize(40U);
	m_characterName.setPosition(sf::Vector2f{ 350.0f,100.0f });
	m_characterName.setFillColor(sf::Color::Red);
	m_characterName.setOutlineColor(sf::Color::Black);
	m_characterName.setOutlineThickness(2.0f);
	


}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_marioNluigiTex.loadFromFile("ASSETS\\IMAGES\\mario-luigi-64.png"))
	{
		std::cout << "problem with mario texture" << std::endl;
	}
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_characterSprite.setTexture(m_marioNluigiTex);
	m_characterSprite.setPosition(m_location);
	m_characterSprite.setTextureRect(sf::IntRect(0, 0, 64, 148));
	m_characterSprite.setOrigin(sf::Vector2f{ 32.0f,74.0f });

}

void Game::changeCharacter()
{
	if (m_ImMario)
	{
		m_characterSprite.setTextureRect(sf::IntRect(64, 0, 64, 148));
		m_characterName.setString("Luigi");
		m_characterName.setFillColor(sf::Color::Green);
	}
	else
	{
		m_characterSprite.setTextureRect(sf::IntRect(0, 0, 64, 148));
		m_characterName.setString("Mario");
		m_characterName.setFillColor(sf::Color::Red);
	}
	m_ImMario = !m_ImMario;
}

void Game::getDirection()
{
	m_direction = Direction::None;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_direction = Direction::Up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_direction = Direction::Down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_direction = Direction::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_direction = Direction::Right;
	}

}

void Game::move()
{
	sf::Vector2f move{ 0.0f,0.0f };
	switch (m_direction)
	{
	case Direction::None:
		break;
	case Direction::Up:
		move.y = -m_speed;
		break;
	case Direction::Down:
		move.y = m_speed;
		break;
	case Direction::Left:
		move.x = -m_speed;
		break;
	case Direction::Right:
		move.x = m_speed;
		break;
	default:
		break;
	}
	m_location += move;
	m_characterSprite.setPosition(m_location);
}
