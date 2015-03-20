//
//  main.cpp
//  jana_fortney_project
//
//  Created by Jana Fortney on 12/7/14.
//  Copyright (c) 2014 Jana Fortney. All rights reserved.
//

//
//  main.cpp
//  jana_fortney_hw09_attempt2
//
/*
 when n=1024, the program took 318 miliseconds, 21 max size
 when n=8192, the program took 297 miliseconds, 7 max size
 when n= 16384, the progam took 290 miliseconds, 5 max size
 
 I used a large portion of the bible as my text to test this.
 
 
 
 
 
 
 */
//  Created by Jana Fortney on 11/5/14.
//  Copyright (c) 2014 Jana Fortney. All rights reserved.
//


#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
#include<iterator>
#include <fstream>
#include <sstream>
using namespace std;



class WordRec
{
public:
    
    string wordS; //word string
    int wordC; ///word count
    WordRec *next;
    
    
    
    
    
    WordRec()
    {
        next = NULL;
    }
    
    WordRec(string string, int count)
    {
        wordS = string;
        wordC = count;
        next = NULL;
    }
    string toString()
    {
        stringstream ss;
        ss<< "Word: " << wordS << "\n";
        ss<< "Frequency: " << wordC <<"\n\n";
        return ss.str();
    }
};



class WordTab
{
private:
    WordRec* entries;
    int N;//size of table
    
    
    int hash(string s)
    {
        int hash = 5381 % N;
        for (int i = 0; i < s.length(); i++)
            hash = (hash * 33 + s[i]) % N;
        return hash;
    }
    
public:
    
    WordTab(int n)
    {
        N = n;
        entries = new WordRec[N];
        
        for (int i=0; i<N; i++)
        {
            entries[i].next = NULL;
            entries[i].wordS = "";
            entries[i].wordC = -1;
        }
        
        
    }
    
    ~WordTab()
    {
        for(int i = 0; i<N; i++)
        {
            if(entries[i].next!=NULL)
            {
                WordRec *temp = entries[i].next, *old = &entries[i];
                while(temp->next!=NULL)
                {
                    old = temp;
                    temp = temp->next;
                    delete old;
                }
                delete temp;
            }
        }
        delete[] entries;
    }
    
    
    
    
    void add( string s)
    {
        int h = hash(s);
        if( entries[h].wordC != -1)
        {
            WordRec *temp= &entries[h];
            
            while(temp->next != NULL)
            {
                if(temp->wordS == s)
                {
                    temp->wordC++;
                    break;
                }
                temp=temp->next;
            }
            if(temp->wordS == s)
                temp->wordC++;
            else
            {
                WordRec* old = temp;
                temp = new WordRec;
                temp->next = NULL;
                temp->wordS = s;
                temp->wordC = 1;
                old->next = temp;
            }
        }
        else
        {
            entries[h].wordC = 1;
            entries[h].wordS = s;
        }
        
    };
    
    WordRec* getEntries()
	{
        int size = 0, pos = 0;
        // int size2=0; /// measuring max link list size
        
        for (int i = 0; i < N; i++)// size of hash table = total size of all linked lists
        {
            size += listsize(&entries[i]);
            
            
        }
        
        
        WordRec *wordArray = new WordRec[size]; // allocate the array
        
        for (int i = 0; i < N; i++)         // copy elements of all linked lists to that array
            listcopy(&entries[i], wordArray, pos);
        
        return wordArray;
    }
    
    
    int maxsize()
    {
        int size = 0;
        int size2=0; /// measuring max link list size
        
        for (int i = 0; i < N; i++)// size of hash table = total size of all linked lists
        {
            size += listsize(&entries[i]);
            
            if (listsize(&entries[i])> size2)
            {
                size2=listsize(&entries[i]);
            }
            
        }
        
        return size2;
    }
    
    int listsize(WordRec *list)  // compute the size of a linked list
    {
        int size = 0;
        WordRec *temp = list;
        while (temp->next != NULL)
        {
            size++;
            temp = temp->next;
        }
        if(temp->wordC!= -1)
            size++;
        return size;
    }
    
