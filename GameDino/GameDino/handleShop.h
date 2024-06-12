#pragma once

void handleShop(sf::Event& event, sf::RenderWindow& window, sf::Font& font, sf::Text& balance,\
	sf::Text& earnedBalance, int& coinsUser, int& cntUserTyrannosaurus, int& cntUserStegosaurus, \
	int& cntUserTriceraptor)
{
	//�������� ������� � �������� ��������
	sf::Texture shopBackground, nameTyrannosaurusTexture, nameStegosaurusTexture, nameTriceraptorTexture, \
	TyrannosaurusTexture, StegosaurusTexture, TriceraptorTexture;
	shopBackground.loadFromFile("images/shop.png");
	nameTyrannosaurusTexture.loadFromFile("images/shop-nameTyrannosaurus.png");
	nameStegosaurusTexture.loadFromFile("images/shop-nameStegosaurus.png");
	nameTriceraptorTexture.loadFromFile("images/shop-nameTriceraptor.png");
	TyrannosaurusTexture.loadFromFile("images/shop-Tyrannosaurus-compressed.png");
	StegosaurusTexture.loadFromFile("images/shop-Stegosaurus-compressed.png");
	TriceraptorTexture.loadFromFile("images/shop-Triceraptor-compressed.png");
	sf::Sprite shopBg(shopBackground), nameTyrannosaurus(nameTyrannosaurusTexture), nameStegosaurus(nameStegosaurusTexture), nameTriceraptor(nameTriceraptorTexture), \
		Tyrannosaurus(TyrannosaurusTexture), Stegosaurus(StegosaurusTexture), Triceraptor(TriceraptorTexture);
	
	//������� ���������� ����������
	sf::Text cntUserTyrannosaurusText("", font, 70);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTyrannosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserStegosaurusText("", font, 70);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserStegosaurusText.setStyle(sf::Text::Bold);//������ �����
	sf::Text cntUserTriceraptorText("", font, 70);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������);//��� ������ ����� (�� ������)
	cntUserTriceraptorText.setStyle(sf::Text::Bold);//������ �����
	
	//������ ���������� ��������
	int pickNum = 0;
	bool mousePressed = false;
	nameTyrannosaurus.setPosition(600, 50);
	Tyrannosaurus.setPosition(750, 110);
	nameStegosaurus.setPosition(600, 300);
	Stegosaurus.setPosition(750, 360);
	nameTriceraptor.setPosition(600, 550);
	Triceraptor.setPosition(750, 610);
	cntUserTyrannosaurusText.setPosition(50, 200);
	cntUserStegosaurusText.setPosition(50, 300);
	cntUserTriceraptorText.setPosition(50, 400);

	while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		nameTyrannosaurus.setColor(sf::Color::White);
		nameStegosaurus.setColor(sf::Color::White);
		nameTriceraptor.setColor(sf::Color::White);
		window.clear();

		//��������� ������� �� ������ �������
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
		pickNum = 0;

		if (nameTyrannosaurus.getGlobalBounds().contains(worldPos)) {
			nameTyrannosaurus.setColor(sf::Color::Blue);
			pickNum = 1;
		}
		if (nameStegosaurus.getGlobalBounds().contains(worldPos)) {
			nameStegosaurus.setColor(sf::Color::Blue);
			pickNum = 2;
		}
		if (nameTriceraptor.getGlobalBounds().contains(worldPos)) {
			nameTriceraptor.setColor(sf::Color::Blue);
			pickNum = 3;
		}

		//������� �� ������ �������
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (pickNum == 1 && !mousePressed) {
				if (coinsUser >= 20) {
					nameTyrannosaurus.setColor(sf::Color::Green);
					cntUserTyrannosaurus++;
					coinsUser -= 20;
					mousePressed = true;
				}
				else { nameTyrannosaurus.setColor(sf::Color::Red); }
			}
			if (pickNum == 2 && !mousePressed) {
				if (coinsUser >= 15) {
					nameStegosaurus.setColor(sf::Color::Green);
					cntUserStegosaurus++;
					coinsUser -= 15;
					mousePressed = true;
				}
				else { nameStegosaurus.setColor(sf::Color::Red); }
			}
			if (pickNum == 3 && !mousePressed) {
				if (coinsUser >= 10) {
					nameTriceraptor.setColor(sf::Color::Green);
					cntUserTriceraptor++;
					coinsUser -= 10;
					mousePressed = true;
				}
				else { nameTriceraptor.setColor(sf::Color::Red); }
			}
		}
		else {
			mousePressed = false; // ���������� ����, ����� ������ ���� ��������
		}
		//���������� �������
		balance.setString("Balance: " + std::to_string(coinsUser));
		//���������� ���������� ����
		cntUserTyrannosaurusText.setString("Tyrannosaurus: " + std::to_string(cntUserTyrannosaurus));
		cntUserStegosaurusText.setString("Stegosaurus: " + std::to_string(cntUserStegosaurus));
		cntUserTriceraptorText.setString("Triceraptor: " + std::to_string(cntUserTriceraptor));

		window.draw(shopBg);
		window.draw(nameTyrannosaurus);
		window.draw(Tyrannosaurus);
		window.draw(nameStegosaurus);
		window.draw(Stegosaurus);
		window.draw(nameTriceraptor);
		window.draw(Triceraptor);
		window.draw(balance);
		window.draw(earnedBalance);

		// ����� ���������� ���� � ���������
		window.draw(cntUserTyrannosaurusText);
		window.draw(cntUserStegosaurusText);
		window.draw(cntUserTriceraptorText);
		window.display();

		
	}
}