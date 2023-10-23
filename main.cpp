#include <iostream>
#include <fstream>
#include "extrafile.h"
using namespace std;

int main()
{
	//Initialize the ships vector of Starship objects
	vector<Starship> ships;

	//cout << "Which file(s) to open?\n";
	//cout << "1. friendlyships.shp" << endl;
	//cout << "2. enemyships.shp" << endl;
	//cout << "3. Both files" << endl;
	int option;
	cin >> option;

	if (option == 1) {
		loadFile("friendlyships.shp", ships);
	}

	if (option == 2) {
		loadFile("enemyships.shp", ships);
	}

	if (option == 3) {
		loadFile("friendlyships.shp", ships);
		loadFile("enemyships.shp", ships);
	}


	//cout << "1. Print all ships" << endl;
	//cout << "2. Starship with the strongest weapon" << endl;
	//cout << "3. Strongest starship overall" << endl;
	//cout << "4. Weakest ship (ignoring unarmed)" << endl;
	//cout << "5. Unarmed ships" << endl;

	cin >> option;

	if (option == 1) {
		printAllShips(ships);
	}
	if (option == 2) {
		//-1 if no ship found has a strongest weapon
		printShip(starshipWithStrongestWeapon(ships));
	}
	if (option == 3) {
		printShip(strongestStarshipOverall(ships));
	}
	if (option == 4) {
		printShip(weakestArmedStarship(ships));
	}
	if (option == 5) {
		unarmedShips(ships);
	}


	return 0;
}