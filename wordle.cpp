#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif
#include <cmath>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
bool isRealWord (std::string &word, const std::set<std::string>& dict);
void findCombinations(std::string& in, std::set<string>& combinations, int index, const std::set<std::string>& dict, int count, int& dashMax, const std::string& floating);
bool hasFloatingLetters(const std::string& word, const std::string& floating);




// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

		if(in == "-" && floating.size() == 0)
		{
			return {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
		}
		int dashes = 0;
		for(int i = 0; i < in.size(); i++)
		{
			if(in[i] == '-')
			{
				dashes++;  // finds howo many "-" are in "in"
			}
		}
		std::set<std::string> fakedict; // set that dict2 reference, since our function takes references
		std::set<std::string>& dict2 = fakedict;
		for(auto it = dict.begin(); it != dict.end(); ++it) //takes the words that have the floating letters and put them into a new dict
		{
			if(hasFloatingLetters(*it, floating) == true)//checks each string in dict and checks if it has the floating letters, if it does it adds them to dict2
			{
				dict2.insert(*it);
			}
		}

		int dashMax = pow(26, dashes); // total number of combinations
		int count = 0;
		std::string inCopy = in; //copy of in to modify it
    std::set<string> answers;
    findCombinations(inCopy, answers, 0, dict2, count, dashMax, floating);



    return answers;
}





// Define any helper functions here
bool isRealWord (std::string &word, const std::set<std::string>& dict)// checks if an inputed string is a real word in dict
{
		return dict.find(word) != dict.end();
}


void findCombinations(std::string& in, std::set<string>& combinations, int index, const std::set<std::string>& dict, int count, int& dashMax, const std::string& floating)
{
	if (count >= dashMax)
	{
    return;
  }
	if(index == in.size()) //base case for when when we fill in all the "-"s
	{
		if(isRealWord(in, dict) == true) 
		{
		combinations.insert(in); //if it is a real word , it is added to the answers set
		index = 0;
		return;
		}
		else
		{
			index = 0;
			return;
		}
	}

	if(in[index] == '-')
	{
		char originalChar = in[index];
		for (char letter = 'a'; letter <= 'z'; letter++)
		{
			in[index] = letter;
			count++;
			findCombinations(in, combinations, index+1, dict, count, dashMax, floating); //recursively creates all combinations
		}		

		in[index] = originalChar;
	}
	else
	{
		findCombinations(in, combinations, index+1, dict, count, dashMax, floating);
	}



}



bool hasFloatingLetters(const std::string& word, const std::string& floating) { //checks if the word has the floating letters
		for (char c : floating) {
        auto it = std::find(word.begin(), word.end(), c);
        if (it == word.end()) {
            return false; 
        }
    }
    return true; 
}