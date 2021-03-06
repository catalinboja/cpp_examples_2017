// ProjectLab8.cpp : Defines the entry point for the console application.
//
#include <fstream>
#include <iostream>
using namespace std;

class MeteoStation {
	char city[100];
	float tempRecordings[24];
	int currentHour;

public:

	MeteoStation() {
		strcpy(this->city, "Nowhere");
		this->currentHour = 0;
		for (int i = 0; i < 24; i++) {
			this->tempRecordings[i] = INT32_MAX;
		}
	}

	MeteoStation(char* cityName) {
		strcpy(this->city, cityName);
		this->currentHour = 0;
		for (int i = 0; i < 24; i++) {
			this->tempRecordings[i] = INT32_MAX;
		}
	}

	float operator[](int hour) {
		if (hour >= 0 && hour < this->currentHour) {
			return this->tempRecordings[hour];
		}
		else
			throw exception();
	}

	void setTemp(int hour, float temp) {
		if (hour >= 0 && hour < 24) {
			if (temp < 1000 && temp > -1000) {
				this->tempRecordings[hour] = temp;
				if(hour > currentHour)
					this->currentHour = hour;
			}
			else throw exception();
		}
		else throw exception();
	}

	friend ostream& operator<<(ostream& console, MeteoStation& station);
};

ostream& operator<<(ostream& console, MeteoStation& station) {
	console << endl << "Location: " << station.city;
	console << endl << "Temperature recordings:";
	for (int i = 0; i <= station.currentHour; i++)
		if(station.tempRecordings[i] == INT32_MAX)
			console << " ## " << "-";
		else
			console << " ## " << station.tempRecordings[i];
	return console;
}

class WeatherStatus {
public:
	char country[100];
	MeteoStation stations[100];
	int noStations;

	WeatherStatus() {
		noStations = 0;
	}

};


//function that will create a text report for weather conditions
void generateReport(WeatherStatus country, char* reportName) {
	ofstream report;
	report.open(reportName, ios::out|ios::app);
	if (report.is_open()) {
		report << "Weather report" << endl;
		for (int i = 0; i < country.noStations; i++)
			report << country.stations[i];
	}
	report.close();

}

int main()
{
	MeteoStation station1("Bucharest");
	MeteoStation station2("Ploiesti");

	station1.setTemp(9, 16.7);
	station1.setTemp(10, 19);
	station2.setTemp(5, 5.3);
	station2.setTemp(2, 3);

	cout << station1 << station2;

	WeatherStatus weather;
	strcpy(weather.country, "Romania");
	weather.noStations = 2;
	weather.stations[0] = station1;
	weather.stations[1] = station2;
	generateReport(weather, "WeatherRomania.txt");

	int vb;
	char test;
	cin >> test;
	cout << test;
	cin >> vb;
	cout << vb;

}

