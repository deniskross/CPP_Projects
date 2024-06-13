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
			selectedDino1Texture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
		}
		else if (pickNum == 2) {
			selectedDino1Texture.loadFromFile("images/shop-Stegosaurus-compressed.png");
		}
		else if (pickNum == 3) {
			selectedDino1Texture.loadFromFile("images/shop-Triceraptor-compressed.png");
		}
	}
	if (cntSelected == 1) {
		if (pickNum == 1) {
			selectedDino2Texture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
		}
		else if (pickNum == 2) {
			selectedDino2Texture.loadFromFile("images/shop-Stegosaurus-compressed.png");
		}
		else if (pickNum == 3) {
			selectedDino2Texture.loadFromFile("images/shop-Triceraptor-compressed.png");
		}
	}
	if (cntSelected == 2) {
		if (pickNum == 1) {
			selectedDino3Texture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
		}
		else if (pickNum == 2) {
			selectedDino3Texture.loadFromFile("images/shop-Stegosaurus-compressed.png");
		}
		else if (pickNum == 3) {
			selectedDino3Texture.loadFromFile("images/shop-Triceraptor-compressed.png");
		}
	}
}

void handleFight(sf::Event& event, sf::RenderWindow& window, sf::Font& font,\
	sf::Texture& terrainTexture, sf::Texture& nameTerrain, \
	sf::Text& balance, sf::Text& earnedBalance, int& cntUserTyrannosaurus, \
	int& cntUserStegosaurus, int& cntUserTriceraptor) {
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

	//Счетчик количества динозавров
	sf::Text cntUserTyrannosaurusText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserStegosaurusText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserTriceraptorText("", font, 50);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTriceraptorText.setStyle(sf::Text::Bold);//жирный текст
	//Подпись пула игрока
	sf::Text userPull("YOUR PULL", font, 80);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	userPull.setFillColor(sf::Color::Green);
	userPull.setStyle(sf::Text::Bold);//жирный текст

	cntUserTyrannosaurusText.setPosition(20, 200);
	cntUserStegosaurusText.setPosition(20, 300);
	cntUserTriceraptorText.setPosition(20, 400);
	userPull.setPosition(750, 50);

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
				if (cntUserTriceraptor > 0 && cntSelected < 3) {
					select3.setFillColor(sf::Color::Green);
					loadingTexture(cntSelected, pickNum, selectedDino1Texture, selectedDino2Texture, selectedDino3Texture);
					//listTextures[cntSelected].loadFromFile("images/shop-Triceraptor-compressed.png");
					cntUserTriceraptor--;
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
		cntUserTriceraptorText.setString("Triceraptor: " + std::to_string(cntUserTriceraptor));
		//Создание спрайтов для картинок выбранных дино
		sf::Sprite selectedDino1(selectedDino1Texture), selectedDino2(selectedDino2Texture), selectedDino3(selectedDino3Texture);
		selectedDino1.setPosition(800, 150);
		selectedDino2.setPosition(800, 350);
		selectedDino3.setPosition(800, 550);
		// Вывод количества дино в инвентаре
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceraptorText);
		window.draw(userPull);
		window.draw(select1);
		window.draw(select2);
		window.draw(select3);
		window.draw(selectedDino1);
		window.draw(selectedDino2);
		window.draw(selectedDino3);

		window.display();
	}
}