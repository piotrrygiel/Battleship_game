#include <SFML/Graphics.hpp>
#include "Ships.h"
#include "Losowanie.h"
#include <iostream>
#include <time.h>

using namespace sf;

int game = 2;
int clickx = 0, clicky = 0;

//Do strzelania w przeciwnika:
int AircraftCarrierAI = 5;
int BattleshipAI = 4;
int SubmarineAI = 3;
int CruiserAI = 3;
int DestroyerAI = 2;
int zatopione_okrety = 0;

Time czas(milliseconds(2000));

//Do ustawiania statkow na mapie przeciwnika:
int orientacja; //1 - poziomo, 2 - pionowo
int wiersz; //losowy wiersz od 0 do 9
int kolumna; //losowa kolumna od 0 do 9
int x = 1;
int gridAI[14][14] =
{
9,9,9,9,9,9,9,9,9,9,9,9,9,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};

int grid[14][14] =
{
9,9,9,9,9,9,9,9,9,9,9,9,9,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,0,0,0,0,0,0,0,0,0,0,0,0,9,
9,9,9,9,9,9,9,9,9,9,9,9,9,9,
};

int main() {

	RenderWindow appWindow(VideoMode(648, 648), "Battleships");
	Event appEvent;

	appWindow.setFramerateLimit(144);

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;

	t1.loadFromFile("board1.jpg");
	t2.loadFromFile("DestroyerH.png");
	t3.loadFromFile("CruiserH.png");
	t4.loadFromFile("BattleshipH.png");
	t5.loadFromFile("AircraftCarrierH.png");
	t6.loadFromFile("menuPoziomo.png");
	t7.loadFromFile("DestroyerV.png");
	t8.loadFromFile("CruiserV.png");
	t9.loadFromFile("BattleshipV.png");
	t10.loadFromFile("AircraftCarrierV.png");
	t11.loadFromFile("pudlo.png");
	t12.loadFromFile("SubmarineH.png");
	t13.loadFromFile("SubmarineV.png");
	t14.loadFromFile("start.png");
	t15.loadFromFile("trafienie.png");
	t16.loadFromFile("menuPionowo.png");

	Sprite sPlanszaGracza(t1), sDestroyerH(t2), sCruiserH(t3), sSubmarineH(t12), sBattleshipH(t4), sAircraftCarrierH(t5), sMenu(t6), sMenu2(t16), sDestroyerV(t7), sCruiserV(t8), sSubmarineV(t13), sBattleshipV(t9), sAircraftCarrierV(t10), sPudlo(t11), sPlanszaAI(t1), sStartButton(t14), sTrafienie(t15);

	srand(time(NULL));

	orientacja = rand() % 2 + 1;

	//Aircraft Carrier:
	if (orientacja == 1) {
		//losujemy pozycje startowa statku
		wiersz = rand() % 10 + 2;
		kolumna = rand() % 6 + 2;
		//ustawiamy statek (pole za polem do prawej)
		gridAI[wiersz][kolumna] = 5;
		gridAI[wiersz][kolumna + 1] = 5;
		gridAI[wiersz][kolumna + 2] = 5;
		gridAI[wiersz][kolumna + 3] = 5;
		gridAI[wiersz][kolumna + 4] = 5;
	}
	else {
		//losujemy pozycje startowa statku
		kolumna = rand() % 10 + 2;
		wiersz = rand() % 6 + 2;
		//ustawiamy statek (pole za polem w dó³)
		gridAI[wiersz][kolumna] = 5;
		gridAI[wiersz + 1][kolumna] = 5;
		gridAI[wiersz + 2][kolumna] = 5;
		gridAI[wiersz + 3][kolumna] = 5;
		gridAI[wiersz + 4][kolumna] = 5;
	}

	orientacja = rand() % 2 + 1;

	//Battleship:
	if (orientacja == 1) {
		//losujemy pozycje startowa statku
		while (1) {
			wiersz = rand() % 10 + 2;
			kolumna = rand() % 7 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 2] == 0 && gridAI[wiersz][kolumna + 3] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz - 1][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna + 3] == 0 && gridAI[wiersz - 1][kolumna + 4] == 0 && gridAI[wiersz][kolumna + 4] == 0 && gridAI[wiersz + 1][kolumna + 4] == 0 && gridAI[wiersz + 1][kolumna + 3] == 0 && gridAI[wiersz + 1][kolumna + 2] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem do prawej)
		gridAI[wiersz][kolumna] = 4;
		gridAI[wiersz][kolumna + 1] = 4;
		gridAI[wiersz][kolumna + 2] = 4;
		gridAI[wiersz][kolumna + 3] = 4;
	}
	else {
		//losujemy pozycje startowa statku
		while (1) {
			kolumna = rand() % 10 + 2;
			wiersz = rand() % 7 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 2][kolumna] == 0 && gridAI[wiersz + 3][kolumna] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 2][kolumna + 1] == 0 && gridAI[wiersz + 3][kolumna + 1] == 0 && gridAI[wiersz + 4][kolumna + 1] == 0 && gridAI[wiersz + 4][kolumna] == 0 && gridAI[wiersz + 4][kolumna - 1] == 0 && gridAI[wiersz + 3][kolumna - 1] == 0 && gridAI[wiersz + 2][kolumna - 1] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem w dó³)
		gridAI[wiersz][kolumna] = 4;
		gridAI[wiersz + 1][kolumna] = 4;
		gridAI[wiersz + 2][kolumna] = 4;
		gridAI[wiersz + 3][kolumna] = 4;
	}

	orientacja = rand() % 2 + 1;

	//Submarine:
	if (orientacja == 1) {
		//losujemy pozycje startowa statku
		while (1) {
			wiersz = rand() % 10 + 2;
			kolumna = rand() % 8 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz - 1][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna + 3] == 0 && gridAI[wiersz][kolumna + 3] == 0 && gridAI[wiersz + 1][kolumna + 3] == 0 && gridAI[wiersz + 1][kolumna + 2] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem do prawej)
		gridAI[wiersz][kolumna] = 3;
		gridAI[wiersz][kolumna + 1] = 3;
		gridAI[wiersz][kolumna + 2] = 3;
	}
	else {
		//losujemy pozycje startowa statku
		while (1) {
			kolumna = rand() % 10 + 2;
			wiersz = rand() % 8 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 2][kolumna] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 2][kolumna + 1] == 0 && gridAI[wiersz + 3][kolumna + 1] == 0 && gridAI[wiersz + 3][kolumna] == 0 && gridAI[wiersz + 3][kolumna - 1] == 0 && gridAI[wiersz + 2][kolumna - 1] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem w dó³)
		gridAI[wiersz][kolumna] = 3;
		gridAI[wiersz + 1][kolumna] = 3;
		gridAI[wiersz + 2][kolumna] = 3;
	}

	orientacja = rand() % 2 + 1;

	//Cruiser:
	if (orientacja == 1) {
		//losujemy pozycje startowa statku
		while (1) {
			wiersz = rand() % 10 + 2;
			kolumna = rand() % 8 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz - 1][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna + 3] == 0 && gridAI[wiersz][kolumna + 3] == 0 && gridAI[wiersz + 1][kolumna + 3] == 0 && gridAI[wiersz + 1][kolumna + 2] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem do prawej)
		gridAI[wiersz][kolumna] = 6;
		gridAI[wiersz][kolumna + 1] = 6;
		gridAI[wiersz][kolumna + 2] = 6;
	}
	else {
		//losujemy pozycje startowa statku
		while (1) {
			kolumna = rand() % 10 + 2;
			wiersz = rand() % 8 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 2][kolumna] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 2][kolumna + 1] == 0 && gridAI[wiersz + 3][kolumna + 1] == 0 && gridAI[wiersz + 3][kolumna] == 0 && gridAI[wiersz + 3][kolumna - 1] == 0 && gridAI[wiersz + 2][kolumna - 1] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem w dó³)
		gridAI[wiersz][kolumna] = 6;
		gridAI[wiersz + 1][kolumna] = 6;
		gridAI[wiersz + 2][kolumna] = 6;
	}

	orientacja = rand() % 2 + 1;

	//Destroyer:
	if (orientacja == 1) {
		//losujemy pozycje startowa statku
		while (1) {
			wiersz = rand() % 10 + 2;
			kolumna = rand() % 9 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna + 2] == 0 && gridAI[wiersz][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna + 2] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem do prawej)
		gridAI[wiersz][kolumna] = 2;
		gridAI[wiersz][kolumna + 1] = 2;
	}
	else {
		//losujemy pozycje startowa statku
		while (1) {
			kolumna = rand() % 10 + 2;
			wiersz = rand() % 9 + 2;
			if (gridAI[wiersz][kolumna] == 0 && gridAI[wiersz + 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna - 1] == 0 && gridAI[wiersz - 1][kolumna] == 0 && gridAI[wiersz - 1][kolumna + 1] == 0 && gridAI[wiersz][kolumna + 1] == 0 && gridAI[wiersz + 1][kolumna + 1] == 0 && gridAI[wiersz + 2][kolumna + 1] == 0 && gridAI[wiersz + 2][kolumna] == 0 && gridAI[wiersz + 2][kolumna - 1] == 0 && gridAI[wiersz + 1][kolumna - 1] == 0 && gridAI[wiersz][kolumna - 1] == 0) {
				break;
			}
		}
		//ustawiamy statek (pole za polem w dó³)
		gridAI[wiersz][kolumna] = 2;
		gridAI[wiersz + 1][kolumna] = 2;
	}

	//Tworzenie obiektów statków
	Ships AircraftCarrier;
	Ships Battleship;
	Ships Submarine;
	Ships Cruiser;
	Ships Destroyer;

	Losowanie AI;

	std::cout << "+++ PLANSZA AI +++" << std::endl << std::endl;
	for (int i = 0; i < 14; i++) {
		std::cout << " | ";
		for (int j = 0; j < 14; j++) {
			std::cout << gridAI[i][j] << " | ";
		}
		std::cout << std::endl;
	}

	while (appWindow.isOpen()) {
		while (appWindow.pollEvent(appEvent)) {
			if (appEvent.type == Event::Closed) {
				appWindow.close();
			}
			if (appEvent.type == Event::MouseMoved) {
				clickx = appEvent.mouseMove.x;
				clicky = appEvent.mouseMove.y;
			}
			if (appEvent.type == Event::MouseButtonReleased) {
				if (clickx > 0 && clickx < 120 && clicky > 374 && clicky < 414) {
					Destroyer.setLimit(true);
					Destroyer.setRozmiar(2);
					Destroyer.setId(1);
					if (Destroyer.getOrientacja() == 0) {
						Destroyer.setOrientacja(1);
					}
				}
				if (clickx > 0 && clickx < 120 && clicky > 414 && clicky < 454) {
					Cruiser.setLimit(true);
					Cruiser.setRozmiar(3);
					Cruiser.setId(2);
					if (Cruiser.getOrientacja() == 0) {
						Cruiser.setOrientacja(1);
					}
				}
				if (clickx > 0 && clickx < 120 && clicky > 454 && clicky < 494) {
					Submarine.setLimit(true);
					Submarine.setRozmiar(3);
					Submarine.setId(3);
					if (Submarine.getOrientacja() == 0) {
						Submarine.setOrientacja(1);
					}
				}
				if (clickx > 0 && clickx < 120 && clicky > 494 && clicky < 534) {
					Battleship.setLimit(true);
					Battleship.setRozmiar(4);
					Battleship.setId(4);
					if (Battleship.getOrientacja() == 0) {
						Battleship.setOrientacja(1);
					}
				}
				if (clickx > 0 && clickx < 120 && clicky > 534 && clicky < 574) {
					AircraftCarrier.setLimit(true);
					AircraftCarrier.setRozmiar(5);
					AircraftCarrier.setId(5);
					if (AircraftCarrier.getOrientacja() == 0) {
						AircraftCarrier.setOrientacja(1);
					}
				}
				if (clickx > 120 && clickx < 240 && clicky > 374 && clicky < 414) {
					Destroyer.setLimit(true);
					Destroyer.setRozmiar(2);
					Destroyer.setId(1);
					if (Destroyer.getOrientacja() == 0) {
						Destroyer.setOrientacja(2);
					}
				}
				if (clickx > 120 && clickx < 240 && clicky > 414 && clicky < 454) {
					Cruiser.setLimit(true);
					Cruiser.setRozmiar(3);
					Cruiser.setId(2);
					if (Cruiser.getOrientacja() == 0) {
						Cruiser.setOrientacja(2);
					}
				}
				if (clickx > 120 && clickx < 240 && clicky > 454 && clicky < 494) {
					Submarine.setLimit(true);
					Submarine.setRozmiar(3);
					Submarine.setId(3);
					if (Submarine.getOrientacja() == 0) {
						Submarine.setOrientacja(2);
					}
				}
				if (clickx > 120 && clickx < 240 && clicky > 494 && clicky < 534) {
					Battleship.setLimit(true);
					Battleship.setRozmiar(4);
					Battleship.setId(4);
					if (Battleship.getOrientacja() == 0) {
						Battleship.setOrientacja(2);
					}
				}
				if (clickx > 120 && clickx < 240 && clicky > 534 && clicky < 574) {
					AircraftCarrier.setLimit(true);
					AircraftCarrier.setRozmiar(5);
					AircraftCarrier.setId(5);
					if (AircraftCarrier.getOrientacja() == 0) {
						AircraftCarrier.setOrientacja(2);
					}
				}
				if (clickx > 270 && clickx < 520 && clicky > 350 && clicky < 470) {
					game = 3;
				}
				if (game == 2) {
					for (int i = 2; i < 12; i++) {
						for (int j = 2; j < 12; j++) {
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Destroyer.getLimit() == true && Destroyer.getOrientacja() == 1) {
								if (Destroyer.SprawdzKolizje(grid, i, j)) {
									Destroyer.UstawPoziomo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Cruiser.getLimit() == true && Cruiser.getOrientacja() == 1) {
								if (Cruiser.SprawdzKolizje(grid, i, j)) {
									Cruiser.UstawPoziomo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Submarine.getLimit() == true && Submarine.getOrientacja() == 1) {
								if (Submarine.SprawdzKolizje(grid, i, j)) {
									Submarine.UstawPoziomo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Battleship.getLimit() == true && Battleship.getOrientacja() == 1) {
								if (Battleship.SprawdzKolizje(grid, i, j)) {
									Battleship.UstawPoziomo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && AircraftCarrier.getLimit() == true && AircraftCarrier.getOrientacja() == 1) {
								if (AircraftCarrier.SprawdzKolizje(grid, i, j)) {
									AircraftCarrier.UstawPoziomo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Destroyer.getLimit() == true && Destroyer.getOrientacja() == 2) {
								if (Destroyer.SprawdzKolizje(grid, i, j)) {
									Destroyer.UstawPionowo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Cruiser.getLimit() == true && Cruiser.getOrientacja() == 2) {
								if (Cruiser.SprawdzKolizje(grid, i, j)) {
									Cruiser.UstawPionowo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Submarine.getLimit() == true && Submarine.getOrientacja() == 2) {
								if (Submarine.SprawdzKolizje(grid, i, j)) {
									Submarine.UstawPionowo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && Battleship.getLimit() == true && Battleship.getOrientacja() == 2) {
								if (Battleship.SprawdzKolizje(grid, i, j)) {
									Battleship.UstawPionowo(grid, i, j);
								}
							}
							if (clickx < 55 + ((j - 2) * 28) && clickx>25 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && grid[i][j] == 0 && AircraftCarrier.getLimit() == true && AircraftCarrier.getOrientacja() == 2) {
								if (AircraftCarrier.SprawdzKolizje(grid, i, j)) {
									AircraftCarrier.UstawPionowo(grid, i, j);
								}
							}
						}
					}
				}
				if (game == 3) {
					for (int i = 2; i < 12; i++) {
						for (int j = 2; j < 12; j++) {
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 0) {
								std::cout << "PUDLO!" << std::endl;
								gridAI[i][j] = -1;
								game = 4;
							}
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 2) {
								std::cout << "Trafiles DESTROYERA!" << std::endl;
								gridAI[i][j] = 22;
								DestroyerAI--;
							}
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 3) {
								std::cout << "Trafiles Submarine!" << std::endl;
								gridAI[i][j] = 33;
								SubmarineAI--;
							}
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 4) {
								std::cout << "Trafiles Battleship!" << std::endl;
								gridAI[i][j] = 44;
								BattleshipAI--;
							}
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 5) {
								std::cout << "Trafiles Aircraft Carrier!" << std::endl;
								gridAI[i][j] = 55;
								AircraftCarrierAI--;
							}
							if (clickx < 378 + ((j - 2) * 28) && clickx > 349 + ((j - 2) * 28) && clicky > 25 + ((i - 2) * 28) && clicky < 55 + ((i - 2) * 28) && gridAI[i][j] == 6) {
								std::cout << "Trafiles Cruiser!" << std::endl;
								gridAI[i][j] = 66;
								CruiserAI--;
							}
						}
					}
				}
			}
		}
		appWindow.clear(Color::Black);
		appWindow.draw(sPlanszaGracza);
		sPlanszaAI.setPosition(324, 0);
		appWindow.draw(sPlanszaAI);
		sMenu.setPosition(0, 350);
		sMenu2.setPosition(120, 350);
		appWindow.draw(sMenu);
		appWindow.draw(sMenu2);
		sStartButton.setPosition(270, 350);
		appWindow.draw(sStartButton);
		for (int i = 2; i < 12; i++) {
			for (int j = 2; j < 12; j++) {
				if (grid[i][j] == 1 && Destroyer.getOrientacja() == 1) {
					sDestroyerH.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sDestroyerH);
					Destroyer.ZmienLimit();
				}
				if (grid[i][j] == 2 && Cruiser.getOrientacja() == 1) {
					sCruiserH.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sCruiserH);
					Cruiser.ZmienLimit();
				}
				if (grid[i][j] == 3 && Submarine.getOrientacja() == 1) {
					sSubmarineH.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sSubmarineH);
					Submarine.ZmienLimit();
				}
				if (grid[i][j] == 4 && Battleship.getOrientacja() == 1) {
					sBattleshipH.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sBattleshipH);
					Battleship.ZmienLimit();
				}
				if (grid[i][j] == 5 && AircraftCarrier.getOrientacja() == 1) {
					sAircraftCarrierH.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sAircraftCarrierH);
					AircraftCarrier.ZmienLimit();
				}
				if (grid[i][j] == 1 && Destroyer.getOrientacja() == 2) {
					sDestroyerV.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sDestroyerV);
					Destroyer.ZmienLimit();
				}
				if (grid[i][j] == 2 && Cruiser.getOrientacja() == 2) {
					sCruiserV.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sCruiserV);
					Cruiser.ZmienLimit();
				}
				if (grid[i][j] == 3 && Submarine.getOrientacja() == 2) {
					sSubmarineV.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sSubmarineV);
					Submarine.ZmienLimit();
				}
				if (grid[i][j] == 4 && Battleship.getOrientacja() == 2) {
					sBattleshipV.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sBattleshipV);
					Battleship.ZmienLimit();
				}
				if (grid[i][j] == 5 && AircraftCarrier.getOrientacja() == 2) {
					sAircraftCarrierV.setPosition((-3 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sAircraftCarrierV);
					AircraftCarrier.ZmienLimit();
				}
			}
		}
		for (int i = 2; i < 12; i++) {
			for (int j = 2; j < 12; j++) {
				if (gridAI[i][j] == -1) {
					sPudlo.setPosition((321 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sPudlo);
				}
				if (gridAI[i][j] == 22 || gridAI[i][j] == 33 || gridAI[i][j] == 44 || gridAI[i][j] == 55 || gridAI[i][j] == 66) {
					sTrafienie.setPosition((321 + ((j - 2) + 1) * 29), (((i - 2) + 1) * 29) - 4);
					appWindow.draw(sTrafienie);
					if (i < 11 && j < 11) {
						sPudlo.setPosition((321 + j * 29), i * 29 - 4);
						appWindow.draw(sPudlo);
					}
					if (i > 2 && j > 2) {
						sPudlo.setPosition((321 + (j - 2) * 29), (i - 2) * 29 - 4);
						appWindow.draw(sPudlo);
					}
					if (j > 2 && i < 11) {
						sPudlo.setPosition((321 + (j - 2) * 29), i * 29 - 4);
						appWindow.draw(sPudlo);
					}
					if (j < 11 && i > 2) {
						sPudlo.setPosition((321 + j * 29), (i - 2) * 29 - 4);
						appWindow.draw(sPudlo);
					}
				}
			}
		}
		if (game == 3 || game == 4) {
			for (int m = 0; m < 14; m++) {
				grid[0][m] = 0;
				grid[m][0] = 0;
				grid[13][m] = 0;
				grid[m][13] = 0;
			}
		}
		if (game == 4) {
			if (AI.getStartR() == 0 && AI.getStartC() == 0) {
				int w = rand() % 10 + 2;		//losowanie koordynatow, w ktore strzelic ma AI
				int k = rand() % 10 + 2;		//losowanie koordynatow, w ktore strzelic ma AI

				if (grid[w][k] > -1 && AI.getR() == 0 && AI.getC() == 0) {
					if (grid[w][k] == 0) {
						sleep(czas);
						std::cout << "AI PUDLO!" << std::endl;
						grid[w][k] = -1;
						game = 3;
					}
					if (grid[w][k] == 1 || grid[w][k] == 11) {
						sleep(czas);
						std::cout << "AI trafilo Destroyera!" << std::endl;
						grid[w][k] = -2;
						if (grid[w - 1][k - 1] == 0) {
							grid[w - 1][k - 1] = -1;
						}
						if (grid[w - 1][k + 1] == 0) {
							grid[w - 1][k + 1] = -1;
						}
						if (grid[w + 1][k + 1] == 0) {
							grid[w + 1][k + 1] = -1;
						}
						if (grid[w + 1][k - 1] == 0) {
							grid[w + 1][k - 1] = -1;
						}
						AI.setObecnieTrafiony(Destroyer.getId());
						Destroyer.zmniejszRozmiar();
						AI.setStartPoint(w, k);
						AI.Trafienie();
					}
					if (grid[w][k] == 2 || grid[w][k] == 22) {
						sleep(czas);
						std::cout << "AI trafilo Cruisera!" << std::endl;
						grid[w][k] = -2;
						if (grid[w - 1][k - 1] == 0) {
							grid[w - 1][k - 1] = -1;
						}
						if (grid[w - 1][k + 1] == 0) {
							grid[w - 1][k + 1] = -1;
						}
						if (grid[w + 1][k + 1] == 0) {
							grid[w + 1][k + 1] = -1;
						}
						if (grid[w + 1][k - 1] == 0) {
							grid[w + 1][k - 1] = -1;
						}
						AI.setObecnieTrafiony(Cruiser.getId());
						Cruiser.zmniejszRozmiar();
						AI.setStartPoint(w, k);
						AI.Trafienie();
					}
					if (grid[w][k] == 3 || grid[w][k] == 33) {
						sleep(czas);
						std::cout << "AI trafilo Submarine!" << std::endl;
						grid[w][k] = -2;
						if (grid[w - 1][k - 1] == 0) {
							grid[w - 1][k - 1] = -1;
						}
						if (grid[w - 1][k + 1] == 0) {
							grid[w - 1][k + 1] = -1;
						}
						if (grid[w + 1][k + 1] == 0) {
							grid[w + 1][k + 1] = -1;
						}
						if (grid[w + 1][k - 1] == 0) {
							grid[w + 1][k - 1] = -1;
						}
						AI.setObecnieTrafiony(Submarine.getId());
						Submarine.zmniejszRozmiar();
						AI.setStartPoint(w, k);
						AI.Trafienie();
					}
					if (grid[w][k] == 4 || grid[w][k] == 44) {
						sleep(czas);
						std::cout << "AI trafilo Battleship!" << std::endl;
						grid[w][k] = -2;
						if (grid[w - 1][k - 1] == 0) {
							grid[w - 1][k - 1] = -1;
						}
						if (grid[w - 1][k + 1] == 0) {
							grid[w - 1][k + 1] = -1;
						}
						if (grid[w + 1][k + 1] == 0) {
							grid[w + 1][k + 1] = -1;
						}
						if (grid[w + 1][k - 1] == 0) {
							grid[w + 1][k - 1] = -1;
						}
						AI.setObecnieTrafiony(Battleship.getId());
						Battleship.zmniejszRozmiar();
						AI.setStartPoint(w, k);
						AI.Trafienie();
					}
					if (grid[w][k] == 5 || grid[w][k] == 55) {
						sleep(czas);
						std::cout << "AI trafilo Aircraft Carrier!" << std::endl;
						grid[w][k] = -2;
						if (grid[w - 1][k - 1] == 0) {
							grid[w - 1][k - 1] = -1;
						}
						if (grid[w - 1][k + 1] == 0) {
							grid[w - 1][k + 1] = -1;
						}
						if (grid[w + 1][k + 1] == 0) {
							grid[w + 1][k + 1] = -1;
						}
						if (grid[w + 1][k - 1] == 0) {
							grid[w + 1][k - 1] = -1;
						}
						AI.setObecnieTrafiony(AircraftCarrier.getId());
						AircraftCarrier.zmniejszRozmiar();
						AI.setStartPoint(w, k);
						AI.Trafienie();
					}
				}
			}
			//Hunt:
			if (AI.getStartR() && AI.getStartC()) {
				if (AI.getPonownie() == 0) {
					AI.setKierunek(rand() % 4 + 1);
					AI.setR_C(AI.getStartR(), AI.getStartC());
				}
				if (AI.getKierunek() == 1) {
					if (AI.getR() > 2) {
						AI.decrementR();
						if (AI.sprawdzCzyTrafiony(grid)) {
							sleep(czas);
							AI.setPonownie(1);
							std::cout << "Madre AI trafilo ponownie!" << std::endl;
							AI.zaznaczTrafienie(grid);
							if (AI.getObecnieTrafiony() == 1) {
								Destroyer.zmniejszRozmiar();
								if (Destroyer.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								Cruiser.zmniejszRozmiar();
								if (Cruiser.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								Submarine.zmniejszRozmiar();
								if (Submarine.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								Battleship.zmniejszRozmiar();
								if (Battleship.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								AircraftCarrier.zmniejszRozmiar();
								if (AircraftCarrier.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
								}
							}
							AI.Trafienie();
						}
						if (AI.sprawdzCzyPudlo(grid)) {
							std::cout << "Madre AI niestety spudlowalo..." << std::endl;
							sleep(czas);
							AI.zaznaczPudlo(grid);
							game = 3;
							if (AI.getObecnieTrafiony() == 1) {
								if (Destroyer.getRozmiar() != 0) {
									AI.setKierunek(3);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								if (Cruiser.getRozmiar() != 0) {
									AI.setKierunek(3);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								if (Submarine.getRozmiar() != 0) {
									AI.setKierunek(3);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								if (Battleship.getRozmiar() != 0) {
									AI.setKierunek(3);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								if (AircraftCarrier.getRozmiar() != 0) {
									AI.setKierunek(3);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
						}
					}else if(grid[AI.getR() - 1][AI.getC() + 1] > 0) {
						AI.setKierunek(2);
					}else if(grid[AI.getR() - 1][AI.getC() - 1] > 0) {
						AI.setKierunek(4);
					}
					else {
					AI.setKierunek(3);
					}
				}
				if (AI.getKierunek() == 2) {
					if (AI.getC() < 11) {
						AI.incrementC();
						if (AI.sprawdzCzyTrafiony(grid)) {
							sleep(czas);
							AI.setPonownie(1);
							std::cout << "Madre AI trafilo ponownie!" << std::endl;
							AI.zaznaczTrafienie(grid);
							if (AI.getObecnieTrafiony() == 1) {
								Destroyer.zmniejszRozmiar();
								if (Destroyer.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								Cruiser.zmniejszRozmiar();
								if (Cruiser.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								Submarine.zmniejszRozmiar();
								if (Submarine.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								Battleship.zmniejszRozmiar();
								if (Battleship.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								AircraftCarrier.zmniejszRozmiar();
								if (AircraftCarrier.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
								}
							}
							AI.Trafienie();
						}
						if (AI.sprawdzCzyPudlo(grid)) {
							sleep(czas);
							std::cout << "Madre AI niestety spudlowalo..." << std::endl;
							AI.zaznaczPudlo(grid);
							game = 3;
							if (AI.getObecnieTrafiony() == 1) {
								if (Destroyer.getRozmiar() != 0) {
									AI.setKierunek(4);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								if (Cruiser.getRozmiar() != 0) {
									AI.setKierunek(4);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								if (Submarine.getRozmiar() != 0) {
									AI.setKierunek(4);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								if (Battleship.getRozmiar() != 0) {
									AI.setKierunek(4);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								if (AircraftCarrier.getRozmiar() != 0) {
									AI.setKierunek(4);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
						}
					}
					else if (grid[AI.getR() - 1][AI.getC() - 1] > 0) {
					AI.setKierunek(1);
					}
					else if (grid[AI.getR() + 1][AI.getC() - 1] > 0) {
					AI.setKierunek(3);
					}
					else {
					AI.setKierunek(4);
					}
				}
				if (AI.getKierunek() == 3) {
					if (AI.getR() < 11) {
						AI.incrementR();
						if (AI.sprawdzCzyTrafiony(grid)) {
							sleep(czas);
							AI.setPonownie(1);
							std::cout << "Madre AI trafilo ponownie!" << std::endl;
							AI.zaznaczTrafienie(grid);
							if (AI.getObecnieTrafiony() == 1) {
								Destroyer.zmniejszRozmiar();
								if (Destroyer.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								Cruiser.zmniejszRozmiar();
								if (Cruiser.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								Submarine.zmniejszRozmiar();
								if (Submarine.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								Battleship.zmniejszRozmiar();
								if (Battleship.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								AircraftCarrier.zmniejszRozmiar();
								if (AircraftCarrier.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
								}
							}
							AI.Trafienie();
						}
						if (AI.sprawdzCzyPudlo(grid)) {
							sleep(czas);
							std::cout << "Madre AI niestety spudlowalo..." << std::endl;
							AI.zaznaczPudlo(grid);
							game = 3;
							if (AI.getObecnieTrafiony() == 1) {
								if (Destroyer.getRozmiar() != 0) {
									AI.setKierunek(1);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								if (Cruiser.getRozmiar() != 0) {
									AI.setKierunek(1);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								if (Submarine.getRozmiar() != 0) {
									AI.setKierunek(1);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								if (Battleship.getRozmiar() != 0) {
									AI.setKierunek(1);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								if (AircraftCarrier.getRozmiar() != 0) {
									AI.setKierunek(1);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
						}
					}
					else if (grid[AI.getR() + 1][AI.getC() + 1] > 0) {
						AI.setKierunek(2);
					}
					else if (grid[AI.getR() + 1][AI.getC() - 1] > 0) {
						AI.setKierunek(4);
					}
					else {
					AI.setKierunek(1);
					}
				}
				if (AI.getKierunek() == 4) {
					if (AI.getC() > 2) {
						AI.decrementC();
						if (AI.sprawdzCzyTrafiony(grid)) {
							sleep(czas);
							std::cout << "Madre AI trafilo ponownie!" << std::endl;
							AI.setPonownie(1);
							AI.zaznaczTrafienie(grid);
							if (AI.getObecnieTrafiony() == 1) {
								Destroyer.zmniejszRozmiar();
								if (Destroyer.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								Cruiser.zmniejszRozmiar();
								if (Cruiser.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								Submarine.zmniejszRozmiar();
								if (Submarine.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								Battleship.zmniejszRozmiar();
								if (Battleship.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								AircraftCarrier.zmniejszRozmiar();
								if (AircraftCarrier.getRozmiar() == 0) {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
								}
							}
							AI.Trafienie();
						}
						if (AI.sprawdzCzyPudlo(grid)) {
							sleep(czas);
							std::cout << "Madre AI niestety spudlowalo..." << std::endl;
							AI.zaznaczPudlo(grid);
							game = 3;
							if (AI.getObecnieTrafiony() == 1) {
								if (Destroyer.getRozmiar() != 0) {
									AI.setKierunek(2);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO DESTROYERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 2) {
								if (Cruiser.getRozmiar() != 0) {
									AI.setKierunek(2);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO CRUISERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 3) {
								if (Submarine.getRozmiar() != 0) {
									AI.setKierunek(2);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO SUBMARINE!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 4) {
								if (Battleship.getRozmiar() != 0) {
									AI.setKierunek(2);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO BATTLESHIP!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
							if (AI.getObecnieTrafiony() == 5) {
								if (AircraftCarrier.getRozmiar() != 0) {
									AI.setKierunek(2);
									AI.setR_C(AI.getStartR(), AI.getStartC());
								}
								else {
									std::cout << "AI ZATOPILO AIRCRAFT CARRIERA!!!" << std::endl;
									AI.Reset();
									game = 3;
								}
							}
						}
					}
					else if (grid[AI.getR() - 1][AI.getC() + 1] > 0) {
					AI.setKierunek(1);
					}
					else if (grid[AI.getR() + 1][AI.getC() + 1] > 0) {
					AI.setKierunek(3);
					}
					else {
					AI.setKierunek(2);
					}
				}
				if (AI.getTrafionePola() == 17) {
					std::cout << "KOMPUTER CIE POKONAL!!!" << std::endl;
					break;
				}
			}
			for (int i = 0; i < 14; i++) {
				std::cout << "| ";
				for (int j = 0; j < 14; j++) {
					std::cout << grid[i][j] << " | ";
				}
				std::cout << std::endl;
			}
		}
		for (int w = 2; w < 12; w++) {
			for (int k = 2; k < 12; k++) {
				if (grid[w][k] == -1) {
					sPudlo.setPosition((-3 + ((k - 2) + 1) * 29), (((w - 2) + 1) * 29) - 4);
					appWindow.draw(sPudlo);
				}
				if (grid[w][k] == -2) {
					sTrafienie.setPosition((-3 + ((k - 2) + 1) * 29), (((w - 2) + 1) * 29) - 4);
					appWindow.draw(sTrafienie);
				}
			}
		}
		if (DestroyerAI == 0) {
			std::cout << "Destroyer ZATOPIONY!" << std::endl;
			zatopione_okrety++;
			std::cout << "Zatopione okrety: " << zatopione_okrety << std::endl;
			DestroyerAI = 1;
		}
		if (SubmarineAI == 0) {
			std::cout << "Submarine ZATOPIONY!" << std::endl;
			zatopione_okrety++;
			std::cout << "Zatopione okrety: " << zatopione_okrety << std::endl;
			SubmarineAI = 1;
		}
		if (CruiserAI == 0) {
			std::cout << "Cruiser ZATOPIONY!" << std::endl;
			zatopione_okrety++;
			std::cout << "Zatopione okrety: " << zatopione_okrety << std::endl;
			CruiserAI = 1;
		}
		if (BattleshipAI == 0) {
			std::cout << "Battleship ZATOPIONY!" << std::endl;
			zatopione_okrety++;
			std::cout << "Zatopione okrety: " << zatopione_okrety << std::endl;
			BattleshipAI = 1;
		}
		if (AircraftCarrierAI == 0) {
			std::cout << "Aircraft Carrier ZATOPIONY!" << std::endl;
			zatopione_okrety++;
			std::cout << "Zatopione okrety: " << zatopione_okrety << std::endl;
			AircraftCarrierAI = 1;
		}
		//Informacja o wygranej
		if (zatopione_okrety == 5) {
			std::cout << "$$$$$ WYGRALES GRE $$$$$ WYGRALES GRE $$$$$ WYGRALES GRE $$$$$" << std::endl;
			break;
		}
		appWindow.display();
	}
	std::cout << "+++ PLANSZA GRACZA +++" << std::endl << std::endl;

	for (int i = 0; i < 14; i++) {
		std::cout << "| ";
		for (int j = 0; j < 14; j++) {
			std::cout << grid[i][j] << " | ";
		}
		std::cout << std::endl;
	}
	sleep(czas);
	return 0;
}
