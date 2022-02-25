#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <string_view>
#include <cctype>
#include <cstring>
 
using namespace std;

void vigenere(string& message, string& key, int (*cript)(int, int)){
    int messageSize = message.size();
    int keySize = key.size();
    
    for(int i = 0, j = 0; i < messageSize; i++){

        int k = j % keySize;
        // j++;

        if(!isalpha(message[i])){
            continue;
        }
        
        j++;

        bool isUpper = isupper(message[i]) != 0;

        if(isUpper){
            message[i] = tolower(message[i]);
        }
 
        message[i] = cript(message[i], key[k]);

        if(isUpper){
            message[i] = toupper(message[i]);
        }
    }
}

int encript(int character, int key){
    return (character - 'a' + key - 'a') % 26 + 'a';
}

int decript(int character, int key){
    // return (character - 'a' - key + 'a') % 26 + 'a';
    return (character - key) % 26 + 'a';
}

int main(int argc, char *argv[]){

    ifstream fileInput;
    ifstream keyInput;
    ofstream fileOutput;
    bool hasEncript = true;
    bool hasDencript = false;
    bool hasOutput = false;

    int state = 0;
    for(int i = 1; i < argc; i++){
        // cout << argv[i] << endl;
        if(state == 0){
            if(strcmp(argv[i], "-i") == 0){
                state = 1;
            } else if(strcmp(argv[i], "-o") == 0){
                state = 2;
            } else if(strcmp(argv[i], "-k") == 0){
                state = 3;
            } else if(strcmp(argv[i], "-e") == 0){
                state = 0;
                hasEncript = true;
                hasDencript = false;
            } else if(strcmp(argv[i], "-d") == 0){
                state = 0;
                hasEncript = false;
                hasDencript = true;
            }
        } else if(state == 1){
            fileInput.open(argv[i]);
            if(!fileInput.is_open()){
                cout << "Nao foi possível abrir o arquivo!\n";
                exit(1);
            }
            state = 0;
        } else if(state == 2){
            fileOutput.open(argv[i]);
            if(!fileOutput.is_open()){
                cout << "Nao foi possível abrir o arquivo!\n";
                exit(1);
            } else{
                hasOutput = true;
            }
            state = 0;
        } else if(state == 3){
            keyInput.open(argv[i]);
            if(!keyInput.is_open()){
                cout << "Nao foi possível abrir o arquivo!\n";
                exit(1);
            }
            state = 0;
        }
    }


    string message;
    copy((istreambuf_iterator<char>(fileInput)), std::istreambuf_iterator<char>(), back_inserter(message));
    fileInput.close();
    
    string key;
    copy_if((istreambuf_iterator<char>(keyInput)), std::istreambuf_iterator<char>(), back_inserter(key), [](char c){
        return isalpha(c);
    });
    keyInput.close();
    transform(key.begin(), key.end(), key.begin(), ::tolower);

    if(hasEncript){
        vigenere(message, key, encript);
    }

    if(hasDencript){
        vigenere(message, key, decript);
    }

    if(hasOutput){
        fileOutput << message;
        fileOutput.close();
    } else{
        cout << message << "\n";
    }
    

    return 0;
}