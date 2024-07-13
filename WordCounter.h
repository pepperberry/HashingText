//hashingText
//3/6/2024
//pepper berry
#include ream>
#include eam>
#include ing>


using namespace std;

#ifndef _WORDCOUNTER_
#define _WORDCOUNTER_

class WordCounter {
public:

    WordCounter(int capacity);
    ~WordCounter();

    int getTotalWordCount();
    bool empty();
    int getCapacity();
    int getWordCount(string word);
    int getUniqueWordCount();
    void removeWord(string word);
    int addWord(string word);

    //opperator overloader
    WordCounter& operator=(const WordCounter &obj);
    //copy constructor
    WordCounter(const WordCounter &obj);



private:
    struct node{//nodes of the linekd list
        string key;//word
        int amount;//amount
        node * next;
    };
    node ** table;//array of ptrs
    int maximum;//size of array
    int total; //amount of words in the table
    int unique; //amount of unique words in the table

};

//copy constructor
WordCounter::WordCounter(const WordCounter &obj) {
    table = new node*[obj.maximum];
    this->maximum = obj.maximum;
    this->unique = obj.unique;
    this->total = obj.total;
    for(int i = 0; i < obj.maximum; ++i){
        this->table[i] = nullptr;
    }

    for(int i = 0; i < obj.maximum; ++i){
        node * currObj = obj.table[i];


        while((currObj) != nullptr){

            node * newNode = nullptr;
            newNode = new node;
            newNode->key = (currObj)->key;
            newNode->amount = (currObj)->amount;
            newNode->next = nullptr;
            if(obj.table[i] == currObj){
                this->table[i] = newNode;//newest code
            }else{
                node * currThis = this->table[i];
                while(currThis->next != nullptr){
                    currThis = currThis->next;
                }
                currThis->next = newNode;
            }
            currObj = currObj->next;

        }
    }
}

//opperator overloader
WordCounter& WordCounter::operator=(const WordCounter &obj){
    if (this != &obj) {
        this->~WordCounter();
    }
    table = new node*[obj.maximum];
    this->maximum = obj.maximum;
    this->unique = obj.unique;
    this->total = obj.total;
    for(int i = 0; i < obj.maximum; ++i){
        this->table[i] = nullptr;
    }

    for(int i = 0; i < obj.maximum; ++i){
        node * currObj = obj.table[i];


        while((currObj) != nullptr){

            node * newNode = nullptr;
            newNode = new node;
            newNode->key = (currObj)->key;
            newNode->amount = (currObj)->amount;
            newNode->next = nullptr;
            if(obj.table[i] == currObj){
                this->table[i] = newNode;//newest code
            }else{
                node * currThis = this->table[i];
                while(currThis->next != nullptr){
                    currThis = currThis->next;
                }
                currThis->next = newNode;
            }
            currObj = currObj->next;

        }
    }

    return *this;

}


//Constructor: The constructor must accept the given capacity and use that for the size of the array.
WordCounter::WordCounter(int capacity){
    table = new node*[capacity];
    for(int i = 0; i < capacity; ++i){
        table[i] =  nullptr;
    }
    maximum = capacity;
    unique = 0;
    total = 0;
}

//getCapacity: Returns the capacity of the hash table.
int WordCounter::getCapacity(){
    return maximum;
}

//empty: Returns true if no words have been added to the hash table; otherwise, returns false.
bool WordCounter::empty(){
    int size = 0;
    for(int i = 0; i < maximum; ++i){
        if((table[i]) != nullptr){
            ++size;
        }
    }
    return (size==0);
}

//getTotalWordCount: Returns the total number of words encountered, including duplicates.
int WordCounter::getTotalWordCount(){
    return total;
}

//getWordCount: Returns the count of the word or zero if word does not exist.
int WordCounter::getWordCount(string word){
    int count = 0;
    size_t hashCode = hash<string>{}(word);//finds index of the table in which the word is located
    int index = hashCode % maximum;
    node * curr = table[index];
    while(curr != nullptr){
        if(curr->key == word){
            count = curr->amount;
        }
        curr = curr->next;
    }
    return count;

}

//~HashTable() : A destructor.
WordCounter::~WordCounter(){
    for(int i = 0; i < maximum; ++i){
        if((table[i]) != nullptr){
            node * nextNode = nullptr;
            node * curr = table[i];
            while(curr != nullptr){
                nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
        }
    }
    delete[] table;
}

//Takes in a word. and either incriments count or adds it to the table
int WordCounter::addWord(string word){
    int times;
    ++ total;

    size_t hashCode = hash<string>{}(word);//finds index of the table in which the word is located
    int index = hashCode % maximum;
    node * curr = table[index];

    //if the word does not exist add to table, check using counter = 0
    if(getWordCount(word) == 0){
        ++unique;
        node * newNode = nullptr;
        newNode = new node;
        newNode->key = word;
        newNode->amount = 1;
        times = 1;
        newNode->next = nullptr;



        if(curr == nullptr){
            table[index] = newNode;
        }else{
            while(curr->next != nullptr){
                curr = curr->next;
            }
            curr->next = newNode;
        }

    }else{//if the word does exist find word and update counter to more nums
        while(curr != nullptr){
            if(curr->key == word){
                ++ curr->amount;
                times = curr->amount;
                curr = curr->next;
            }else{
                curr = curr->next;
            }
        }

    }

    return times;

}

//getUniqueWordCount: Returns the number of unique words encountered (i.e. entries in the hash table).
int WordCounter::getUniqueWordCount(){
    return unique;
}

//removeWord: Takes in a word completely removes it from the table.
//Update the unique and total word counts if necessary.
void WordCounter::removeWord(string word){

    size_t hashCode = hash<string>{}(word);//finds index of the table in which the word is located
    int index = hashCode % maximum;
    node * curr = table[index];
    node * prev = nullptr;


    while(curr != nullptr){
        if(curr->key == word){//if word found
            if(curr->next != nullptr){//if not at end of list
                if(prev == nullptr){
                    table[index] = curr->next;
                }else{
                    prev->next = curr->next;
                }

                total -= curr->amount;
                --unique;
                delete curr;
                return;
            }else{
                total -= curr->amount;
                --unique;
                delete curr;
                if(prev == nullptr){
                    table[index] = nullptr;
                }else{
                    prev->next = nullptr;
                }
                return;

            }
        }else{//iterate
            prev = curr;
            curr = curr->next;
        }
    }


}


#endif
