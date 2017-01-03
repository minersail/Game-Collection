#include "stdafx.h"
#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "Barrier.h"
#include "Decoration.h"
#include "NPC.h"
#include "Messenger.h"
#include "Building.h"
#include "Item.h"
#include "QuestGiver.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "The Unfortunate Adventure of Joe");
	_mainWindow.setFramerateLimit(60);

	_view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
	_view.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	_mainWindow.setView(_view);

	_editingBuilding = false;

	/////////////////////////////////////INITIALIZATION////////////////////////////////////////////////////////
	new Map(0, 0, "Tiles", "Map 0", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(50, 0, "Tiles", "Map 1", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(100, 0, "Tiles", "Map 2", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(0, 50, "Tiles", "Map 3", sf::Vector2i(16, 16), "maps/3.txt", 50, 50);
	new Map(50, 50, "Tiles", "Map 4", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(100, 50, "Tiles", "Map 5", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(0, 100, "Tiles", "Map 6", sf::Vector2i(16, 16), "maps/6.txt", 50, 50);
	new Map(50, 100, "Tiles", "Map 7", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);
	new Map(100, 100, "Tiles", "Map 8", sf::Vector2i(16, 16), "maps/blank.txt", 50, 50);

	//////////////////////////////////GAME BORDERS///////////////////////////////////////////
	new Barrier(0, 0, "Fence", "North Border", sf::Vector2i(149, 1));
	new Barrier(0, 149, "Fence", "South Border", sf::Vector2i(149, 1));
	new Barrier(149, 0, "Fence", "East Border", sf::Vector2i(1, 149));
	new Barrier(0, 0, "Fence", "West Border", sf::Vector2i(1, 149));
	/////////////////////////////////////////////////////////////////////////////////////////
	
							// TILE 3 //
	new Barrier(50, 50, "Fence", "Orchard Lake East Fence", sf::Vector2i(1, 100));

							// TILE 6 //
	new Barrier(37, 137, "Water", "lake 1", sf::Vector2i(5, 5), 3);
	new Barrier(37, 127, "Blue House", "some house", 1, sf::IntRect(0, 26, 80, 70));
	new Barrier(37, 115, "Blue House", "some house 3", 1, sf::IntRect(0, 26, 80, 70));
	new Barrier(1, 109, "Blue House", "some house 2", 1, sf::IntRect(0, 26, 80, 70));
	new Decoration(38, 137, "Grass Side", "grass 1", sf::Vector2i(3, 1));
	new Decoration(38, 141, "Grass Side", "grass 2", sf::Vector2i(3, 1), 180);
	new Decoration(37, 138, "Grass Side", "grass 3", sf::Vector2i(1, 3), 270);
	new Decoration(41, 138, "Grass Side", "grass 4", sf::Vector2i(1, 3), 90);
	new Decoration(37, 137, "Grass Corner 2", "grass 5");
	new Decoration(37, 142, "Grass Corner 2", "grass 6", 270);
	new Decoration(42, 142, "Grass Corner 2", "grass 7", 180);
	new Decoration(42, 137, "Grass Corner 2", "grass 8", 90);

	for (int i = 0; i < 9; i++)
	{
		Item* apple = new Item(15 + i, 133, "Apple", "Apple");
	}

	// House 1
	Building* JoeHouse = new Building(30, 136, "Blue House", "Joe's House", UseObject::UsePoint(32, 142, Entity::Up), UseObject::UsePoint(-25, 33, Entity::Down), sf::IntRect(0, 26, 80, 70));
	SwitchObjectManager(JoeHouse);
	new Map(-35, 15, "Building Tiles", "Bottom Floor", sf::Vector2i(16, 16), "maps/joehouse.txt", 20, 20);
	new Barrier(-35, 15, "Floor", "North Wall", sf::Vector2i(20, 1));
	new Barrier(-35, 34, "Floor", "South Wall", sf::Vector2i(20, 1));
	new Barrier(-16, 15, "Floor", "East Wall", sf::Vector2i(1, 20));
	new Barrier(-35, 15, "Floor", "West Wall", sf::Vector2i(1, 20));
	new Decoration(-35, 15, "Wall", "North Wall Decoration", sf::Vector2i(20, 1), 90);
	new Decoration(-35, 34, "Wall", "South Wall Decoration", sf::Vector2i(20, 1), 270);
	new Decoration(-16, 15, "Wall", "East Wall Decoration", sf::Vector2i(1, 20), 180);
	new Decoration(-35, 15, "Wall", "West Wall Decoration", sf::Vector2i(1, 20), 0);
	new Decoration(-15, 15, "Wall Corner", "Wall Corner 1", 90);
	new Decoration(-35, 35, "Wall Corner", "Wall Corner 2", 270);
	new Decoration(-15, 35, "Wall Corner", "Wall Corner 3", 180);
	new Decoration(-35, 15, "Wall Corner", "Wall Corner 4", 0);
	new Decoration(-24, 35, "Door", "Door", 180);
	new Messenger(-25, 30, "Old Man", "Old Fart", 2);
	JoeHouse->GetCollisionList() = _collisionManager.GetBuildingList();
	SwitchObjectManager();

	// House 2
	Building* LarryHouse = new Building(1, 133, "Blue House", "Larry's House", UseObject::UsePoint(3, 139, Entity::Up), UseObject::UsePoint(-25, 33, Entity::Down), sf::IntRect(0, 26, 80, 70));
	SwitchObjectManager(LarryHouse);
	new Map(-35, 15, "Building Tiles", "Bottom Floor", sf::Vector2i(16, 16), "maps/joehouse.txt", 20, 20);
	new Barrier(-35, 15, "Floor", "North Wall", sf::Vector2i(20, 1));
	new Barrier(-35, 34, "Floor", "South Wall", sf::Vector2i(20, 1));
	new Barrier(-16, 15, "Floor", "East Wall", sf::Vector2i(1, 20));
	new Barrier(-35, 15, "Floor", "West Wall", sf::Vector2i(1, 20));
	new Decoration(-35, 15, "Wall", "North Wall Decoration", sf::Vector2i(20, 1), 90);
	new Decoration(-35, 34, "Wall", "South Wall Decoration", sf::Vector2i(20, 1), 270);
	new Decoration(-16, 15, "Wall", "East Wall Decoration", sf::Vector2i(1, 20), 180);
	new Decoration(-35, 15, "Wall", "West Wall Decoration", sf::Vector2i(1, 20), 0);
	new Decoration(-15, 15, "Wall Corner", "Wall Corner 1", 90);
	new Decoration(-35, 35, "Wall Corner", "Wall Corner 2", 270);
	new Decoration(-15, 35, "Wall Corner", "Wall Corner 3", 180);
	new Decoration(-35, 15, "Wall Corner", "Wall Corner 4", 0);
	new Decoration(-24, 35, "Door", "Door", 180);
	LarryHouse->GetCollisionList() = _collisionManager.GetBuildingList();
	SwitchObjectManager();

	// House 3
	Building* DerbHouse = new Building(1, 119, "Blue House", "Derb's House", UseObject::UsePoint(3, 125, Entity::Up), UseObject::UsePoint(-25, 33, Entity::Down), sf::IntRect(0, 26, 80, 70));
	SwitchObjectManager(DerbHouse);
	new Map(-35, 15, "Building Tiles", "Bottom Floor", sf::Vector2i(16, 16), "maps/joehouse.txt", 20, 20);
	new Barrier(-35, 15, "Floor", "North Wall", sf::Vector2i(20, 1));
	new Barrier(-35, 34, "Floor", "South Wall", sf::Vector2i(20, 1));
	new Barrier(-16, 15, "Floor", "East Wall", sf::Vector2i(1, 20));
	new Barrier(-35, 15, "Floor", "West Wall", sf::Vector2i(1, 20));
	new Decoration(-35, 15, "Wall", "North Wall Decoration", sf::Vector2i(20, 1), 90);
	new Decoration(-35, 34, "Wall", "South Wall Decoration", sf::Vector2i(20, 1), 270);
	new Decoration(-16, 15, "Wall", "East Wall Decoration", sf::Vector2i(1, 20), 180);
	new Decoration(-35, 15, "Wall", "West Wall Decoration", sf::Vector2i(1, 20), 0);
	new Decoration(-15, 15, "Wall Corner", "Wall Corner 1", 90);
	new Decoration(-35, 35, "Wall Corner", "Wall Corner 2", 270);
	new Decoration(-15, 35, "Wall Corner", "Wall Corner 3", 180);
	new Decoration(-35, 15, "Wall Corner", "Wall Corner 4", 0);
	new Decoration(-24, 35, "Door", "Door", 180);
	DerbHouse->GetCollisionList() = _collisionManager.GetBuildingList();
	SwitchObjectManager();

	// ------------------------------------------Things drawn under Joe go above here------------------------------------------------
	new NPC(32, 120, "NPC 1", "Bob");
	new NPC(32, 120, "NPC 1", "Bobb");
	new NPC(32, 120, "NPC 1", "Bobbb");
	new NPC(32, 120, "NPC 1", "Bbob");
	new NPC(32, 120, "NPC 1", "Booob");
	new NPC(32, 120, "NPC 1", "Boooob");
	
	new Player(34, 142, "Joe", "Joe");

	new Messenger(3, 138, "NPC 2", "Steve", 1);
	new Messenger(25, 89, "Will", "Will", 3);

	new QuestGiver(14, 125, "Sister", "Sister", 4, 1);
	// ------------------------------------------Things drawn over Joe go below here-------------------------------------------------
	
							// TILE 3 //
	

							// TILE 6 //
	new Decoration(30, 136, "Blue House Roof", "Joe roof");
	new Decoration(1, 133, "Blue House Roof", "Larry roof");
	new Decoration(1, 119, "Blue House Roof", "Derb roof");
	new Decoration(37, 127, "Blue House Roof", "some roof");
	new Decoration(37, 115, "Blue House Roof", "some roof 3");
	new Decoration(1, 109, "Blue House Roof", "some roof 2");

	///////////////////////////////////////////////////////////////////////////////////////////
	_currentBuilding = NULL;
	LoadFonts();

	_gameState = Playing;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{
	case Playing:
	{
		_mainWindow.clear();

		_collisionManager.Update();

		_gameObjectManager.UpdateAll(currentEvent); // Most important lines of code:
		_gameObjectManager.DrawAll(_mainWindow);    // They update and draw all sprites

		_mainWindow.display();
		break;
	}
	case InBuilding: // Buildings require their own GameState because they have their own GameObjectManager and EntityLists
	{
		_mainWindow.clear();
		_collisionManager.CheckChunkCollisions(-1);

		_currentBuilding->GetFloorManager().UpdateAll(currentEvent);
		_currentBuilding->GetFloorManager().DrawAll(_mainWindow);
		_mainWindow.display();

		if (currentEvent.type == sf::Event::KeyPressed && currentEvent.key.code == sf::Keyboard::Space)
		{
			float pX = GetPlayer()->GetPosition().x; // Hitbox's origin
			float pY = GetPlayer()->GetPosition().y;
			UseObject::UsePoint EP = _currentBuilding->exitPoint;

			sf::RectangleShape unit;
			unit.setSize(sf::Vector2f(16, 16));
			unit.setPosition(EP.x * 16, EP.y * 16);

			// Debug for Door--KEEP
			/*unit.setFillColor(sf::Color::Red);
			Game::GetWindow().draw(unit);
			Game::GetWindow().display();*/

			if (unit.getGlobalBounds().contains(pX, pY))
			{
				sf::IntRect joeRect = GetPlayer()->GetTextureRect();
				if ((joeRect.left == joeRect.width * 0 && EP.dir == Entity::Up) || (joeRect.left == joeRect.width * 1 && EP.dir == Entity::Right)
					|| (joeRect.left == joeRect.width * 2 && EP.dir == Entity::Down) || (joeRect.left == joeRect.width * 3 && EP.dir == Entity::Left))
				{
					LockView(false);
					GetPlayer()->SetPosition(_currentBuilding->GetActivationLocations()[0].x * 16, _currentBuilding->GetActivationLocations()[0].y * 16);
					_currentBuilding = NULL;
					_gameState = Game::Playing;
					return;
				}
			}
		}
		break;
	}
	case Talking:
	{
		_mainWindow.clear();
		
		if (_currentBuilding != NULL) // Player is currently in a building
		{
			_currentBuilding->GetFloorManager().DrawAll(_mainWindow);
		}
		else
		{
			_gameObjectManager.DrawAll(_mainWindow);
		}

		_dialogueManager.Manage(currentEvent, _mainWindow);
		_mainWindow.display();
		break;
	}
	case Inventory:
	{
		_mainWindow.clear();

		if (_currentBuilding != NULL) // Player is currently in a building
		{
			_currentBuilding->GetFloorManager().DrawAll(_mainWindow);
		}
		else
		{
			_gameObjectManager.DrawAll(_mainWindow);
		}
		
		_inventoryManager.Manage(currentEvent, _mainWindow);
		_mainWindow.display();
		break;
	}
	case GameOver:
	{
		_gameObjectManager.DrawAll(_mainWindow);
		_mainWindow.display();
		break;
	}
	}

	if (currentEvent.type == sf::Event::Closed)
		_gameState = Exiting;
}

void Game::LoadFonts()
{
	regular.loadFromFile("fonts/regular.ttf");
}

sf::Font& Game::GetFont(std::string fontID)
{
	if (fontID == "Regular")
	{
		return regular;
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

GameObjectManager& Game::GetObjectManager()
{
	if (_editingBuilding)
	{
		return _currentBuilding->GetFloorManager();
	}
	else
	{
		return _gameObjectManager;
	}
}

void Game::SwitchObjectManager(Building* building)
{
	if (building != NULL)
	{
		_editingBuilding = true;
		_currentBuilding = building;
	}
	else
	{
		_collisionManager.GetBuildingList().clear();
		_editingBuilding = false;
	}
}

void Game::StartBuildingMode(Building* building)
{
	_currentBuilding = building;
	_collisionManager.SwitchBuildingList(building->GetCollisionList());
	_gameState = InBuilding;
}

ResourceManager& Game::GetResourceManager()
{
	return _resourceManager;
}

CollisionManager& Game::GetCollisionManager()
{
	return _collisionManager;
}

DialogueManager& Game::GetDialogueManager()
{
	return _dialogueManager;
}

InventoryManager& Game::GetInventoryManager()
{
	return _inventoryManager;
}

QuestManager& Game::GetQuestManager()
{
	return _questManager;
}

Player* Game::GetPlayer()
{
	return dynamic_cast<Player*>(_gameObjectManager.Get("Joe"));
}

sf::Vector2f Game::GetMousePos(bool absolute)
{
	if (absolute)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_mainWindow);
		sf::Vector2f adjustedPos = _mainWindow.mapPixelToCoords(mousePos);
		return adjustedPos;
	}
	else
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(_mainWindow);
		return static_cast<sf::Vector2f>(mousePos);
	}
}

sf::Vector2i Game::GTS(std::string textureID)
{
	return sf::Vector2i(_resourceManager.Get(textureID).getSize());
}

void Game::SetView(float newX, float newY)
{
	if (!_screenLocked)
	{
		_view.setCenter(newX, newY); // Adjusts the center of the view
		_mainWindow.setView(_view); // Applies view
	}
}

void Game::LockView(bool lock)
{
	_screenLocked = lock;
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
ResourceManager Game::_resourceManager;
CollisionManager Game::_collisionManager;
DialogueManager Game::_dialogueManager;
InventoryManager Game::_inventoryManager;
QuestManager Game::_questManager;
sf::Font Game::regular;
sf::View Game::_view;

bool Game::_editingBuilding;
bool Game::_screenLocked;
Building* Game::_currentBuilding;