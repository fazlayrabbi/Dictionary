/*******************************************************************************
Title: frabbi_hwk1.h
Author: Fazlay Rabbi 
Created on: 09/27/2014 
Description:Header file for a program which accepts a file name 
from command line containing a sorted list of words. These sorted list of 
words are then loaded and their substrings are created. Then the program 
asks user to enter a word to find a similar list of words in the dictionary. 
Program also creates substrings of that word and then compares substrings 
of user's words and words in dictionary. For each word in the dictionary if
any of substrings matches with that of user's word, then that dictionary 
word is outputed. The program asks user to input a word until user 
declines to do so.
Usage: ./main.exe dictionary file
Build with: g++ frabbi_hwk1main.cpp frabbi_hwk1.cpp -o main.exe
Dependencies: One input file that should be in the same directory.
Modifications: Comments were added on 09/29/2014
*******************************************************************************/
#ifndef FRABBI_HWK1_H
#define FRABBI_HWK1_H
#include<string>
#include<vector>
using namespace std;

class dictionary{
      public:
             dictionary(string setword);/*Declares the class dictionary and 
             sets the word.
             
             pre-condition: setword is the input word.
             post-condition: word is set equal to setword.*/
             void createsubstring();/*Creates substings of the word.
             
             post-condition: The function calls substringmaker which in turn
             calls substringmaker2 to create substrings of the word.*/
             
             string getword();//Function returns private member word.
             
             void sortSubstrings();/*This function sorts substrings of the word
             using function sort from template "algorithm"*/

             vector<string> getsubstring();
             //Function returns private member sunbstring.
             
      private:
              string word;
              vector<string> substring;
              //This vector is a list of substrings of the word
};

void substringmaker(vector<string>& subs, string word);/*This recurssive 
function sets substrings subs from string word by working collaboritively 
with substringmaker2. At first, the function puts the original word in the list 
of substring. Then it calls substringmaker2 which is also a recurssuve
fuction that continues to erase the last charcter of the already reduced word 
until its length= 2 and then it erases the first character of the word. 
substringmaker runs recurssively until the word length is reduced to 2.

pre-condition: subs is a call by refernce parameter which excepts substrings.
String word is the word for which substrings are to be made.
post-condition: vector subs contains all possible substrings that can be made 
from the word.*/

void substringmaker2(vector<string>& subs, string word);/*This recurssive 
function only gets called in another recurssive function, substringmaker. It 
gets a word from substringmaker and continues to erase the last character
of the word until its length gets reduced to 2.

pre-condition: subs is a call by refernce parameter which excepts substrings.
String word is the string recieved from substringmaker for which substrings
are to be made.
post-condition: vector subs contains substrings that can be made 
from the string recieved from substringmaker.
*/

void compare(vector<string> usersub, vector<dictionary> dic);
/* This function outputs all possible words in the dictionary which is related 
to the word user entered. It does so by comparing substrings of user's word 
and substrings of each word in the dictionary via binary search in a nested 
loop. If any of the substring matches, then the program outputs that word. 
Since the dictionary file is sorted and the program outputs the word in the 
sorted manner.

pre-condtion: usersub is the vector which contains all substrings of user's 
word. dic is the vector that contains all the words in the dictionary. 
post-condition: Outputs the list of words that are similar. In case there is no
related word, program informs the user about it.
*/

#endif
