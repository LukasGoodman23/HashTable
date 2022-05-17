//main.cpp

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int SIZE = 26;
//making a constant size for the array
const int HASH = 26;
//this is my hash key

struct node
{
    //creating a struct node for the linked list
    string data;
    node *next = NULL;
};

struct node *bucketArray[SIZE];
//a global array called bucketArray

void insert(string newData)
{
    //linked list insert method
    struct node *newNode = new node;   //create a new node
    newNode->data = newData;              //setting the data
    newNode->next = bucketArray[int(tolower(newData.at(0))) % HASH];   //the hashing
    bucketArray[int(tolower(newData.at(0))) % HASH] = newNode;    //shifting in the array
}

bool find(string lookup)
{
    //pass in what we are looking for
    struct node *temp;
    //create a temp node
    int x = int(tolower(lookup.at(0))) % HASH;
    //now we find the key with our hash function		
    temp = bucketArray[x];
    //set temp as a node	
    if (bucketArray[x] == NULL)
    {
        //if null empty
        cout << "Not here " << endl;;
        return false;
    }
    if (bucketArray[x]->data == lookup)
    {
        //if data at the hash function value is same as lookup we found it!
        cout << "found at index " << x << endl;
        return true;
    }
    else
    { //we need to check if the data may be in that index, but in the chain so we need to step through the list
        while (temp != NULL)
        {
            if (temp->data == lookup)
            {
                cout << "found at index " << x << endl;
                return true;
            }
            temp = temp->next;
            //moves the while loop to the end of the list

        }
        return false;
    }
}

void display()
{
    struct node *temp;
    //this is like ½ of the lookup method
    for (int i = 0; i < SIZE; i++)
    {
        int x = i % HASH;
        //just use the hash function to find index
        temp = bucketArray[x];
        while (temp != NULL)
        {
            cout << temp->data << " ";
            //print it out
            temp = temp->next;
        }
        cout << endl;
    }
}

int main()
{
    string word;

    ifstream fin("words.in");
    if (!fin) {
        cout << "File not found\n";
        exit(2);
    }

    while (!fin.eof())
    {
        fin >> word;
        for (int j= 0; j < word.size(); j++)
        {
            word[j]= tolower(word[j]);
        }
        insert(word);
    }

    //read in the rows and cols
    fin.close();

    display();             //displaying the data
    cout << find("cabal");     //looking for yellow
}