    void listcopy(WordRec *list, WordRec array[], int &pos) // copy elements of a linked list into an array starting from pos
	{
        WordRec *temp = list;
        while (temp->next != NULL)
        {
            array[pos] = *temp;
            array[pos].next=&array[pos+1];
            pos++;
            temp = temp->next;
        }
        if(temp->wordC!=-1)
        {
            array[pos] = *temp;
            array[pos].next = &array[pos+1];
            pos++;
        }
    }
    string print()
    {
        stringstream ss;
        WordRec * temp;
        for(int i =0; i <N; i++)
        {
            temp = &entries[i];
            if(entries[i].wordC != -1)
            {
                while(temp->next!=NULL)
                {
                    ss<< temp->toString();
                    temp = temp->next;
                }
                ss<<temp->toString();
            }
        }
        
        return ss.str();
    }
};



void insertion_sort(vector<int> &arrC, vector<string> &arrS, int length)
{
    int i, j ,tmp;
    string temp;
    for (i = 1; i < length; i++)
    {
        j = i;
        while (j > 0 && arrC[j - 1] < arrC[j])
        {
            tmp = arrC[j];
            arrC[j] = arrC[j - 1];
            arrC[j - 1]= tmp;
            
            temp = arrS[j];
            arrS[j] = arrS[j - 1];
            arrS[j - 1] = temp;
            
            j--;
        }//end of while loop
        
    }//end of for loop
}


int getDynamicArraySize(WordRec * myArray)
{
    int count = 0;
    WordRec* temp = myArray;
    for(int i =0; temp[i].wordC > 0; i++)
    {
        count++;
    }
    return count;
}


int main()
{
   
    int n = 8192;
    WordTab myTable(n);
    WordRec * myArray;
    double count1;
   
    
    srand (time(NULL));
    
 
    clock_t begin1=clock();

  
        
        ifstream fin("/Users/janafortney/Desktop/item.txt");
        while (!fin.eof())
        {
            string word;
            fin>>word;
            myTable.add(word);
        
        }
        fin.close();
   
    
   
        vector<string> wordsVec;
        vector<string> twogram;
        
        ifstream fin1("/Users/janafortney/Desktop/item.txt");
        while (!fin1.eof())
        {
            string word;
            fin1>>word;
            wordsVec.push_back(word);
        }
        fin1.close();
        
        for(int i=0; i<=wordsVec.size(); i++)
        {
            twogram.push_back(wordsVec[i]+" "+wordsVec[i+1]);
        
        }
        
        for (int i=0; i<=twogram.size(); i++)
        {
            myTable.add(twogram[i]);
            
        }
        

    
    
    
        vector<string> threegram;
  
        for(int i=0; i<=wordsVec.size(); i++)
        {
            threegram.push_back(wordsVec[i]+" "+wordsVec[i+1]+" "+wordsVec[i+2]);
            
        }
        
        for (int i=0; i<=threegram.size()-1; i++)
        {
            myTable.add(threegram[i]);
            
        }
    
    
     myArray = myTable.getEntries();
    
    int size= getDynamicArraySize(myArray);
    cout<<size<<endl;
    
    vector<string> word;
    vector<int> count;
    
    
    for(int i=0; i<size; i++)
    {
        word.push_back(myArray[i].wordS);
        count.push_back(myArray[i].wordC);
    
    }
    
   
    
    insertion_sort(count,word, size);
  
    
    ofstream fout("/users/janafortney/Desktop/divide.txt");
    for(int i = 0; i<size; i ++)
    {
        fout<<"Word: "<<word[i]<<endl;
        fout<<"Freq: "<<count[i]<<endl<<endl;
        // cout<<myArray[i].toString();
    }
    fout.close();
    
    
    clock_t end1=clock();
    double time1 = (double) (end1-begin1) / CLOCKS_PER_SEC * 1000.0;
    count1 +=time1;
    
    int size3=myTable.maxsize();
    
    cout<<count1<<" miliseconds "<< size3<<" max size"<<endl;
    return 0;
}

