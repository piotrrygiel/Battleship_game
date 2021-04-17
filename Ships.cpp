#include "Ships.h"

/*Ships::Ships(bool l, int r, int o)
{
	limit = l;
	rozmiar = r;
	orientacja = o;
}*/

Ships::Ships()
{
	limit = false;
	rozmiar = 0;
	orientacja = 0;
	id = 0;
}

void Ships::ZmienLimit()
{
	limit = false;
}

void Ships::Trafienie()
{
	rozmiar--;
}

int Ships::getRozmiar()
{
	return rozmiar;
}

int Ships::getOrientacja()
{
	return orientacja;
}

int Ships::getId()
{
	return id;
}

bool Ships::getLimit()
{
	return limit;
}

void Ships::zmniejszRozmiar()
{
	--rozmiar;
}

void Ships::setOrientacja(const int o)
{
	orientacja = o;
}

void Ships::setRozmiar(const int r)
{
	rozmiar = r;
}

void Ships::setLimit(bool l)
{
	limit = l;
}

void Ships::setId(const int id)
{
	this->id = id;
}

void Ships::UstawPoziomo(int grid[][14], int i, int j)
{
	if (id < 3) {
		for (int x = 0; x < rozmiar; x++) {
			if (x == 0) {
				grid[i][j] = rozmiar - 1;
			}
			else {
				grid[i][j + x] = (rozmiar - 1) * 11;
			}
		}
	}
	else {
		for (int x = 0; x < rozmiar; x++) {
			if (x == 0) {
				grid[i][j] = rozmiar;
			}
			else {
				grid[i][j + x] = rozmiar * 11;
			}
		}
	}
}

void Ships::UstawPionowo(int grid[][14], int i, int j)
{
	if (id < 3) {
		for (int x = 0; x < rozmiar; x++) {
			if (x == 0) {
				grid[i][j] = rozmiar - 1;
			}
			else {
				grid[i + x][j] = (rozmiar - 1) * 11;
			}
		}
	}
	else {
		for (int x = 0; x < rozmiar; x++) {
			if (x == 0) {
				grid[i][j] = rozmiar;
			}
			else {
				grid[i + x][j] = rozmiar * 11;
			}
		}
	}
}

bool Ships::SprawdzKolizje(int grid[][14], int i, int j)
{
	//Destroyer
	if (id == 1) {
		if (orientacja == 1) {
			if (grid[i][j + 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i + 1][j] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j + 2] == 0 && grid[i][j + 2] == 0 && grid[i - 1][j + 2] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
		else {
			if (grid[i + 1][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0 && grid[i + 2][j] == 0 && grid[i + 2][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
	}
	//Cruiser
	if (id == 2) {
		if (orientacja == 1) {
			if (grid[i][j + 1] == 0 && grid[i][j + 2] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j + 2] == 0 && grid[i - 1][j + 3] == 0 && grid[i][j + 3] == 0 && grid[i + 1][j + 3] == 0 && grid[i + 1][j + 2] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
		else {
			if (grid[i + 1][j] == 0 && grid[i + 2][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0 && grid[i + 3][j + 1] == 0 && grid[i + 3][j] == 0 && grid[i + 3][j - 1] == 0 && grid[i + 2][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
	}
	//Submarine (warunki identyczne jak Cruiser bo ten sam rozmiar)
	if (id == 3) {
		if (orientacja == 1) {
			if (grid[i][j + 1] == 0 && grid[i][j + 2] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j + 2] == 0 && grid[i - 1][j + 3] == 0 && grid[i][j + 3] == 0 && grid[i + 1][j + 3] == 0 && grid[i + 1][j + 2] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
		else {
			if (grid[i + 1][j] == 0 && grid[i + 2][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0 && grid[i + 3][j + 1] == 0 && grid[i + 3][j] == 0 && grid[i + 3][j - 1] == 0 && grid[i + 2][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
	}
	//Battleship
	if (id == 4) {
		if (orientacja == 1) {
			if (grid[i][j + 1] == 0 && grid[i][j + 2] == 0 && grid[i][j + 3] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j + 2] == 0 && grid[i - 1][j + 3] == 0 && grid[i - 1][j + 4] == 0 && grid[i][j + 4] == 0 && grid[i + 1][j + 4] == 0 && grid[i + 1][j + 3] == 0 && grid[i + 1][j + 2] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
		else {
			if (grid[i + 1][j] == 0 && grid[i + 2][j] == 0 && grid[i + 3][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0 && grid[i + 3][j + 1] == 0 && grid[i + 4][j + 1] == 0 && grid[i + 4][j] == 0 && grid[i + 4][j - 1] == 0 && grid[i + 3][j - 1] == 0 && grid[i + 2][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
	}
	//Aircraft Carrier
	if (id == 5) {
		if (orientacja == 1) {
			if (grid[i][j + 1] == 0 && grid[i][j + 2] == 0 && grid[i][j + 3] == 0 && grid[i][j + 4] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i - 1][j + 2] == 0 && grid[i - 1][j + 3] == 0 && grid[i - 1][j + 4] == 0 && grid[i - 1][j + 5] == 0 && grid[i][j + 5] == 0 && grid[i + 1][j + 5] == 0 && grid[i + 1][j + 4] == 0 && grid[i + 1][j + 3] == 0 && grid[i + 1][j + 2] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 1][j] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
		else {
			if (grid[i + 1][j] == 0 && grid[i + 2][j] == 0 && grid[i + 3][j] == 0 && grid[i + 4][j] == 0 && grid[i - 1][j - 1] == 0 && grid[i - 1][j] == 0 && grid[i - 1][j + 1] == 0 && grid[i][j + 1] == 0 && grid[i + 1][j + 1] == 0 && grid[i + 2][j + 1] == 0 && grid[i + 3][j + 1] == 0 && grid[i + 4][j + 1] == 0 && grid[i + 5][j + 1] == 0 && grid[i + 5][j] == 0 && grid[i + 5][j - 1] == 0 && grid[i + 4][j - 1] == 0 && grid[i + 3][j - 1] == 0 && grid[i + 2][j - 1] == 0 && grid[i + 1][j - 1] == 0 && grid[i][j - 1] == 0) {
				return true;
			}
		}
	}
	return false;
}
