// ProjectLab10.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>
using namespace std;

enum FuelType {DIESEL, GASOLINE, ELECTRIC};

class Engine {
	int cc;
	int rpm;
	FuelType type;
	const int serialNo;
public:
	Engine(int CC, int RPM, 
		FuelType Type,int Serial)
		:serialNo(Serial),cc(CC),rpm(RPM) {
		//this->cc = CC;
		this->type = Type;
	}
};

class Vehicle {
protected:
	char model[50];
	Engine engine;	//composition
public:
	Vehicle(char* Model,int CC, int RPM,
		FuelType Type, int Serial)
		:engine(CC,RPM,Type,Serial) {
		strcpy(this->model, Model);
	}
};

class ElectricVehicle :public Vehicle {
	int chargingLevel;
public:
	ElectricVehicle(int CC, int Serial, int level, char *model)
		:Vehicle(model,CC,5000,ELECTRIC,Serial) {
		this->chargingLevel = level;
	}
};


void main(int argc,char* values[])
{
	cout << endl << "We are at "
		<< values[0];
	if (argc == 3) {
		cout << endl << "We received:";
		cout << endl << values[1];
		cout << endl << values[2];

		//process the files
		ifstream vehicles;
		vehicles.open(values[2],ios::in);
		char buffer[1000];
		vehicles.getline(buffer,1000);
		cout << endl << buffer;
		//parse the line
		char* noVehicles = strtok(buffer, ";");

		int n = atoi(noVehicles);

		cout << endl << "No of vehicles " << n;
		while (char* value = strtok(NULL, ";")) {
			cout << endl << value;
		}

		vehicles.close();


	}
	ElectricVehicle eVehicle(1000,1,90,"Tesla S");
}

