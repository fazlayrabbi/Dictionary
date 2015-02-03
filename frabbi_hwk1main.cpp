/*******************************************************************************
Title: frabbi_hwk1main.cpp
Author: Fazlay Rabbi 
Created on: 09/27/2014 
Description: Main file for a program which accepts a file name 
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
#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<cstring>
#include<fstream>
#include"frabbi_hwk1.h"
using namespace std;
int main(int argc, char *argv[]){

 int j=0;//j is the counter for vector d.
 ifstream input;//input opens te file in command line.
 string temp, run;/*temp takes input from ifstream input and user's word. 
 run takes input for continuation of the program*/ 
 char ctemp[33];/*ctemp is used to convert any uppercase letter in user's 
 word to lower case*/
 char c;/*c is used to convert any uppercase letter in user's word 
 to lower case*/
 vector <dictionary> d;//d is vector of type dictionary.
 
 input.open(argv[1]);
 
 if (input.fail()){
     cerr<<"Dictionary file could not be opened.\n";
     exit(1);
    }
 while(!input.eof()){//runs till the end of file
     input >> temp;
     d.push_back(temp);
     d[j].createsubstring();
     d[j].sortSubstrings();
     j++;
    }  
 input.close();  
  
 while(true){
  cout<< "Please enter a word to lookup (more than 1 and less than 33";
  cout<<" characters):\n";
  getline(cin, temp);
  cout<<endl;
  while(temp.length()<2 || temp.length() >32){
   cout<<"Invalid amount of characters entered.\n";
   cout<< "Please enter a word to lookup (more than 1 and less than 33";
   cout<<" characters):\n"; 
   getline(cin, temp);  
   cout<<endl;                  
  }
  strcpy(ctemp, temp.c_str());/*temp is copied to ctemp so that uppercase 
                                            letter (if any) is converted to lowercase.*/
  
  int i=0;//Counter for characters in ctemp.
  while(ctemp[i]){
    c=ctemp[i];//c takes each individual character of ctemp at a time.
    ctemp[i]= (tolower(c));//tolower converts uppercase letter to lower case.
    i++;              
  }
  temp= ctemp;//After conversion of uppercase letters to lower case.
  vector<string> subtemp; //subtemp is substrings of user's word.
  substringmaker(subtemp, temp);//substrings of user's word are created.
  compare(subtemp, d);/*comparison of dictionary words and user's word are 
                                   done.*/
  cout<< "Do you want to look up another word?\n" ;
  cout<<"(Enter 'No' or 'N' to discontinue or enter any other charatcer to "; 
  cout<< "continue):\n";
  getline(cin, run);
  cout<<endl;
  if (run=="No"||run=="no"||run=="n"||run=="N"||run=="nO"||run=="NO")
     break;// While loop and program ends if user enters N or No.
  }
  
 return 0;   
}
