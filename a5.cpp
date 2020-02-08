// a5.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Chamodi Basnayake
// St.# : 301309667
// Email: cbasnaya@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// You are only allowed to include these files --- don't include anything else!
// If you think it's necessary to include another file, please speak to the
// instructor.
//

#include "cmpt_error.h"
#include <iostream>
#include <fstream>
#include <sstream>



using namespace std;

class Hashtable {

private:
    int cap; // capacity of the table
    int sz;  // # of elements in the table

    enum class State { empty, removed, filled };

    struct Cell {
        string val;
        State state;
    };

    Cell* arr;

    //Using polynomial hashing to hash strings
    long long int hash(const string& s) const {
        long long int h = 0;
        long long int prime = 1;

        for ( int i = 0; i < s.length(); i++) {
            //Using 11 as the prime seed
            prime *= 11;
            h += int(s[i]) * prime;
        }
        
        return h;
    }

public:
    //Constructor: sets the initial capacity to 20 if capacity is unspecified
    Hashtable(int init_cap = 20): cap(init_cap), sz(0), arr(new Cell[cap]) {
        for(int i = 0; i < cap; i++) {
            //Sets all the cells to empty initially
            arr[i] = Cell{"", State::empty};
        }
    }

    ~Hashtable() {
        delete[] arr;
    }

    int size() const {
        return sz;
    }

    //Returns the array
    Cell* array() const {
        return arr;
    }

    int capacity() const {
        return cap;
    }

    double load_factor() const {
        return double(size()) / capacity();
    }

    bool is_empty() const {
        return size() == 0;
    }

    bool is_full() const {
        return size() == capacity();
    }

    //Takes in an array of type Cell*, then inserts the string into the hash table
    void put(const string& s, Cell* array) {

        unsigned long long int h = hash(s);

        for(int i = 0; ; i++) {
            //Calculate location based on quadratic probing
            int loc = (h + (i*i)) % cap;
            //If the state of the cell is empty or removed, insert the strin there
            if (array[loc].state == State::empty || array[loc].state == State::removed) {
                array[loc].val = s;
                array[loc].state = State::filled;
                sz++;

                //Check if the load factor is bigger than or equal to 0.5. If so, resize array
                double load = load_factor();

                if (load >= 0.5){
                    resize();
                }

                return;
            //If cell is filled, move on
            }else if ( array[loc].state == State::filled){

            }
        }
    }

    //If the the given string
    bool find(const string& s) {
        if (is_empty()) {
            return false;
        }

        //Store the hash value
        unsigned long long int h = hash(s);

        for (int i = 0; i < cap; i++) {
            //Calculate location using quadratic probing
            int loc = (h + (i*i)) % cap;
            string val = arr[loc].val;

            //If the cell is empty, stop the search as string isn't found
            if (arr[loc].state == State::empty) {
                return false;
            //If the Cell is filled, check if it is the right value
            } else if (arr[loc].state == State::filled){
                if (arr[loc].val == s) {
                    return true;
                }

            //If Cell is removed, continue
            } else if ( arr[loc].state == State::removed){
                
            }    
        }
        return false;
    }

    //Remoe a string from the hash table
    void remove(const string& s) {
        if (is_empty()) {
            return;
        }

        unsigned long long int h = hash(s);

        for (int i = 0; i < cap; i++) {    
            //Use quadratic probing to find location
            int loc = (h + (i*i)) % cap;

            //If Cell is empty, the string isn't there
            if (arr[loc].state == State::empty) {
                return;
            //If Cell is filled, check if it is the one we are looking for
            } else if (arr[loc].state == State::filled){
                if (s == arr[loc].val) {
                    arr[loc].state = State::removed;
                    sz--;
                    return;
                }
            //If Cell is removed, move on
            } else if ( arr[loc].state == State::removed){

            }
        }
    }     

    //Resize the array if the load factor is more than 0.5
    void resize() {

        //Get the next prime after the capacity is doubled
        long int prime = nextPrime(cap*2);
        
        int oldCap = cap;
        sz = 0;
        //Change the capacity to new prime number
        cap = prime;
        //Create a new array
        Cell* newArr = new Cell[cap];

        //Initialize the new array
        for (int i = 0; i < cap; i++) {
            newArr[i] = Cell{"", State::empty};
        }

        //Go through the old array and rehash all the values into the new array
        for (int i = 0; i < oldCap; i++) {
            if (arr[i].state == State::filled) {
                string value = arr[i].val;
                put(value, newArr);
            }
        }
        //Delete the old array and make the pointer point to the new array
        delete [] arr;
        arr = newArr;
    }

    // Check if a number is prime
    bool isPrime (long int n) {

        //Easy to check if it's 2 or 3
        if (n == 2 || n == 3) {
            return true;
        }

        //Check if it's one or divisible by 2
        if (n == 1 || n % 2 == 0){
            return false;
        }

        //Check until half of the value
        for (int i = 3; i <= n/2; i++) {
            //Check if n is divisible by something between 3 and n/2
            if (n % i == 0){
                return false;
            }
        }
        //If all test passed, it's a prime
        return true;
    }    

