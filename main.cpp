#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <string_view>
#include <cctype>
 


using namespace std;

int main(int argc, char *argv[]){

    ifstream fileInput;
    ifstream keyInput;
    ofstream fileOutput;

    int state = 0;
    for(int i = 1; i < argc; ){
        cout << argv[i] << endl;
        if(state == 0){
            if(argv[i] == "-i"){
                state = 1;
            } else if(argv[i] == "-o"){
                state = 2;
            } else if(argv[i] == "-k"){
                state = 3;
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
    copy_if((istreambuf_iterator<char>(fileInput)), std::istreambuf_iterator<char>(), back_inserter(fileInput), [](auto c){
        if
    });
    // string message((istreambuf_iterator<char>(fileInput)), std::istreambuf_iterator<char>());
    // message.erase(remove_if(message.begin(), message.end(), [](char c){
    //     return !isalpha(c);
    // }));
    // transform(message.begin(), message.end(), back_inserter(message), [](char))
    // string key((istreambuf_iterator<char>(keyInput)), std::istreambuf_iterator<char>());


    return 0;
}