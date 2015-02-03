/*******************************************************************************
Title: frabbi_hwk1.cpp
Author: Fazlay Rabbi 
Created on: 09/27/2014 
Description: Implementation file for a program which accepts a file name 
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
#include <algorithm>
#include<fstream>
#include"frabbi_hwk1.h"
using namespace std;

string dictionary::getword(){
  return word;           
}

dictionary::dictionary(string setword){
  word=setword;
}

void dictionary::sortSubstrings(){
  sort(substring.begin(),substring.end());
}

void substringmaker( vector<string>& subs, string word){
    subs.push_back(word);
    if (word.length()>2){//Base case is 2.
         substringmaker2(subs, word);
         word.erase(0,1);/*Erases the character in position 0. e.g. have is 
                          turned into ave*/
         substringmaker(subs, word);//calls itself until the world length is 2.
     }  
}
void substringmaker2(vector<string>& subs, string word){
       if(word.length()>2){//base case is 2
            word.erase(word.length()-1,1);/*Erases the character in last 
                                           position. e.g. have is turned into 
                                           hav*/    
            subs.push_back(word);//reduced string is entered into subs
            substringmaker2(subs, word);/*calls itself until the world 
                                         length is 2.*/
        }
}
void dictionary::createsubstring(){
    substringmaker( substring, word);
}

vector<string> dictionary::getsubstring() {
  return substring;              
}

void compare(vector<string> usersub, vector<dictionary> dic){
  int found=0;/*found indictates whether a single related word found. if 0, 
  then no related words found and if 1 at least 1 related word is found.
  Initially set to 0.*/
  for (int i=0; i<dic.size(); i++){
     int matched=0;/*matched indictates whether the word in dictionary 
     matched with user's word. if 0, then they don't and if 1 then they
     matched. Initially set to 0.*/
     for (int j=0; j<usersub.size(); j++){
         vector<string> tempsub= dic[i].getsubstring();/*tempsub contains 
                                                        substrings of words in dic[i].*/

         /*Following if-else statements deals with binary search. Note that
          every word's substrings in  dictionary are sorted. Therefore, we 
          compare the middle index of tempsub with usersub[j]*/
         if (tempsub[tempsub.size()/2]==usersub[j] ){
         
             if(found==0){
                 found=1;//First related word found
                 cout<<"Here is a list of similar word(s):\n";    
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                     
              } 
              else if(found==1){   
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                    
              } 
         }
        
         else if(tempsub[tempsub.size()/2]<usersub[j]){/*We do
           forward looping in this case*/
           for (int k=(tempsub.size()/2)+1; k< tempsub.size(); k++){
              if(usersub[j]==tempsub[k] && found==0){
                 found=1;//First related word found
                 cout<<"Here is a list of similar word(s):\n";    
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                     
              } 
              else if(usersub[j]==tempsub[k] && found==1){   
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                    
              } 
              if (matched==1)
                 break;//breaks the loop since substring match was found.             
           } 
         } 
         else if(tempsub[tempsub.size()/2]>usersub[j]){/*We do
           backward looping in this case*/
           for (int k=(tempsub.size()/2)-1; k >-1; k--){
              if(usersub[j]==tempsub[k] && found==0){
                 found=1;//First related word found
                 cout<<"Here is a list of similar word(s):\n";    
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                     
              } 
              else if(usersub[j]==tempsub[k] && found==1){   
                 cout<<dic[i].getword()<<endl;
                 matched=1  ; //substrings matched!                    
              } 
              if (matched==1)
                 break;//breaks the loop since substring match was found.             
           } 
         } 
         if (matched==1)
            break;//breaks the loop since substring match was found.  
     }  
     if (matched==1)
        continue;//continues to the next word in dic since match was found.  
  }
  if (found==0)//If no related words are found.
     cout<<"Sorry, no matching word found!\n";           
  cout<<endl;   
}
