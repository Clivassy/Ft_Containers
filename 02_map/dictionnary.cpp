#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <list>

using namespace std;

int main()
{
    //------------------------
    //  STANDARD MAP 
    //------------------------
    map< string, string> myDictionary;

    myDictionary.insert(pair<string, string>("banana","banane"));
    myDictionary.insert(pair<string, string>("pineaple","ananas"));
    myDictionary.insert(pair<string, string>("orange","orange"));
    myDictionary.insert(pair<string, string>("apple","pomme"));

    myDictionary["apple"] = "Die "; // access and change element of the map
   //   myDictionary["cocumber"] = "Cocombre";
   //   myDictionary.clear();
    cout << myDictionary.size() << endl;
    for (auto pair : myDictionary) {
        cout << pair.first << "-" << pair.second << endl;
    }
    cout << "-------------------------------" << endl;

    //////////////////////////////////////////////////////

    //--------------
    //  POKEDEX 
    //--------------
    map<string, list<string> > pokedex;

    list<string> pikachuAttacks { "thunder shock", "tail whip", "quick attack"};
    list<string> charmanderAttacks { "flame thrower ", "scary face"};
    list<string> chikoriAttacks { "razor leaf", "poison powder"};

    pokedex.insert(pair<string, list<string> >("Pikachu", pikachuAttacks));
    pokedex.insert(pair<string, list<string> >("Charmander", charmanderAttacks));
    pokedex.insert(pair<string, list<string> >("Chikori", chikoriAttacks));

    for (auto pair : pokedex) {
        cout << pair.first << " - ";
        
        for (auto attack : pair.second)
            cout << attack << " - ";
        
        cout << endl;
    }
}