#pragma once

class Ships {
	bool limit;
	int rozmiar;
	int orientacja;
	int id;
public:
	//Ships(bool l, int r, int o);
	Ships();
	void ZmienLimit();
	void Trafienie();
	int getRozmiar();
	int getOrientacja();
	int getId();
	bool getLimit();
	void zmniejszRozmiar();
	void setOrientacja(const int o);
	void setRozmiar(const int r);
	void setLimit(bool l);
	void setId(const int id);
	void UstawPoziomo(int grid[][14], int i, int j);
	void UstawPionowo(int grid[][14], int i, int j);

	bool SprawdzKolizje(int grid[][14], int i, int j);
};
