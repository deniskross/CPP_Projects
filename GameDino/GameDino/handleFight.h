#pragma once

#include <random>

enum Terrain { Plain, River, Mountain };
Terrain getRandomTerrain() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 2);

	return static_cast<Terrain>(distrib(gen));
}

void handleFight(sf::Event& event, sf::RenderWindow& window, sf::Font& font,\
	sf::Texture& terrainTexture, sf::Texture& nameTerrain, \
	sf::Text& balance, sf::Text& earnedBalance, int& cntUserTyrannosaurus, \
	int& cntUserStegosaurus, \
	int& cntUserTriceraptor) {
	Terrain randomTerrain = getRandomTerrain();

	//Счетчик количества динозавров
	sf::Text cntUserTyrannosaurusText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserStegosaurusText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//жирный текст
	sf::Text cntUserTriceraptorText("", font, 70);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	cntUserTriceraptorText.setStyle(sf::Text::Bold);//жирный текст

	cntUserTyrannosaurusText.setPosition(50, 200);
	cntUserStegosaurusText.setPosition(50, 300);
	cntUserTriceraptorText.setPosition(50, 400);

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

		window.draw(terrainSprite);
		window.draw(nameTerrainSprite);
		window.draw(balance);
		window.draw(earnedBalance);

		//Обновление количества дино
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceraptorText.setString("Triceraptor: " + std::to_string(cntUserTriceraptor));

		// Вывод количества дино в инвентаре
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceraptorText);

		window.display();
	}
}