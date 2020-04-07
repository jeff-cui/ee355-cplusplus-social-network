#include "contact.h" 
// TODO: Add needed libraries! 

Email::Email(string type, string email_addr){
    // TODO: Complete me!
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    cout << "Enter email address: ";
    // some code here
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    // emaple: Email (USC): tommytrojan@usc.edu
    if (style=="full")
	    return "Email (" + type + "): " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
    // TODO: It is possible that num includes "-" or not, manage it! 222-444-7898
    // TODO: Complete this method!

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand why?
    long int area_code = atoi(num.substr(0, 3).c_str());
    long int  number = atoi(num.substr(3).c_str()); 
    this->phone_num = area_code*10000000 + number; 
    */
}


void Phone::set_contact(){
    // TODO: Complete this method
    // Use the same prompts as given!
	cout <<"Enter the type of phone number: ";
	cout << "Enter the phone number: ";
}


string Phone::get_contact(string style){
    // TODO: Complete this method, get hint from Email 
    // follow the format of this example: Phone (Office): 310-192-2847

    /* Note: Modify the following code can help you implementing this function
     * This code has a bug, can you understand it？
    int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
    */ 
}


void Phone::print(){
    // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


