
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
}

Network::~Network(){
    // TODO: Complete this method
    // Destructure delete all the Person
}


void Network::push_front(Person* newEntry){
    // Adds a new Person (newEntry) to the front of LL
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Person* newEntry){
    // TODO: Complete this method!
    // Adds a new Person (newEntry) to the back of LL
}


void Network::printDB(){
    // Don't change this method
    // Note: Notice that we don't need to update this even after adding to Person attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of persons: " << count << endl;
    cout << "------------------------------" << endl;
    Person* ptr = head;
    while(ptr != NULL){
        ptr->print_person();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
    // TODO: Complete this method!
    // Saves the netwrok in file <filename>
    // Note: The format of the output file is very abstract, just raw data
    // Look at studentDB.db as a template
    // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, 
    // now the one who is responsible for implementing Network should be aware of implementation of Person, not good! You will fix this in PA2. 
}


void Network::loadDB(string filename){
    // TODO: Complete this method!
    // Loads the netwrok from file <filename>
    // The format of the input file is similar to saveDB
    // Look at network studentDB.txt as a template
    // Phone number can be with dashes or without them
    // You need to use the following constructor of the Person class, Person::Person(fname, lname, bdate, email, phone)
    
    Person* ptr = head;
    while(head != NULL){
        ptr = head->next;
        delete head;
        head = ptr;
        count--;
    }
    head = NULL;
    tail = NULL;
    ifstream infile;
    infile.open(filename.c_str());
    string buff, fname, lname, bdate;
    
    // TODO: Decalre other vairiable if needed

    while(getline(infile, buff)){
        lname = buff.substr(0, buff.find(','));
        fname = buff.substr(buff.find(',')+2);
        getline(infile, bdate);
        // TODO: read email and phone
        
        // this line is to read the dash line
        getline(infile, buff);
        // TODO: use the constructor Person::Person(fname, lname, bdate, email, phone) to modify the following line
        Person* newEntry = NULL;
        
        this->push_back(newEntry);
    }
}

Person* Network::search(string fname, string lname, string bdate){
    // TODO: Complete this method!
    // Search the Network for the given fname, lname, bdate
    // You may create a new person, say searchEntry, with fname, lname and bdate. Think about what Person constructor will be helpful with these arguments.
    // And use == overloaded operator between two persons
    // if found, returns a pointer to it, else returns NULL
    // Don't forget to delete allocated memory.
}

bool Network::remove(string fname, string lname, string bdate){
    // TODO: Complete this method! Follow these steps:
    // Create a new person with the the give arguments as you do in search
    // Search if this person exists using search method. If it does not exist just return false! Else, remove the person from LL, make the other connections connected
    // Don't forget to delete allocated memory, change count and returning values!

}

void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!

    int opt;
    while(1){
        cout << "\033[2J\033[1;1H";
        printMe("banner"); // from misc library

        cout << "Select from below: \n";
        cout << "1. Load network database \n";
        cout << "2. Save network database \n";
        cout << "3. Add a new person \n";
        cout << "4. Search \n";
        cout << "5. Remove a person \n";
        cout << "6. Print database \n";
        
        cout << "\nSelect an option ... ";
        
        if (cin >> opt) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Wrong option! " << endl;
            return;
        }
        
        // You may need these variables! Add more if you want!
        string fname, lname, fileName, bdate;
        cout << "\033[2J\033[1;1H";

        if (opt==1){
            // TODO: Complete me!
            cout << "Loading network database \n";
            // TODO: print all the files in this same directory that have ".db" format
            // Take a look into sample_files.cpp 
            cout << "Enter the name of the load file: "; 
            // If file with name FILENAME does not exist: 
            cout << "File FILENAME does not exist!" << endl;
            // If file is loaded successfully, also print the count of persons in it: 
            cout << "Network loaded from " << fileName << " with " << count << " persons \n";
            
        }
        else if (opt==2){
            // TODO: Complete me!
            cout << "Saving network database \n";
            cout << "Enter the name of the save file: ";
            cout << "Network saved in " << fileName << endl;
        }
        else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new person ONLY if it does not exists!
            cout << "Adding a new person \n";
        }
        else if (opt == 4){
            // TODO: Complete me!
            cout << "Searching: \n";
            cout << "First Name: ";
            cout << "Last Name: ";
            cout << "Birthdate (M/D/YYYY): ";
            // if found: print person's firstname, lastname, bdate, email, phone using print_person()
            // if not, cout << "Not found! \n";
        }
        else if (opt==5){
            // TODO: Complete me!
            cout << "Removing a person \n";
            cout << "First name: ";
            cout << "Last name: ";
            cout << "Birthdate (M/D/YYYY): ";
            // if found, cout << "Remove Successful! \n";
            // if not found: cout << "Person not found! \n";
        }
        else if (opt==6){
            // TODO: Complete me!
            cout << "Network Database: \n";
            printDB();
        }
        else
            cout << "Nothing matched!\n";
        
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "\n\nPress Enter key to go back to main menu ... ";
        string temp;
        std::getline (std::cin, temp);
        cout << "\033[2J\033[1;1H";
    }
}


