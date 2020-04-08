

#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h> // directory+entry
using namespace std;

int main(){
    
    DIR *dir;
    struct dirent *ent;
    char targetFolderAddr[] = "./";
    if ((dir = opendir ("./")) != NULL) {
       /* Note: You may ask "what is dir here in this code"? 
        * You have two options (as an engineer): 
        * 1. Spend a lot of time reading about dirent.h, exploring stackoverflow pages and make test cases, you will learn something, but does it worth the time? Specially when you may forget about it till the next time you actually need to know about it. 
        * 2. Just use it to solve your problem, maybe a small test to understand its potentiallity. So next time when you design something you know this functionality exists. Of course, each option has its advantages and disadvatanges. 
        * And remember, you have a deadline for this PA!
       */ 
          while ((ent = readdir (dir)) != NULL) {
              string file_name = ent->d_name;

              for (int i = 0; i < file_name.size(); i++) {
                if (file_name[i] == '.') {
                  if (file_name[i+1] == 'd' && file_name[i+2] == 'b') {
                    cout << file_name << endl;
                  }
                }
              }
              
              //cout << ent->d_name << endl;
          }
          closedir (dir);
    } else {
          /* could not open directory */
          perror ("No directory!");
          return 1;
    }

    return 0;
}
