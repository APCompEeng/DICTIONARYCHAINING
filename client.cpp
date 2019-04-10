// tests the operations of dictionary.cpp
// filename client.cpp
// authors: Adam Pesch
// date September 26, 2018

#include "dictionary.h"
#include <iostream>
#include <fstream>

using namespace std;

void part2a(istream& input, Dictionary& myDictionary);
void part2b(istream& input, Dictionary& myDictionary);
void part2c(istream& input, Dictionary& myDictionary, Key& brb, Key& yil, Item& anItem, bool& isFound);
void part2d(istream& input, Dictionary& myDictionary, Key& deleteTest, bool& isFound, bool& isEmpty);
void part2e(istream& input, Dictionary& myDictionary, Key& yil, Item& anItem, bool& isFound);

int main()
{
	Item a, anItem;
	Key brb("brb");
	Key yil("yil");
	Key deleteTest("yli");
	bool isFull, isAlreadyThere, isFound, isEmpty;
	ifstream input;
	Dictionary myDictionary;
	
	input.open("in.dat");
	
	part2a(input, myDictionary);
	
	part2b(input, myDictionary);
	
	part2c(input, myDictionary, brb, yil, anItem, isFound);
	
	part2d(input, myDictionary, deleteTest, isFound, isEmpty);
	
	part2e(input, myDictionary, yil, anItem, isFound);
	
	input.close();
	
	return 0;
}


void part2a(istream& input, Dictionary& myDictionary)
{
	cout << "part 2a)" << endl;
	//part 2a input 4 unique abbreviations
	input >> myDictionary;
	
	cout << myDictionary << endl;
}

void part2b(istream& input, Dictionary& myDictionary)
{
	cout << "part 2b)" << endl;
	//part 2b input 3 more abbreviations that will out to the same spot as one of the previous ones
	input >> myDictionary;
	
	cout << myDictionary << endl;
}

void part2c(istream& input, Dictionary& myDictionary, Key& brb, Key& yil, Item& anItem, bool& isFound)
{
	cout << "part 2c)" << endl;
	//part 2c read 2 more abbreviations and look for their meanings. One is one of the original ones, one is the last one from part b
	cout << "currently searching for brb and yil" << endl << endl;
	
	myDictionary.searchForMeaning(brb, anItem, isFound);
	
	cout << anItem << endl << endl;
	
	myDictionary.searchForMeaning(yil, anItem, isFound);
	
	cout << anItem << endl << endl;
}

void part2d(istream& input, Dictionary& myDictionary, Key& deleteTest, bool& isFound, bool& isEmpty)
{
	cout << "part 2d)" << endl;
	//part 2d read another abbreviation that is the second from part b) and delete it
	myDictionary.deleteEntry(deleteTest, isEmpty, isFound);
	
	cout << "currently removing yli" << endl << endl;
	
	cout << myDictionary << endl;
}

void part2e(istream& input, Dictionary& myDictionary, Key& yil, Item& anItem, bool& isFound)
{
	cout << "part 2e)" << endl;
	//read and search for the last one from part b again, which makes you go by the deleted one
	cout << "currently searching for yil" << endl << endl;
	
	myDictionary.searchForMeaning(yil, anItem, isFound);
	
	cout << anItem << endl << endl;
}