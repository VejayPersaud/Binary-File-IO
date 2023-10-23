#include "extrafile.h"
#include <fstream>
#include <climits>
using namespace std;

void loadFile(const string &filename, vector<Starship> &ships) { //opens the given file and loads the Starship objects into the vector.


    ifstream inFile(filename,ios_base::binary); 

    if (!inFile) {// trivial error handle case check
        cout << "Error opening file: " << filename << endl;
        return;
    }

    int numShips; //initialize the variable numShips. The first batch of bytes in the file is the number of ships
    inFile.read(reinterpret_cast<char*>(&numShips), sizeof(numShips)); //from the file, the first batch of bytes representing the number of ships is sent to variable numShips

    for (int i = 0; i < numShips; i++) {// this loop will populate objects with their attributes from the structured binary file.
        Starship ship;// Create a Starship object called ship in program memory

        //The next batch of info from the binary file is a length of a "string", and then the actual characters that make up that string. Read in the length and data in two separate sections
        
        //Read in amount/length of the string.
        int nameLength;
        inFile.read(reinterpret_cast<char*>(&nameLength),sizeof(nameLength));
        
        //Reserve space for the array of characters. Start reading them into our array and assigning it to the object attributes.
        char* name = new char[nameLength]; //array of characters dynamically allocated on the heap
        inFile.read(name, nameLength); //read in x length of bytes and send to the name pointer.
        ship.name = string(name, name + nameLength - 1); //Starts at where name points to in the array.name + nameLength - 1 is pointer arithmetic and adds positions to the pointer essentially, moving it.-1 will help exclude the null terminator
        delete[] name; //cleanup



        //Read in the amount/length of the class of ship string
        int classLength;
        inFile.read(reinterpret_cast<char*>(&classLength), sizeof(classLength));

        //Reserve space for the array of  characters. Start reading them int our array and assigning it to the objects attributes.
        char* shipClass = new char[classLength];
        inFile.read(shipClass, classLength);
        ship.shipClass = string(shipClass, shipClass + classLength - 1);
        delete[] shipClass; 



        // Read in ship length(short, should be 2 bytes)
        inFile.read(reinterpret_cast<char*>(&ship.length), sizeof(ship.length));


        // Read in shield capacity
        inFile.read(reinterpret_cast<char*>(&ship.shieldCapacity), sizeof(ship.shieldCapacity));


        // Read in maximum warp speed
        inFile.read(reinterpret_cast<char*>(&ship.maxWarp), sizeof(ship.maxWarp));


        // Read in number of weapons
        int numWeapons;
        inFile.read(reinterpret_cast<char*>(&numWeapons), sizeof(numWeapons));

        for (int j = 0; j < numWeapons; j++) { //Each Starship object has multiple weapons with attributes. 
            Weapon weapon; //Create a Weapon object called weapon in program memory.

            //Same structure as above. Length and data are read in.
            
            //Amount/Length of name
            int weaponNameLength;
            inFile.read(reinterpret_cast<char*>(&weaponNameLength),sizeof(weaponNameLength));

            //data of the character in the name
            char* weaponName = new char[weaponNameLength];
            inFile.read(weaponName,weaponNameLength);
            weapon.name = string(weaponName, weaponName + weaponNameLength - 1); //reminder the -1 excludes the null terminator and this uses pointer arithmetic.
            delete[] weaponName;


            // Read in the weapon power rating
            inFile.read(reinterpret_cast<char*>(&weapon.powerRating), sizeof(weapon.powerRating));

            // Read in the weapon power consumption
            inFile.read(reinterpret_cast<char*>(&weapon.powerConsumption), sizeof(weapon.powerConsumption));

            ship.weapons.push_back(weapon);// add the weapon to the ship object's vector(armament/inventory) of available weapons.

        
        
        }// end of j for loop

        ships.push_back(ship);

 
    }// end of i for loop
}//end of loadFile

void printAllShips(const vector<Starship> &ships) {
    
    if (ships.empty()) {// Trivial case check
        cout << "No starships available." << endl;
        return;
    }

    // Iterate over all ships and print their details
    for (unsigned int i = 0; i < ships.size(); i++) {
        cout << "Name: " << ships[i].name << endl;
        cout << "Class: " << ships[i].shipClass << endl; 
        cout << "Length: " << ships[i].length << endl;
        cout << "Shield capacity: " << ships[i].shieldCapacity << endl;
        cout << "Maximum Warp: " << ships[i].maxWarp << endl;
        cout << "Armaments:" << endl;

        int totalFirepower = 0;
        bool hasWeapons = false;

        // Print weapons
        for (unsigned int j = 0; j < ships[i].weapons.size(); j++) {
            hasWeapons = true; //if we enter this loop at all that means it has weapons
            totalFirepower += ships[i].weapons[j].powerRating;

            cout << ships[i].weapons[j].name << ", " << ships[i].weapons[j].powerRating << ", " << ships[i].weapons[j].powerConsumption << endl;
        }

        
        if (!hasWeapons) {//Check if the ship is unarmed
            cout << "Unarmed" << endl;
        }
        
        if (totalFirepower > 0) {// Check if total firepower is greater than 0, and display if true.
            cout << "Total firepower: " << totalFirepower << endl;
        }

        if (i != ships.size() - 1) {//Check if its not last ship, print newline to separate
            cout << endl;
        }
        
    }
}

