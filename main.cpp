//hasing the hobbit
//3/6/2024
//pepper berry
#include "WordCounter.h"
#include "CommonWordList.h"

#include eam>
#include ream>
#include eam>
#include ing>
#include nip>
using namespace std;

string cleanWord(string);
void removeCommonWords(WordCounter &);

void ReadFile(WordCounter &a, string filename);
void hashStats(WordCounter &);//so code is more consice



const char APOSTROPHE_CHAR = '\''; 	// apostrophe character used in cleanWord
const char HYPHEN_CHAR = '-'; 		// hyphen/dash character used in cleanWord

int main() {
    string filename;
    string words;
    string capacity;


    // populate common words
	CommonWordList::populateWords();


    //Ask client for filename & capacity & create a WordCounter object (hash table).
    cout << "What is the filename: ";
    getline(cin, filename);
    cout << endl <<"What is the capacity: ";
    getline(cin, capacity);
    WordCounter a(stoi(capacity));


    //Load the file and read in each word from file, includes cleaning the words
    ReadFile(a, filename);


    //After all words are read in from file, call removeCommonWords on the hash table.
    removeCommonWords(a);

    //Print hash table statistics.
    hashStats(a);


    //Ask client for the word(s) that they want to analyze.
    cout <<"\nEnter words to analyze (separated by spaces): ";
    getline(cin, words);


    //Print word analysis statistics.
    cout << "\n\nAnalysis of words:\n"
    <<"  Given Word   Count\n"
    <<"+------------+-------+\n";

    string word = "";
    int lenght = words.length();
    for(int i = 0; i < lenght; i++){
        if(words[i] == ' '){
            cout << "     " <<word <<"         "<<a.getWordCount(word) <<endl;
            word = "";
        }else{
            word += words[i];
        }


    }
    if(word.length() != 0){
        cout << "     " <<word <<"         "<<a.getWordCount(word) <<endl;
    }

    //Remove the word(s) inputted
    cout <<"\nEnter words to remove (separated by spaces): ";
    getline(cin, words);

    word = "";
    lenght = words.length();
    for(int i = 0; i < lenght; i++){
        if(words[i] == ' '){
            a.removeWord(word);
            word = "";
        }else{
            word += words[i];
        }


    }
    if(word.length() != 0){
        a.removeWord(word);
    }

    //Print hash table statistics again
    hashStats(a);

    //displays usage of copy construct and overloader
    cout <<"\nCopy construcor usage: \n";
    WordCounter b = a;
    hashStats(b);

    b.addWord("jazzy");
    cout <<"\nadds \"jazzy\" to the 2nd hash table to show the traansfer\n";
    cout <<"\nassignment overloader usage: \n";
    a = b;
    hashStats(a);



}

string cleanWord(string s) {
   string result = "";                  // Keep track of the cleaned result.
   unsigned i = 0, length = s.length(); // Input for the for loop.
   for (; i < length; i++) {
      if (isalnum(s[i]))
         result += tolower(s[i]);
      else if (s[i] == APOSTROPHE_CHAR) {
         if (i > 0 && isalnum(s[i-1]))
            result += s[i];
      } else if (s[i] == HYPHEN_CHAR) {
         if (i > 0 && i < (length-1) && isalnum(s[i-1]) && isalnum(s[i+1]))
            result += s[i];
			// If a word ends in a hyphen, we assume it is residue that needs to
			// be paired with the next word. Return the word with the hyphen as a
			// signal to the caller to retain it as residue.
         else if (i > 0 && i == (length-1) && isalnum(s[i-1]))
            result += s[i];
      }
   }
   return result;
}

void removeCommonWords(WordCounter &wc) {
    for (string &s : CommonWordList::getWords()){
        wc.removeWord(s);
    }
}

void ReadFile(WordCounter &a, string filename){//reads in the text file to vecotr
    string line;
    string FILENAME;
    string word = "";
    //gets file
    FILENAME = filename;
    ifstream inputFile(FILENAME);

    if(inputFile){
        while(getline(inputFile, line)) {
            //inputs file content to file string
            int lenght = line.length();
            for(int i = 0; i < lenght; i++){
                if(line[i] == ' ' ){
                    if(word.length() > 0 && word != "-"){
                        word = cleanWord(word);
                        a.addWord(word);
                    }
                    word = "";
                }else{
                    word += line[i];
                }
            }

            if(word.length() > 0 && word != "-"){//checks if a last word exists
                if(word[word.length()-1] != '-'){
                    word = cleanWord(word);
                    a.addWord(word);
                    word = "";
                }

            }else{word = "";}
        }

    }else{
        cout << "could not read file";

    }
    //closing the file
    inputFile.close();


}

//This includes the number of unique words, total number of words, and calculate the load factor.
void hashStats(WordCounter &a){
    //word stats
    double uCount = a.getUniqueWordCount();
    double cap = a.getCapacity();
    double loadSize = ((uCount)/(cap));
    //tests the empty funct
    if(a.empty() == 1){
        cout<<"\nis the table emptry right now?: true"<<endl<<endl;
    }else{
        cout<<"\nis the table emptry right now?: false"<<endl<<endl;
    }
    cout << "\nWord Counter statistics:\n"
    <<"  #Unique   #Total   Load F.\n"
    <<"+---------+--------+---------+\n"
    <<"     "<<uCount<<"       "<<a.getTotalWordCount()<<"        "<<setprecision(3)<<loadSize<<endl;//this does not really work


}



