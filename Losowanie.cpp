#include "Losowanie.h"

Losowanie::Losowanie()
{
	start_r = 0;
	start_c = 0;
	obecnie_trafiony = 0;
	kierunek = 0;
	ponownie = 0;
	trafione_pola = 0;
	r = 0;
	c = 0;
}

void Losowanie::setStartPoint(int st_r, int st_c)
{
	start_r = st_r;
	start_c = st_c;
}

void Losowanie::setObecnieTrafiony(int ob_traf)
{
	obecnie_trafiony = ob_traf;
}

void Losowanie::setKierunek(int kier)
{
	kierunek = kier;
}

void Losowanie::zmienPonownie()
{
	if (ponownie == 0) {
		ponownie = 1;
	}
	else {
		ponownie = 0;
	}
}

void Losowanie::Trafienie()
{
	trafione_pola++;
}

void Losowanie::setR_C(int r, int c)
{
	this->r = r;
	this->c = c;
}

void Losowanie::setPonownie(int p)
{
	ponownie = p;
}

void Losowanie::Reset()
{
	start_r = 0;
	start_c = 0;
	obecnie_trafiony = 0;
	ponownie = 0;
	kierunek = 0;
	r = 0;
	c = 0;
}

bool Losowanie::sprawdzCzyTrafiony(int grid[][14])
{
	if (grid[r][c] > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Losowanie::sprawdzCzyPudlo(int grid[][14])
{
	if (grid[r][c] == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Losowanie::zaznaczTrafienie(int grid[][14])
{
	grid[r][c] = -2;
	if (grid[r - 1][c - 1] == 0) {
		grid[r - 1][c - 1] = -1;
	}
	if (grid[r - 1][c + 1] == 0) {
		grid[r - 1][c + 1] = -1;
	}
	if (grid[r + 1][c + 1] == 0) {
		grid[r + 1][c + 1] = -1;
	}
	if (grid[r + 1][c - 1] == 0) {
		grid[r + 1][c - 1] = -1;
	}
}

void Losowanie::zaznaczPudlo(int grid[][14])
{
	grid[r][c] = -1;
}

int Losowanie::getStartR()
{
	return start_r;
}

int Losowanie::getStartC()
{
	return start_c;
}

int Losowanie::getObecnieTrafiony()
{
	return obecnie_trafiony;
}

int Losowanie::getKierunek()
{
	return kierunek;
}

int Losowanie::getPonownie()
{
	return ponownie;
}

int Losowanie::getTrafionePola()
{
	return trafione_pola;
}

int Losowanie::getR()
{
	return r;
}

int Losowanie::getC()
{
	return c;
}

void Losowanie::decrementR()
{
	--r;
}

void Losowanie::decrementC()
{
	--c;
}

void Losowanie::incrementR()
{
	++r;
}

void Losowanie::incrementC()
{
	++c;
}