Starship starshipWithStrongestWeapon(const vector<Starship> &ships) {

    if (ships.empty()) {//trivial case check
        cout << "No starships available." << endl;
    }
    
    int maxWeaponPower = -1; //case to prove wrong. If there are no strongest weapons, then maxWeaponPower will remain -1
    
    
    unsigned int indexOfStrongestWeaponShip = ships.size();// Start with an invalid index to signify that no starship has been found yet.

    // Iterate over all ships
    for (unsigned int i = 0; i < ships.size();i++) {

        // For each ship, iterate over its weapons
        for (unsigned int j = 0; j < ships[i].weapons.size(); j++) {

            
            if (ships[i].weapons[j].powerRating > maxWeaponPower) {//Condition check if the weapon's power is greater than maxWeaponPower
                maxWeaponPower = ships[i].weapons[j].powerRating;
                indexOfStrongestWeaponShip = i;
            }
        }
    }

    // Return the ship with the strongest weapon
    return ships[indexOfStrongestWeaponShip];
    
}

Starship strongestStarshipOverall(const vector<Starship> &ships) {
    if (ships.empty()) {//trivial case, list is empty
        return Starship();
    }

    int maxCombinedPower = -1;//case to prove wrong. If there are no strongest Starship object, then maxCombinedPower will remain -1
    unsigned int strongestIndex = 0;// index of the starship with the highest combined power

    // Traverse the ships
    for (unsigned int i = 0; i < ships.size(); i++) {
        int currentCombinedPower = 0;

        // Compute combined weapon power for the current ship
        for (unsigned int j = 0; j < ships[i].weapons.size(); ++j) {
            currentCombinedPower += ships[i].weapons[j].powerRating;
        }

        
        if (currentCombinedPower > maxCombinedPower) {//Check if current starship's combined weapon power is greater than the max found so far, update the max
            maxCombinedPower = currentCombinedPower;
            strongestIndex = i;
        }
    }

    // Return the starship with the highest combined power
    return ships[strongestIndex];
}

Starship weakestArmedStarship(const vector<Starship> &ships) {
    int minWeaponPower = INT_MAX; // Initialize with the largest possible int value
    unsigned int indexOfWeakestArmedShip = 0;

    
    for (unsigned int i = 0; i < ships.size(); i++) {// Iterate over all ships
        int totalPower = 0;

        
        if (ships[i].weapons.size() > 0) {//Check if a ship has weapons
            
            for (unsigned int j = 0; j < ships[i].weapons.size(); j++) {// Sum the power of all weapons on this ship
                totalPower += ships[i].weapons[j].powerRating;
            }

            
            if (totalPower < minWeaponPower) {// Check if this ship's total weapon power is less than the current minimum, update our minimum and remember this ship's index
                minWeaponPower = totalPower;
                indexOfWeakestArmedShip = i;
            }
        }
    }

    
    
    if (indexOfWeakestArmedShip == ships.size()) {// Error check if we didn't find any armed starship (all ships had no weapons).
        return Starship(); // or throw an exception
    }

    // Return the ship with the weakest total weapon power using the saved index
    return ships[indexOfWeakestArmedShip];
}

void printShip(const Starship& ship) {
    cout << "Name: " << ship.name << endl;
    cout << "Class: " << ship.shipClass << endl;
    cout << "Length: " << ship.length << endl;
    cout << "Shield capacity: " << ship.shieldCapacity << endl;
    cout << "Maximum Warp: " << ship.maxWarp << endl;

    int totalFirepower = 0;

    if (ship.weapons.empty()) {
        cout << "Armaments: " << endl << "Unarmed" << endl;
    }
    else {
        cout << "Armaments: " << endl;
        for (unsigned int i = 0; i < ship.weapons.size(); i++) {
            Weapon weapon = ship.weapons[i];
            totalFirepower += weapon.powerRating;
            cout << weapon.name << ", " << weapon.powerRating << ", " << weapon.powerConsumption << endl;
        }
    }

    if (totalFirepower > 0) {
        cout << "Total firepower: " << totalFirepower << endl;
    }

    cout << endl; // Extra newline for spacing between ships
    
    
}

vector<Starship> unarmedShips(const vector<Starship> &ships) {
    vector<Starship> result;

    // Iterate over all ships
    for (unsigned int i = 0; i < ships.size(); i++) {
        
        if (ships[i].weapons.size() == 0) {// Check if the ship has no weapons
            result.push_back(ships[i]);
            printShip(ships[i]);
        }
    }

    return result;
}


