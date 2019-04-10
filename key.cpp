//filename key.cpp
//author  Adam Pesch
//date September 7, 2018
//Implementation of Abstract Data Type Key
//
//   data object: a key which is a texting abbreviation
//   operations: create, destroy, copy, 
//               input, output, assign
//               check if same, check if less than, 
//               convert to an integer

#include "key.h"

//allows for input of an item from either the standard input device or a file
//pre input has been opened and readied for the input of
//    a texting abbreviation followed by newline and associated meaning with
//    spaces between words ending with a newline. For example:
//    lol
//    laugh out loud
//
//post rightHandSideItem has been filled with a texting abbreviation and its
//     associated meaning
//usage cin >> myItem;
istream& operator>> (istream& input, Key& rightHandSideKey)
{
   input >> rightHandSideKey.textingAbbreviation;
   return input;
}

//allows for the output of an item to the standard output device or a file
//pre rightHandSideItem has been filled with a texting abbreviation and
//    its associated meaning 
//    output has been opened
//post rightHandSideItem has been written to the output device
//     lol:  laugh out loud
// 
//usage  outfile << myItem;
ostream& operator<< (ostream& output, const Key& rightHandSideKey)
{
   output << rightHandSideKey.textingAbbreviation;
   return output;
}

//creates an empty item (texting abbreviation and its associated meaning)
//post 
//usage Item aitem;
Key::Key()
{
   
}

//creates a specific texting abbreviation
//pre keyText is assigned a string that represents a texting abbreviation
//post Key object has a copy of the texting abbreviation in keyText
//usage Key akey("lol"); 
Key::Key(string keyText)
{
   textingAbbreviation = keyText;
}

//releases memory for a texting abbreviation
//pre Key object exists
//post Key object no longer exists, memory has been freed
//usage automatically done at the end of scope
Key::~Key()
{
   
}

//copies a texting abbreviation
//pre rightHandSideKey has been assigned a texting abbreviation
//post Key object has a copy of rightHandSideKey
//usage bkey = akey;
Key& Key::operator=(const Key& rightHandSideKey)
{
   if (this != &rightHandSideKey) {
		textingAbbreviation = rightHandSideKey.textingAbbreviation;
   }
	return *this;
}


//converts a texting abbreviation to an integer
//pre Key object exists
//post returns the sum of the ASCII values of letters in the texting abbreviation
//usage cout << akey.convertToInteger();
int Key::convertToInteger() const
{
   int asciiSum = 0;
   for (int k = 0; k < textingAbbreviation.length(); k++)
   {
       asciiSum = asciiSum + textingAbbreviation.at(k);;
   }
   return asciiSum;
}

//checks if two texting abbreviations are the same
//pre rightHandSideKey has been assigned
//post returns true if Key object is the same exact texting abbreviation as that in rightHandSideKey
//usage if (akey == bkey) { cout << "the texting abbreviations are the same" << endl;
bool Key::operator==(const Key& rightHandSideKey) const
{
   return (textingAbbreviation == rightHandSideKey.textingAbbreviation);
}

//checks if one texting abbreviation is less than another
//pre rightHandSideKey has been assigned a texting abbreviation
//post returns true if Key object's texting abbreviation is less than (alphabetically) the one in rightHandSideKey
//usage if (akey < bkey) { cout << "left text is less than right text" << endl;
bool Key::operator<(const Key& rightHandSideKey) const
{
  
  return (textingAbbreviation < rightHandSideKey.textingAbbreviation);
 
}
