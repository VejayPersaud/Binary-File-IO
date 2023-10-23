#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
using namespace std;

struct Weapon {
    string name;
    int powerRating;
    float powerConsumption;

};


struct Starship {
    string name;
    string shipClass;
    short length;
    int shieldCapacity;
    float maxWarp;
    vector<Weapon> weapons;

};



//Function Prototypes
void loadFile(const string& filename, vector<Starship>& ships);
void printAllShips(const vector<Starship>& ships);
Starship starshipWithStrongestWeapon(const vector<Starship>& ships);
Starship strongestStarshipOverall(const vector<Starship>& ships);
Starship weakestArmedStarship(const vector<Starship>& ships);
vector<Starship> unarmedShips(const vector<Starship>& ships);
void printShip(const Starship& ship);





