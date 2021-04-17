#pragma once

class Losowanie {
	int start_r;
	int start_c;
	int obecnie_trafiony;
	int kierunek;
	int ponownie;
	int trafione_pola;
	int r;
	int c;
public:
	Losowanie();
	void setStartPoint(int st_r, int st_c);
	void setObecnieTrafiony(int ob_traf);
	void setKierunek(int kier);
	void zmienPonownie();
	void Trafienie();
	void setR_C(int r, int c);
	
	void setPonownie(int p);

	void Reset();

	bool sprawdzCzyTrafiony(int grid[][14]);
	bool sprawdzCzyPudlo(int grid[][14]);

	void zaznaczTrafienie(int grid[][14]);
	void zaznaczPudlo(int grid[][14]);

	int getStartR();
	int getStartC();
	int getObecnieTrafiony();
	int getKierunek();
	int getPonownie();
	int getTrafionePola();
	int getR();
	int getC();

	void decrementR();
	void decrementC();
	void incrementR();
	void incrementC();
};