    //Calculate next prime
    long int nextPrime(long int n) {
        //If it is divisible by 2, try adding 1
        if (n % 2 == 0) {
            n++;
        }
        
        //Check if it is prime
        while (!isPrime( n )) {
            //Keep adding two, until it is prime
            n += 2;
        }
        return n;
    }

    //To be used later in the program. This was implemented here to make sure that class hides its implementation details
    //It takes in a string and calculates distance between it and every value of the hash table.
    void suggestion (const string& s1) {
        //Keep count of how many suggestions are output
        int count = 0;

        for (int i = 0; i < cap; i++) {

            if (arr[i].state == State::empty || arr[i].state == State::removed) {
            
            //If the Cell is filled, go ahead
            } else {
                //Let s2 be string at location i
                string s2 = arr[i].val;

                // Implementation of Levenshtein Distance Algorithm : Citations provided
                const int n(s2.size());

                //Create a new array with size
                int *costs = new int[n + 1];

                //Allocate values to each cell of array
                for (int k = 0; k <= n; k++) {
                    costs[k] = k;
                }

                int i = 0;

                //Iterating over the array using const_iterator
                for (std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i) {
                    costs[0] = i+1;
                    int corner = i;

                    int j = 0;
                    for (std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j) {
                        int upper = costs[j+1];

                        if (*it1 == *it2) {
                            costs[j+1] = corner;
                        } else {
                            int t(upper<corner?upper:corner);

                            costs[j+1] = (costs[j]<t?costs[j]:t) +1;
                        }
                        corner = upper;
                    }
                }

                //Setting the distance of the two words
                int result = costs[n];
                //Deleting new array
                delete [] costs;
                //If the words are within 2 distances apart, print it
                if (result <= 2 && result != 0) {
                    count ++;
                    cout << s2 << endl;
                }
                //If 8 strings are printed, stop
                if (count == 8) {
                    break;
                }

            }
            
        }
    }

    //Used for printing the hash table (Optional) : Cited
    void print_info() const {
        cout << "load_factor = " << size() << "/" << capacity() << " = " << load_factor() << "\n";
        
        for(int i = 0; i < cap; i++) {
            cout << "arr[" << i << "] = \"" << arr[i].val << "\" (";
            switch (arr[i].state) {
                case State::empty: cout << "empty"; break;
                case State::removed: cout << "removed"; break;
                case State::filled: cout << "filled"; break;
            } 
            cout << ")\n";
        } 
        cout << "load_factor = " << size() << "/" << capacity() << " = " << load_factor() << "\n";
    }

}; // class Hashtable

//Read the maindict.txt
Hashtable readMainFile () {
    //Use ifstream to read file
    ifstream infile;
    infile.open ("maindict.txt");
    string s;
    Hashtable table(5);

    //throw an error if the file is not found
    if (infile.fail()) {
        cmpt::error ("File can't be found");
    }

    //Take in words one at a time and input it into the hash table
    while (infile >> s) {
        table.put(s,table.array());
    }

    infile.close();

    //return the hash table
    return table;
}

//Read the addedwords.txt
//Same as previous file
Hashtable readAddedFile () {

    ifstream infile;
    infile.open ("addedwords.txt");
    string s;
    Hashtable table(5);

    if (infile.fail()) {
        cmpt::error ("File can't be found");
    }

    while (infile >> s) {
        
        table.put(s,table.array());
    }

    infile.close();
    return table;
}

//Function to check if a string exists in maindictionary or the addedwords file
void check(Hashtable& maindict, Hashtable& addwords, string& w) {

    //If found in either hashtables, print ok
    if (maindict.find(w)|| addwords.find(w)) {
        cout << "ok" << endl;
    //If not, say don't know the word
    } else {
        cout << "Don't know " << w << endl;
    }
}

//Function to add a string into the addedwords file
void add(Hashtable& maindict, Hashtable& addwords, string& w) {
    //Use ofstrea to add words into txt file
    ofstream outfile;
    //If it already exists in either file, don't add it in
    if (maindict.find(w) || addwords.find(w)) {
        cout << "The word already exists" << endl;
    //If the word doesn't exist, add it into addedwords hash table and then later add it to txt file
    } else {
        addwords.put(w, addwords.array());
        //Open the txt file, and then add it in using outfile
        outfile.open("addedwords.txt", ios_base::app);
        outfile << w << endl;
        cout << "Added " << w << endl;
    }
}

//Remove a string from addedwords hash table
void remove(Hashtable& maindict, Hashtable& addwords, string& w) {

    //Find if the word exists in the file, then remove it
    if (addwords.find(w)) {
        cout << "Deleteing " << w << endl;
        addwords.remove(w);
    
    //If the word is found in main dictionary, then say we can't delete it
    } else if (maindict.find(w)) {
        cout << "Can't remove " << w << ": it's in the main dictionary." << endl;

    } else {
        cout << "Can't remove " << w << ": the word doesn't exist." << endl;
    }
}

