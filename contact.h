#ifndef CONTACT_H
#define CONTACT_H

#include <iostream>
#include <string>
#include <sstream>
// TODO: You may need to add other libraries here!
using namespace std;


class Contact {
//TODO: protected or private
protected:
	string type;
public:
    // the following functions are pure virtual functions
	virtual void print() = 0;
    virtual string get_contact(string style="full") = 0;
	virtual void set_contact() = 0;
};


class Email: public Contact{
private:
    string email_addr;
public:
    Email(string type, string email_addr);
    // TODO: Complete me!
    string get_contact(string style = "full");
    void print();
    void set_contact();

};


class Phone: public Contact{
private:
	string phone_num; 
public:
    Phone(string type, string phone_number);
    // TODO: Complete me!
    string get_contact(string style = "full");
    void print();
    void set_contact();
};

#endif
