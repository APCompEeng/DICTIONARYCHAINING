// Implementation of ADT Dictionary
//     data object: a bunch of texting abbreviations and their meanings 
//     operations: create, destroy
//                 search the dictionary for an item given its text
//                 insert a new item into the dictionary
//                 remove an item from the dictionary given its text
//   associated operations: input and output
// filename dictionary.cpp
// authors: Adam Pesch
// date September 26, 2018

#include "dictionary.h"
#include "stack.h"
#include <iostream>


const int TABLESIZE = 11;

struct DictionaryRecord
{
	int numberOfItems;
	Stack* hashTablePtr;
};

void printStack(Stack hashTablePtr)
{
	Item topItem;
	Stack tempStack;
	bool isAdded;
	if(hashTablePtr.isEmpty())
	{
		cout << endl;
	}
	while (!hashTablePtr.isEmpty())
	{
		hashTablePtr.getTop(topItem);
		tempStack.push(topItem, isAdded);
		hashTablePtr.pop();
	}
	while (!tempStack.isEmpty())
	{
		tempStack.getTop(topItem);
		cout << "\t" << topItem << endl;
		tempStack.pop();
	}
}

void searchStack(Stack tempCopy, const Key& targetText, Item& anItem, bool& isFound)
{
	Item topItem;
	tempCopy.getTop(topItem);
	isFound = topItem == targetText;
	while(!isFound && !tempCopy.isEmpty())
	{
		tempCopy.pop();
		tempCopy.getTop(topItem);
		isFound = topItem == targetText;
	}
	if (isFound)
	{
		tempCopy.getTop(topItem);
		anItem = topItem;
	}
}

// displays a dictionary
// pre: output has been opened if it is a file
//      rightHandSideDictionary has been assigned items
// post: output contains each item on a separate line in the format with headings.
//       for example
//       address    text       meaning
//          0        lol       laugh out loud
//          1        ttyl      talk to you later
// usage: outfile << myDictionary;
ostream& operator<< (ostream& output, const Dictionary& rightHandSideDictionary)
{
	output << "address\ttext\tmeaning" << endl;
	for (int i = 0 ; i < TABLESIZE; i++)
	{
		output << "   " << i;
		printStack(rightHandSideDictionary.dictionaryPtr -> hashTablePtr[i]);
	}
	return output;
}

// inputs items into a dictionary
// pre: input has been opened if it is a file
//      items are arranged in the following format
//      2
//      lol
//      laugh out loud
//      ttyl
//      talk to you later
// post: if there is room, 
//       all items in the input have been stored in rightHandSideDictionary
// usage: infile >> myDictionary;
istream& operator>> (istream& input, Dictionary& rightHandSideDictionary)
{
	bool isFull = false;
	bool isAlreadyThere = false;
	int numOfInputs;
	
	input >> numOfInputs;
	for (int i = 0; ((i < numOfInputs) && (!isFull)); i++)
	{
		Item anItem;
		input >> anItem;
		rightHandSideDictionary.addNewEntry(anItem, isFull, isAlreadyThere);
	}
	return input;
}

// creates a new dictionary
// post: Dictionary object exists but is empty
// usage: Dictionary myDictionary;	
Dictionary::Dictionary(){
	dictionaryPtr = new DictionaryRecord;
	dictionaryPtr -> numberOfItems = 0; 
	dictionaryPtr -> hashTablePtr = new Stack[TABLESIZE];
}

// destroys a dictionary
// pre: Dictionary object exists
// post: all memory for Dictionary object has been freed
// usage: automatically done at the end of scope
Dictionary::~Dictionary()
{
	dictionaryPtr -> hashTablePtr = NULL;
	delete dictionaryPtr;
}

// searchs for a meaning with a given text
// pre targetText has been assigned 
// post if an item with texting abbreviationthe same as targetText is found then
//          isFound is true and theItem is that item
//       else isFound is false
// usage  myDictionary.searchForMeaning(targetText, anItem, isFound);
void Dictionary::searchForMeaning(const Key& targetText, Item& anItem, bool& isFound)
{
	int address = (targetText.convertToInteger() % TABLESIZE);
	Stack tempCopy(dictionaryPtr -> hashTablePtr[address]);
	Item topItem;
	
	tempCopy.getTop(topItem);
	isFound = topItem == targetText;

	int previousAddress = (address - 1) % TABLESIZE;
	
	while (!isFound && previousAddress != address)
	{
		address = (address+ 1) % TABLESIZE;
		tempCopy.getTop(topItem);
		isFound = topItem == targetText;
		searchStack(tempCopy, targetText, anItem, isFound);
	}
	if (isFound)
	{
		tempCopy.getTop(topItem);
		anItem = topItem;
	}
}


// inserts a new text' item into the dictionary
// pre: newItem has been assigned
// post: if there is room in the Dictionary object and newItem's text
//            is not already there  isFull is false and isAlreadyThere is false
//            and newItem is appropriately added
//       else either isFull is true or isAlreadyThere is true, depending
// usage: myDictionary.addNewEntry(myItem, isFull, isAlreadyThere);
void Dictionary::addNewEntry(const Item& newItem, bool& isFull, bool& isAlreadyThere)
{
	Item temp;
	bool isAdded;
	int address = (newItem.convertToInteger() % TABLESIZE);
	
	if (!isAlreadyThere && !isAdded)
	{
		dictionaryPtr -> hashTablePtr[address].push(newItem, isAdded);
		dictionaryPtr -> numberOfItems++;
	}
	else
	{
		isAlreadyThere = true;
	}
}

void deleteFromStack(Stack& hashTablePtr, const Key& targetText, bool& isFound)
{
	Stack tempStack;
	Item topItem;
	bool isAdded;
	while(!isFound && !hashTablePtr.isEmpty())
	{
		cout << "found it" << endl;
		hashTablePtr.getTop(topItem);
		isFound = targetText == topItem;
		if(!isFound)
		{
			tempStack.push(topItem, isAdded);
		}
		hashTablePtr.pop();
	}
	while(!tempStack.isEmpty())
	{
		tempStack.getTop(topItem);
		hashTablePtr.push(topItem, isAdded);
		tempStack.pop();
	}
}

// removes the item associated with a given text from the dictionary
// pre: targetText is assigned
// post: if Dictionary object is not empty and 
//           targetText is found in Dictionary object, isFound is true
//           and the associated Item object (text and meaning) has been 
//           removed from the Dictionary object 
//       else isFound is false or isEmpty is true depending
// usage: myDictionary.deleteEntry(myText, isEmpty, isFound);
void Dictionary::deleteEntry(const Key& targetText, bool& isEmpty, bool& isFound)
{
	isFound = false;
	isEmpty = false;
	int address;
	int indexStop;
	Item topItem;
	
	address = (targetText.convertToInteger() % TABLESIZE);
	indexStop = (address - 1) % TABLESIZE;
	dictionaryPtr -> hashTablePtr[address].getTop(topItem);
	isFound = topItem == targetText;
	isEmpty = !(dictionaryPtr -> numberOfItems == TABLESIZE);
	
	if(isFound)
	{
		dictionaryPtr -> hashTablePtr[address].pop();
	}
	
	while (!isFound && (address != indexStop))
	{
		deleteFromStack(dictionaryPtr -> hashTablePtr[address], targetText, isFound);
		address = (address+1) % TABLESIZE;
	}
	
	
}