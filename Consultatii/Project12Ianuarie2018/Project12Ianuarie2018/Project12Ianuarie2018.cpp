// Project12Ianuarie2018.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

class Box {
	void* continut;
public:
	Box(void* adresaContinut) {
		continut = adresaContinut;
	}

	void* getContinut() {
		return continut;
	}
};

class Frigider {
	int greutate = 10;
public:
	int getGreutate() {
		return this->greutate;
	}
};

class Prajitura {
	float tempMinima;
};

template<typename T, typename R> 
class BoxT {
	T* continut;
	float pret;
	R codBare;
public:
	BoxT(T* adresaContinut) {
		continut = adresaContinut;
	}

	T* getContinut() {
		return continut;
	}

	void getDescriere() {
		cout << endl << "Doar pentru electrocasnice";
	}
};

template<>
void BoxT<Prajitura, int>::getDescriere() {
	cout << endl << "Doar pentru prajituri";
}

int main()
{

	int * numere;
	int nr;

	vector<int> vectorNumere;
	vectorNumere.push_back(10);
	vectorNumere.push_back(20);
	vectorNumere.push_back(20);
	vectorNumere.push_back(20);
	vectorNumere.push_back(20);
	cout << endl << "Dimensiune " << vectorNumere.size();
	cout << endl << "Primul element " << vectorNumere[0];

	set<int> valoriUnice;
	valoriUnice.insert(20);
	valoriUnice.insert(20);
	valoriUnice.insert(20);
	valoriUnice.insert(20);
	valoriUnice.insert(30);
	valoriUnice.insert(40);
	cout << endl << "Dimensiune " << valoriUnice.size();
	set<int>::iterator it = valoriUnice.begin();
	for (; it != valoriUnice.end(); it++) {
		cout << endl << *it;
	}

	map<int, const char*> studenti;
	studenti.insert(pair<int, const char*>(1, "Gigel"));
	studenti.insert(pair<int, const char*>(2, "Ion"));
	studenti.insert(pair<int, const char*>(3, "Alina"));
	cout << endl << studenti[1];
	cout << endl << studenti[2];
	cout << endl << studenti[3];
	////impachetare
	//Frigider frigider;
	////Box livrareFrigider(&frigider);
	//Prajitura p;

	////BoxT<Prajitura,int> livrarePrajitura(&frigider);
	//BoxT<Prajitura, int> livrarePrajitura(&p);
	////BoxT<Frigider, float> livrarePrajitura2;

	//Box livrareFrigider(&p);

	////livrare
	//Frigider* destinatie = 
	//	(Frigider*)livrareFrigider.getContinut();
	//cout << endl << "Greutate frigider " << destinatie->getGreutate();


}

