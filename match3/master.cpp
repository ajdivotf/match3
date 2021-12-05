#include "values.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <vector>
#include <iostream>

using namespace sf;

Vector2f pos;//координаты курсора
Vector2i pixelPos;

int main()
{
	srand(time(0));
	RenderWindow window(VideoMode(350, 420), "three!");
	std::vector<Texture>textures(count);//текстуры для фигурок
	std::string name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\characters_000";//имена файлов с текстурами
	Sprite sprite;
	//звук
	SoundBuffer matchBuffer[3];//создаём буфер для звука
	std::string sound_name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\match";
	Sound match[3];
	for (int i = 0; i < 3; i++)
	{
		sound_name = sound_name + std::to_string(i + 1) + ".ogg";
		matchBuffer[i].loadFromFile(sound_name);//загружаем в него звук
		match[i].setBuffer(matchBuffer[i]);
		match[i].setVolume(100);
		sound_name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\match";
	}
	Music music;//создаем объект музыки
	music.openFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\music.ogg");//загружаем файл
	//шрифт
	Font font;
	font.loadFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\Khand-ExtraBold.otf");
	//счёт игрока
	Text account("", font, 45);
	account.setString(std::to_string(score));
	account.setFillColor(Color::Black);
	account.setPosition(285, 350);
	//кнопка выхода из игры
	Text enter("", font, 30);
	enter.setString("ENTER");
	enter.setFillColor(Color::Black);
	enter.setPosition(15, 370);
	//оформление интерфейса
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
	//подсветка при нажатии
	Texture white;
	white.loadFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\white_1.png");
	Sprite white_sp(white);
	white_sp.setColor(Color(250, 250, 250, 180));
	white_sp.setPosition(150, 500);
	//если игра только началась, то
	if (mode)//если начали новую игру
	{
		//отгружаем текстуры
		for (int i = 0; i < count; i++)
		{
			name = name + std::to_string(i + 1) + ".png";
			textures[i].loadFromFile(name);
			name = "C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\image\\characters_000";
		}
		//заполняем сетку 
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
		//удаляем три одинаковых до генерации сетки
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
	while (window.isOpen())//пока оно открыто
	{
		Event event;//объект класса событий
		while (window.pollEvent(event))//пока происходят события
		{
			if (event.type == Event::Closed)//если нажимаем на крест, то окно закрывается
				window.close();
			if (event.type == Event::MouseButtonPressed && move)//если нажата клавиша мыши и игровое поле включено
				if (event.key.code == Mouse::Left)
				{//а именно левая
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
					if (enter.getGlobalBounds().contains(mousePosF))//выход из игры
					{
						mode = true;//мы в главном меню
						move = false;//и нельзя двигать фишки
					}
					else
					{
						pixelPos = Mouse::getPosition(window);//забираем коорд курсора
						pos = window.mapPixelToCoords(pixelPos);
						if (!swap) select++;
						sx = pos.y / ts;
						sy = pos.x / ts;
						//выделяем спрайт белым
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
						move = true;//можно двигать фишки
						mode = false;//вышли из главного меню
						score = 0;//обнулили счёт для следующей игры
					}
				}
		}
		if (select == 1)//если просто выбрали фишку, то сохраняем ее координаты
		{
			pr_x = pos.y / ts;
			pr_y = pos.x / ts;
		}
		else if (select == 2)
		{
			x = pos.y / ts;//выбрали вторую фишку, сохраняем координаты
			y = pos.x / ts;
			if (abs(x - pr_x) + abs(y - pr_y) == 1)//если фишки находятся рядом сверху-слева-справа-внизу
			{
				//меняем их текстуры
				kind_r = grid[pr_x][pr_y].kind;
				grid[pr_x][pr_y].kind = grid[x][y].kind;
				grid[x][y].kind = kind_r;
				//проверка линий, где поменялись фишки, в зависимости от того, куда добавили/откуда убрали
				if (y != 9 and y != 8)//в начале, ряд
				{
					if (grid[x][y].kind == grid[x][y + 1].kind)
						if (grid[x][y].kind == grid[x][y + 2].kind)
						{
							score++;
							grid[x][y].kind = -1;
							grid[x][y + 1].kind = -1;
							grid[x][y + 2].kind = -1;
							mat = true;//для последующего воспроизведения звука удаления тройки
						}
				}
				if (y != 0 and y != 9)//посередине, ряд
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
				if (y != 0 and y != 1)//в конце, ряд
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
				if (x != 8 and x != 9)//в начале, столбец
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
				if (x != 0 and x != 9)//в середине, столбец
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
				if (x != 1 and x != 9)//в конце, столбец
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
				//если у обоих сдвинутых фишек закрывается ряд
				if (pr_y != 9 and pr_y != 8)//в начале, ряд
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
				if (pr_y != 0 and pr_y != 9)//посередине, ряд
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
				if (pr_y != 0 and pr_y != 1)//в конце, ряд
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
				if (pr_x != 8 and pr_x != 9)//в начале, столбец
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
				if (pr_x != 0 and pr_x != 9)//в середине, столбец
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
				if (pr_x != 1 and pr_x != 9)//в конце, столбец
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
				//если при генерации появилась линия из трёх, то уничтожаем её 
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
				if (mat)//если уничтожили линию из трёх, то воспроизводим звук
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
		{//проверка, если вдруг сгенерировался ряд из трёх. счёт не меняется, поскольку это мб случайно из-за rand()
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
		account.setString(std::to_string(score));//пересчитываем счёт
		window.draw(account);//и выводим его 
		window.draw(enter);//кнопка выхода
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				if (grid[i][j].kind != -1)
				{//просто выводим фишки, если не надо их удалять из-за совпадения
					sprite.setPosition(grid[i][j].x, grid[i][j].y);
					sprite.setTexture(textures[grid[i][j].kind]);
					window.draw(sprite);
				}
				else//удаляем те фишки, которые образовали линию из трёх
					grid[i][j].kind = rand() % count;
			}
		if (music.getStatus() == Music::Stopped)//зацикливание музыки
		{
			music.openFromFile("C:\\Users\\wellcat\\source\\repos\\match3\\Debug\\sounds\\music.ogg");
			music.play();
		}
		window.draw(white_sp);//текстура для выделения фишек
		if (mode)//если игра только началась
		{
			if (score > maximum)//меняем лучший резульат
			{
				maximum = score;
				r_best = "BEST: ";
				r_best = r_best + std::to_string(maximum);
				best.setString(r_best);
			}
			acc.setString(std::to_string(score));
			window.draw(black_sp);//затеменение экрана
			window.draw(play);//кнопка "начать игру"
			window.draw(best);//лучший результат
			if (score != 0)
			{
				window.draw(acc);//нынешний результат
			}
		}
		window.display();
	}
	return 0;
}
