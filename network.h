
#ifndef NETWORK_H
#define NETWORK_H

#include "person.h"
#include "date.h"
// You may need to add more libraries 
#include <stdlib.h>
#include <list>
class Network{

    private:
        // head pointed to the first element (node) of the linked list
        Person* head;
        // tail pointed to the last element (node) of the linked list
        Person* tail;
        int count; 
        Person* search(string fname, string lname, string bdate);

        // phase 2
        Person* search(string queryid);

    public:
        Network();
        Network(string fileName);
        ~Network();
        void push_front(Person* newEntry);
        void push_back(Person* newEntry);
        bool remove(string fname, string lname, string bdate);
        void saveDB(string filename);
        void loadDB(string filename);
        void printDB();
        void showMenu();

        // Phase 2
        void friends_recommendation(int k);
};

#endif
