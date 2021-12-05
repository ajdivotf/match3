#include "values.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include <iostream>

using namespace sf;

Vector2f pos;//���������� �������
Vector2i pixelPos;

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(350, 420), "three!");
	std::vector<Texture>textures(count);//�������� ��� �������
	std::string name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\characters_000";//����� ������ � ����������
	Sprite sprite;
	//����
	SoundBuffer matchBuffer[3];//������ ����� ��� �����
	std::string sound_name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\match";
	Sound match[3];
	for (int i = 0; i < 3; i++)
	{
		sound_name = sound_name + std::to_string(i + 1) + ".ogg";
		matchBuffer[i].loadFromFile(sound_name);//��������� � ���� ����
		match[i].setBuffer(matchBuffer[i]);
		match[i].setVolume(100);
		sound_name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\match";
	}
	Music music;//������� ������ ������
	music.openFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\music.ogg");//��������� ����
	//�����
	Font font;
	font.loadFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\Khand-ExtraBold.otf");
	//���� ������
	Text account("", font, 45);
	account.setString(std::to_string(score));
	account.setFillColor(Color::Black);
	account.setPosition(285, 350);
	//������ ������ �� ����
	Text enter("", font, 30);
	enter.setString("ENTER");
	enter.setFillColor(Color::Black);
	enter.setPosition(15, 370);
	//���������� ����������
	Text play("", font, 60);
	play.setString("PLAY");
	play.setFillColor(Color::White);
	play.setPosition(120, 180);
	Text best("", font, 30);
	std::string r_best = "BEST: ";
	best.setString("BEST: 0");
	best.setFillColor(Color::White);
	best.setPosition(130, 150);
	Text acc("", font, 60);
	acc.setFillColor(Color::White);
	acc.setPosition(155, 80);
	Texture black;
	black.loadFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\black.jpg");
	Sprite black_sp(black);
	black_sp.setColor(Color(0, 0, 0, 230));
	//��������� ��� �������
	Texture white;
	white.loadFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\white_1.png");
	Sprite white_sp(white);
	white_sp.setColor(Color(250, 250, 250, 180));
	white_sp.setPosition(150, 500);
	//���� ���� ������ ��������, ��
	if (mode)//���� ������ ����� ����
	{
		//��������� ��������
		for (int i = 0; i < count; i++)
		{
			name = name + std::to_string(i + 1) + ".png";
			textures[i].loadFromFile(name);
			name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\characters_000";
		}
		//��������� ����� 
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				grid[i][j].i = i;
				grid[i][j].j = j;
				grid[i][j].kind = rand() % count;
				grid[i][j].x = double(j * ts);
				grid[i][j].y = double(i * ts);
			}
		}
		//������� ��� ���������� �� ��������� �����
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (j != 8 and j != 9)
				{
					if (grid[i][j].kind == grid[i][j + 1].kind)
					{
						if (grid[i][j].kind == grid[i][j + 2].kind)
						{
							grid[i][j].kind = -1;
							grid[i][j + 1].kind = -1;
							grid[i][j + 1].kind = -1;
							if (j != 7)
								j += 3;
						}
					}
				}
			}
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (i != 8 and i != 9)
				{
					if (grid[i][j].kind == grid[i + 1][j].kind)
					{
						if (grid[i][j].kind == grid[i + 2][j].kind)
						{
							grid[i][j].kind = -1;
							grid[i + 1][j].kind = -1;
							grid[i + 2][j].kind = -1;
							if (i != 7)
								i += 3;
						}
					}
				}
			}
	}
	while (window.isOpen())//���� ��� �������
	{
		Event event;//������ ������ �������
		while (window.pollEvent(event))//���� ���������� �������
		{
			if (event.type == Event::Closed)//���� �������� �� �����, �� ���� �����������
				window.close();
			if (event.type == Event::MouseButtonPressed && move)//���� ������ ������� ���� � ������� ���� ��������
				if (event.key.code == Mouse::Left)
				{//� ������ �����
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (enter.getGlobalBounds().contains(mousePosF))//����� �� ����
					{
						mode = true;//�� � ������� ����
						move = false;//� ������ ������� �����
					}
					else
					{
						pixelPos = Mouse::getPosition(window);//�������� ����� �������
						pos = window.mapPixelToCoords(pixelPos);
						if (!swap) select++;
						sx = pos.y / ts;
						sy = pos.x / ts;
						//�������� ������ �����
						sprite.setPosition(grid[sx][sy].x, grid[sx][sy].y);
						sprite.setTexture(textures[grid[sx][sy].kind]);
						white_sp.setPosition(grid[sx][sy].x, grid[sx][sy].y);
					}
				}
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (play.getGlobalBounds().contains(mousePosF) and mode)
					{
						move = true;//����� ������� �����
						mode = false;//����� �� �������� ����
						score = 0;//�������� ���� ��� ��������� ����
					}
				}
		}
		if (select == 1)//���� ������ ������� �����, �� ��������� �� ����������
		{
			pr_x = pos.y / ts;
			pr_y = pos.x / ts;
		}
		else if (select == 2)
		{
			x = pos.y / ts;//������� ������ �����, ��������� ����������
			y = pos.x / ts;
			if (abs(x - pr_x) + abs(y - pr_y) == 1)//���� ����� ��������� ����� ������-�����-������-�����
			{
				//������ �� ��������
				kind_r = grid[pr_x][pr_y].kind;
				grid[pr_x][pr_y].kind = grid[x][y].kind;
				grid[x][y].kind = kind_r;
				//�������� �����, ��� ���������� �����, � ����������� �� ����, ���� ��������/������ ������
				if (y != 9 and y != 8)//� ������, ���
				{
					if (grid[x][y].kind == grid[x][y + 1].kind)
						if (grid[x][y].kind == grid[x][y + 2].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x][y + 1].kind = -1;
							grid[x][y + 2].kind = -1;
							mat = true;//��� ������������ ��������������� ����� �������� ������
						}
				}
				if (y != 0 and y != 9)//����������, ���
				{
					if (grid[x][y].kind == grid[x][y + 1].kind)
						if (grid[x][y].kind == grid[x][y - 1].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x][y + 1].kind = -1;
							grid[x][y - 1].kind = -1;
							mat = true;
						}
				}
				if (y != 0 and y != 1)//� �����, ���
				{
					if (grid[x][y].kind == grid[x][y - 1].kind)
						if (grid[x][y].kind == grid[x][y - 2].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x][y - 1].kind = -1;
							grid[x][y - 2].kind = -1;
							mat = true;
						}
				}
				if (x != 8 and x != 9)//� ������, �������
				{
					if (grid[x][y].kind == grid[x + 1][y].kind)
						if (grid[x][y].kind == grid[x + 2][y].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x + 1][y].kind = -1;
							grid[x + 2][y].kind = -1;
							mat = true;
						}
				}
				if (x != 0 and x != 9)//� ��������, �������
				{
					if (grid[x][y].kind == grid[x + 1][y].kind)
						if (grid[x][y].kind == grid[x - 1][y].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x + 1][y].kind = -1;
							grid[x - 1][y].kind = -1;
							mat = true;
						}
				}
				if (x != 1 and x != 9)//� �����, �������
				{
					if (grid[x][y].kind == grid[x - 1][y].kind)
						if (grid[x][y].kind == grid[x - 2][y].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x - 1][y].kind = -1;
							grid[x - 2][y].kind = -1;
							mat = true;
						}
				}
				//���� � ����� ��������� ����� ����������� ���
				if (pr_y != 9 and pr_y != 8)//� ������, ���
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y + 1].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y + 2].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x][pr_y + 1].kind = -1;
							grid[pr_x][pr_y + 2].kind = -1;
							mat = true;
						}
				}
				if (pr_y != 0 and pr_y != 9)//����������, ���
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y + 1].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y - 1].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x][pr_y + 1].kind = -1;
							grid[pr_x][pr_y - 1].kind = -1;
							mat = true;
						}
				}
				if (pr_y != 0 and pr_y != 1)//� �����, ���
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y - 1].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x][pr_y - 2].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x][pr_y - 1].kind = -1;
							grid[pr_x][pr_y - 2].kind = -1;
							mat = true;
						}
				}
				if (pr_x != 8 and pr_x != 9)//� ������, �������
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x + 1][pr_y].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x + 2][pr_y].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x + 1][pr_y].kind = -1;
							grid[pr_x + 2][pr_y].kind = -1;
							mat = true;
						}
				}
				if (pr_x != 0 and pr_x != 9)//� ��������, �������
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x + 1][pr_y].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x - 1][pr_y].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x + 1][pr_y].kind = -1;
							grid[pr_x - 1][pr_y].kind = -1;
							mat = true;
						}
				}
				if (pr_x != 1 and pr_x != 9)//� �����, �������
				{
					if (grid[pr_x][pr_y].kind == grid[pr_x - 1][pr_y].kind)
						if (grid[pr_x][pr_y].kind == grid[pr_x - 2][pr_y].kind)
						{
							score++;
							grid[pr_x][pr_y].kind = -1;
							grid[pr_x - 1][pr_y].kind = -1;
							grid[pr_x - 2][pr_y].kind = -1;
							mat = true;
						}
				}
				//���� ��� ��������� ��������� ����� �� ���, �� ���������� � 
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
					{
						if (j != 8 and j != 9)
						{
							if (grid[i][j].kind == grid[i][j + 1].kind)
							{
								if (grid[i][j].kind == grid[i][j + 2].kind)
								{
									if (grid[i][j].kind != -1)
									{
										score++;
										mat = true;
									}
									grid[i][j].kind = -1;
									grid[i][j + 1].kind = -1;
									grid[i][j + 1].kind = -1;
									if (j != 7)
										j += 3;
								}
							}
						}
					}
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
					{
						if (i != 8 and i != 9)
						{
							if (grid[i][j].kind == grid[i + 1][j].kind)
							{
								if (grid[i][j].kind == grid[i + 2][j].kind)
								{
									if (grid[i][j].kind != -1)
									{
										score++;
										mat = true;
									}
									grid[i][j].kind = -1;
									grid[i + 1][j].kind = -1;
									grid[i + 2][j].kind = -1;
									if (i != 7)
										i += 3;
								}
							}
						}
					}
				if (mat)//���� ���������� ����� �� ���, �� ������������� ����
				{
					match[rand() % 3].play();
					mat = false;
				}
				white_sp.setPosition(150, 500);
				swap = false;
				select = 0;
			}
			else select = 1;
		}
		window.clear(Color::White);
		{//��������, ���� ����� �������������� ��� �� ���. ���� �� ��������, ��������� ��� �� �������� ��-�� rand()
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
				{
					if (j != 8 and j != 9)
					{
						if (grid[i][j].kind == grid[i][j + 1].kind)
						{
							if (grid[i][j].kind == grid[i][j + 2].kind)
							{
								if (grid[i][j].kind != -1)
									grid[i][j].kind = -1;
								grid[i][j + 1].kind = -1;
								grid[i][j + 1].kind = -1;
								if (j != 7)
									j += 3;
							}
						}
					}
				}
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
				{
					if (i != 8 and i != 9)
					{
						if (grid[i][j].kind == grid[i + 1][j].kind)
						{
							if (grid[i][j].kind == grid[i + 2][j].kind)
							{
								if (grid[i][j].kind != -1)
									grid[i][j].kind = -1;
								grid[i + 1][j].kind = -1;
								grid[i + 2][j].kind = -1;
								if (i != 7)
									i += 3;
							}
						}
					}
				}
		}
		account.setString(std::to_string(score));//������������� ����
		window.draw(account);//� ������� ��� 
		window.draw(enter);//������ ������
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (grid[i][j].kind != -1)
				{//������ ������� �����, ���� �� ���� �� ������� ��-�� ����������
					sprite.setPosition(grid[i][j].x, grid[i][j].y);
					sprite.setTexture(textures[grid[i][j].kind]);
					window.draw(sprite);
				}
				else//������� �� �����, ������� ���������� ����� �� ���
					grid[i][j].kind = rand() % count;
			}
		if (music.getStatus() == Music::Stopped)//������������ ������
		{
			music.openFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\music.ogg");
			music.play();
		}
		window.draw(white_sp);//�������� ��� ��������� �����
		if (mode)//���� ���� ������ ��������
		{
			if (score > maximum)//������ ������ ��������
			{
				maximum = score;
				r_best = "BEST: ";
				r_best = r_best + std::to_string(maximum);
				best.setString(r_best);
			}
			acc.setString(std::to_string(score));
			window.draw(black_sp);//����������� ������
			window.draw(play);//������ "������ ����"
			window.draw(best);//������ ���������
			if (score != 0)
			{
				window.draw(acc);//�������� ���������
			}
		}
		window.display();
	}
	return 0;
}
