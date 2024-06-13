#pragma once

#include <random>

enum Terrain { Plain, River, Mountain };
Terrain getRandomTerrain() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 2);

	return static_cast<Terrain>(distrib(gen));
}

void loadingTexture(int& cntSelected, int& pickNum, sf::Texture& selectedDino1Texture, \
	sf::Texture& selectedDino2Texture, sf::Texture& selectedDino3Texture) {
	if (cntSelected == 0) {
		if (pickNum == 1) {
			selectedDino1Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino1Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino1Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
	if (cntSelected == 1) {
		if (pickNum == 1) {
			selectedDino2Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino2Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino2Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
	if (cntSelected == 2) {
		if (pickNum == 1) {
			selectedDino3Texture.loadFromFile("images/TyrannosaurusFightUser.png");
		}
		else if (pickNum == 2) {
			selectedDino3Texture.loadFromFile("images/StegosaurusFightUser.png");
		}
		else if (pickNum == 3) {
			selectedDino3Texture.loadFromFile("images/TriceratopsFightUser.png");
		}
	}
}

void actionFight(sf::Event& event, sf::RenderWindow& window, sf::Sprite& terrainSprite, \
	sf::Sprite& nameTerrainSprite, sf::Text& balance, sf::Text& earnedBalance, \
	sf::Sprite& selectedDino1, sf::Sprite& selectedDino2, sf::Sprite& selectedDino3) {
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//Отрисовка карты и баланса
		window.clear();
		window.draw(terrainSprite);
		window.draw(nameTerrainSprite);
		window.draw(balance);
		window.draw(earnedBalance);

		//Отрисовка динозавров
		selectedDino1.setPosition(200, 50);
		selectedDino2.setPosition(200, 250);
		selectedDino3.setPosition(200, 450);
		window.draw(selectedDino1);
		window.draw(selectedDino2);
		window.draw(selectedDino3);

		window.display();
	}
}

void handleFight(sf::Event& event, sf::RenderWindow& window, sf::Font& font,\
	sf::Texture& terrainTexture, sf::Texture& nameTerrain, \
	sf::Text& balance, sf::Text& earnedBalance, int& cntUserTyrannosaurus, \
	int& cntUserStegosaurus, int& cntUserTriceratops) {
	Terrain randomTerrain = getRandomTerrain();
	int pickNum = 0, cntSelected = 0;
	bool mousePressed = false;

	sf::Texture selectedDino1Texture, selectedDino2Texture, selectedDino3Texture;

	//Список текстур
	sf::Texture listTextures[3]{ selectedDino1Texture, selectedDino2Texture, selectedDino3Texture };
	
	// Создание кнопок для выбора дино
	sf::RectangleShape select1(sf::Vector2f(50, 50));
	select1.setFillColor(sf::Color::White);
	select1.setPosition(400, 210);
	sf::RectangleShape select2(sf::Vector2f(50, 50));
	select2.setFillColor(sf::Color::White);
	select2.setPosition(400, 310);
	sf::RectangleShape select3(sf::Vector2f(50, 50));
	select3.setFillColor(sf::Color::White);
	select3.setPosition(400, 410);
	sf::RectangleShape buttonFight(sf::Vector2f(150, 60));
	buttonFight.setFillColor(sf::Color::White);
	buttonFight.setPosition(1050, 740);

	//Счетчик количества динозавров
	sf::Text cntUserTyrannosaurusText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserStegosaurusText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserTriceratopsText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTriceratopsText.setStyle(sf::Text::Bold);//жирный текст
	//Подпись пула игрока
	sf::Text userPull("YOUR PULL", font, 80);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	userPull.setFillColor(sf::Color::Green);
	userPull.setStyle(sf::Text::Bold);//жирный текст
	sf::Text buttonFightText("Fight!", font, 60);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	buttonFightText.setFillColor(sf::Color::Black);
	buttonFightText.setStyle(sf::Text::Bold);

	cntUserTyrannosaurusText.setPosition(20, 200);
	cntUserStegosaurusText.setPosition(20, 300);
	cntUserTriceratopsText.setPosition(20, 400);
	userPull.setPosition(800, 20);
	buttonFightText.setPosition(1070, 730);

	//Создание пустого списка пула игрока из объектов классов


	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		//Выбор рандомной местности
		switch (randomTerrain) {
		case Terrain::Plain:
			terrainTexture.loadFromFile("images/plane.png");
			nameTerrain.loadFromFile("images/name-plain.png");
			break;
		case Terrain::River:
			terrainTexture.loadFromFile("images/river.png");
			nameTerrain.loadFromFile("images/name-river.png");
			break;
		case Terrain::Mountain:
			terrainTexture.loadFromFile("images/mountain.png");
			nameTerrain.loadFromFile("images/name-mountain.png");
		}
		//Отрисовка местности
		sf::Sprite terrainSprite(terrainTexture), nameTerrainSprite(nameTerrain);
		nameTerrainSprite.setPosition(550, 10);
		nameTerrainSprite.setColor(sf::Color::White);

		//Сброс цвета кнопок
		select1.setFillColor(sf::Color::White);
		select2.setFillColor(sf::Color::White);
		select3.setFillColor(sf::Color::White);
		buttonFight.setFillColor(sf::Color::White);

		window.clear();
		window.draw(terrainSprite);
		window.draw(nameTerrainSprite);
		window.draw(balance);
		window.draw(earnedBalance);

		//Наведение курсора на кнопку выбора
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		pickNum = 0;
		if (select1.getGlobalBounds().contains(worldPos)) {
			pickNum = 1;
		}
		if (select2.getGlobalBounds().contains(worldPos)) {
			pickNum = 2;
		}
		if (select3.getGlobalBounds().contains(worldPos)) {
			pickNum = 3;
		}
		if (buttonFight.getGlobalBounds().contains(worldPos)) {
			buttonFight.setFillColor(sf::Color::Blue);
			pickNum = 4;
		}

		//Нажатие на кнопку выбора
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			
			if (pickNum == 1 && !mousePressed) {
				if (cntUserTyrannosaurus > 0 && cntSelected < 3) {
					select1.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					//listTextures[cntSelected].loadFromFile("images/shop-Tyrannosaurus-compressed.png");
					cntUserTyrannosaurus--;
					cntSelected++;
					mousePressed = true;
				}
				else { select1.setFillColor(sf::Color::Red); }
			}
			if (pickNum == 2 && !mousePressed) {
				if (cntUserStegosaurus > 0 && cntSelected < 3) {
					select2.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					//listTextures[cntSelected].loadFromFile("images/shop-Stegosaurus-compressed.png");
					cntUserStegosaurus--;
					cntSelected++;
					mousePressed = true;
				}
				else { select2.setFillColor(sf::Color::Red); }
			}
			if (pickNum == 3 && !mousePressed) {
				if (cntUserTriceratops > 0 && cntSelected < 3) {
					select3.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					//listTextures[cntSelected].loadFromFile("images/shop-Triceraptor-compressed.png");
					cntUserTriceratops--;
					cntSelected++;
					mousePressed = true;
				}
				else { select3.setFillColor(sf::Color::Red); }
			}
			
		}
		else {
			mousePressed = false; // Сбрасываем флаг, когда кнопка мыши отпущена
			//cntSelected++;
		}
		//Обновление количества дино
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceratopsText.setString("Triceratops: " + std::to_string(cntUserTriceratops));
		//Создание спрайтов для картинок выбранных дино
		sf::Sprite selectedDino1(selectedDino1Texture), selectedDino2(selectedDino2Texture), selectedDino3(selectedDino3Texture);
		selectedDino1.setPosition(800, 100);
		selectedDino2.setPosition(800, 300);
		selectedDino3.setPosition(800, 500);
		// Вывод количества дино в инвентаре
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceratopsText);
		window.draw(userPull);
		window.draw(select1);
		window.draw(select2);
		window.draw(select3);
		window.draw(buttonFight);
		window.draw(buttonFightText);
		window.draw(selectedDino1);
		window.draw(selectedDino2);
		window.draw(selectedDino3);

		window.display();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (pickNum == 4) { actionFight(event, window, terrainSprite, \
			nameTerrainSprite, balance, earnedBalance, selectedDino1, \
				selectedDino2, selectedDino3); while (window.isOpen()); }
		}
	}
}