//Check if a character is a punctuation or not
bool punctuation (char& c) {

    if ((int(c) >= 33 && int(c) <= 64)|| (int(c) >= 91 && int(c) <= 96 ) || (int(c) >= 123 && int(c) <= 126 )) {
        return true;
    }

    return false;
}

//Check for unknown words in a given file
void checkfile(Hashtable& maindict, Hashtable& addwords, string& w) {
    
    ifstream infile;
    infile.open (w);
    string s;

    if (infile.fail()) {
        cout << "Can't find file " << w << endl;
    }

    //Take in one line at a time, to keep track of file's line numbers
    for (int count = 1; getline(infile,s); count ++) {
        //Use stringstream to separate out the words
        stringstream stream(s);

        while (stream >> s) {
            //Check if the first character of the word is a punctuation, then we discard it.
            if (punctuation(s[0])) {
            
            //If the first character is a letter, we continue to look into it
            } else {
                //If the last character is a punctuation: "something." or "go!"
                //Then we remove the last character: "something" or "go"
                if (punctuation(s[s.length()-1])) {
                    s.pop_back();
                }

                //Find if the word already exists, if not, then output it along with line number
                if ((maindict.find(s) || addwords.find(s))) {

                } else {
                    cout << s << " : line " << count << endl;
            
                }
            }    
        }
    }

    infile.close();
}

//Call the suggest method from the hash table
//Suggestions will only be found using the maindictionary
void suggest (Hashtable& maindict, string& s1) {

    maindict.suggestion(s1);
    
}


int main() {
    
    //Create two hash tables for each of the fles
    Hashtable maindict = readMainFile();
    Hashtable addwords = readAddedFile ();

    cout << "Welcome to SpellCheck Master Jr.!" << endl;
    string s;
    //An array of size two to store the first two words of the user's command
    string arr[2];
    

    //While the user doesn't ask to quit the program, run commands in a loop
    while (arr[0] != "quit" || arr[0] != "done" || arr[0] != "stop" || arr[0] != "quit" ) {
        
        cout << endl;
        cout << "Enter commands: check, add, remove, checkfile, suggest or quit " << endl;
        cout << " : " << endl;
        
        //Get string of user's command
        getline (cin, s);
        cout << endl;
        cout << "You said: " << s <<  " " << endl;

        int count = 0;
        //Use stringstream to separate out words from sentence
        stringstream stream(s);
        while (stream >> s) {
            //Store first two words into an array
            arr[count] = s;
            count++;

            //only care about the first two words
            if (count == 2) {
                break;
            }
        }

        //Record the command of the user as command and string
        string comm = arr[0];
        string str = arr[1];

        //Do as aske according to their command
        if (comm == "check") {
            check(maindict,addwords,str);

        } else if (comm == "add") {
            add(maindict, addwords,str);

        } else if (comm == "remove") {
            remove(maindict, addwords,str);

        } else if (comm == "checkfile"){
            checkfile(maindict, addwords, str);

        } else if (comm == "suggest") {
            suggest(maindict, str);

        } else if (comm == "quit" ||comm == "done" ||comm == "stop" || comm == "end") {
            cout << "Done. Bye" << endl;
            break;
            
        } else {
            cout << "Don't know command" << endl;
        }
    }
} // main



/*  CITATIONS

- Hashtable: A huge portion is taken from Toby's notes posted on the class website

    Exactly copied: enum class, Cell Struct, constructor, destructor, size, capacity, load factor, print_info
    Got a lot of influence from Toby's notes for (although I rewrote them myself): put, find, remove

- Hash function: Used polynomial hashing, inspired by this website

    https://sunilsavanur.wordpress.com/2012/08/14/polynomial-hash-function-for-dictionary-words/

- isPrime and nextPrime functions were inspired by following websites:

    https://stackoverflow.com/questions/30052316/find-next-prime-number-algorithm
    https://gist.github.com/alabombarda/f3944cd68dda390d25cb

- Suggestion method: Used Levenshtein distance algorithm. Copied the algorithm directly from following website
    
    https://rosettacode.org/wiki/Levenshtein_distance#C.2B.2B

- Punctuation function: got the idea for using ASCII from following website

    https://www.experts-exchange.com/questions/22882996/read-a-file-into-an-array-and-remove-punctuation-while-changing-everything-to-lowercase-in-c.html
    http://www.asciitable.com/

- add function: using ofstream to add words into a file. Used ios_base::app as suggested in following website
    
    https://www.geeksforgeeks.org/cpp-program-to-append-content-of-one-text-file-to-another/

- Checkfile function: got the idea for the for loop (to count the line number) from the following website
    
    http://www.cplusplus.com/forum/beginner/127905/

*/


