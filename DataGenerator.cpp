using namespace std;

#include <iostream>
#include <unordered_set>
#include <random>
#include <fstream>
#include <chrono>
#include <thread>

const int azSize = 26;
const int nSize = 10;
const int allSize = 62;

const char AZ[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char az[] = "abcdefghijklmnopqrstuvwxyz";
const char n09[] = "0123456789";
const char all[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

const int strSize = 24;
const int aTotal = 100;
const int bTotal = 1000000;
const int cTotal = 5000000;
const string seta = "setA.txt";
const string setb = "setB.txt";
const string setc = "setC.txt";

const string exists = "found.txt";
const string exists_nein = "notFound.txt";

unordered_set<string> hs;

void CreateString(string &str){

    str[0] = AZ[rand() % azSize];
    str[1] = AZ[rand() % azSize];
    str[2] = AZ[rand() % azSize];
    str[3] = AZ[rand() % azSize];
    str[4] = '.';
    str[5] = all[rand() % allSize];
    str[6] = all[rand() % allSize];
    str[7] = all[rand() % allSize];
    str[8] = all[rand() % allSize];
    str[9] = '.';
    str[10] = n09[rand() % nSize];
    str[11] = n09[rand() % nSize];
    str[12] = n09[rand() % nSize];
    str[13] = n09[rand() % nSize];
    str[14] = n09[rand() % nSize];
    str[15] = '@';
    str[16] = all[rand() % allSize];
    str[17] = all[rand() % allSize];
    str[18] = all[rand() % allSize];
    str[19] = all[rand() % allSize];
    str[20] = '.';

    int r = rand() % 3;
    if (r == 0){
        str[21] = 'c';
        str[22] = 'o';
        str[23] = 'm';
        str[24] = '\n';
    }
    else if (r == 1){
        str[21] = 'o';
        str[22] = 'r';
        str[23] = 'g';
        str[24] = '\n';
    }
    else{
        str[21] = 'm';
        str[22] = 'y';
        str[23] = '\0';
        str[24] = '\n';
    }


}
void CreateStrings(string filename, int total, bool ignoreHs = false){

    ofstream file(filename);

    string str(strSize + 1, '*');

    int i = 0;
    for (; i < total; i++){
        CreateString(str);
        if (!ignoreHs){
            auto it = hs.find(str);
            if (it != hs.end()){
                i--;
                continue;
            }

            hs.insert(str);
        }
        file << str;
    }
    printf("Generated %d lines of data into %s\n", total, filename.c_str());

    file.close();
}


void checkFound(){

    ifstream infile(exists);
    string line;
    printf("\nChecking %s if all items can be found\n", exists.c_str());
    while (getline(infile, line)){
        auto it = hs.find(line);
        if (it != hs.end()){
            printf("%s Found (Intended)\n", line.c_str());
            continue;
        }
        printf("%s Not Found (Error!)\n", line.c_str());
    }
}
void checkNotFound(){

    ifstream infile(exists_nein);
    string line;
    printf("\nChecking %s if all items cannot be found\n", exists_nein.c_str());
    while (getline(infile, line)){
        auto it = hs.find(line);
        if (it != hs.end()){
            printf("%s Found (Error!)\n", line.c_str());
            continue;
        }
        printf("%s Not Found (Intended)\n", line.c_str());
    }

}

int main()
{

    srand(0);
    CreateStrings(seta, aTotal);
    hs.clear();
    srand(0);
    CreateStrings(setb, bTotal);
    hs.clear();
    srand(0);
    CreateStrings(setc, cTotal);
    hs.clear();


    ifstream stream(setc);
    string line;
    while (getline(stream, line)){
        hs.insert(line);
    }

    srand(0);
    CreateStrings(exists, 10, true);
    srand(time(0));
    CreateStrings(exists_nein, 10, true);

    checkFound();
    checkNotFound();


    return 0;
}

