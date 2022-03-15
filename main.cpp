#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <string_view>
#include <cctype>
#include <cstring>
#include <map>
 
using namespace std;


// const vector<float> histogramaPort{0.1463, 0.0104, 0.0388, 0.0499, 0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040, 0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252, 0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167, 0.0001, 0.0021, 0.0001, 0.0047};
// const vector<float> histogramaEng{0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
const vector<float> histogramaPort{14.63, 01.04, 03.88, 04.99, 12.57, 01.02, 01.30, 01.28, 06.18, 00.40, 00.02, 02.78, 04.74, 05.05, 10.73, 02.52, 01.20, 06.53, 07.81, 04.34, 04.63, 01.67, 00.01, 00.21, 00.01, 00.47};
const vector<float> histogramaEng{08.167, 01.492, 02.782, 04.253, 12.702, 02.228, 02.015, 06.094, 06.966, 00.153, 00.772, 04.025, 02.406, 06.749, 07.507, 01.929, 00.095, 05.987, 06.327, 09.056, 02.758, 00.978, 02.360, 00.150, 01.974, 00.074};


void vigenere(string& message, string& key, int (*cript)(int, int), string &out){
    out = message;
    int messageSize = out.size();
    int keySize = key.size();
    
    for(int i = 0, j = 0; i < messageSize; i++){

        int k;
        do{
            k = j % keySize;
        } while(!isalpha(key[k]));
        // j++;

        if(!isalpha(out[i])){
            continue;
        }

        j++;

        bool isUpper = isupper(out[i]) != 0;

        if(isUpper){
            out[i] = tolower(out[i]);
        }
 
        out[i] = cript(out[i], key[k]);

        if(isUpper){
            out[i] = toupper(out[i]);
        }
    }
}

int encript(int character, int key){
    return (character - 'a' + key - 'a') % 26 + 'a';
}

int decript(int character, int key){
    // return (character - 'a' - key + 'a') % 26 + 'a';
    return ((character - key) % 26 + 26) % 26 + 'a';
}

void getOcorrencias(string &message, vector<pair<string, int>> &ocorrencias){
    
    vector<vector<int>> quandoOcorre;
    map<string, int> mapaQuandoOcorre;
    string str;
    string str2; 
    for(int i = 0; i < message.size(); i++){
        if(isalpha(message[i])){
            str.push_back(tolower(message[i]));
        }
    }
    for(int i = 0; i <= str.size()-3; i++){
        str2 = str.substr(i, 3);
        if(!mapaQuandoOcorre.count(str2)){
            mapaQuandoOcorre[str2] = quandoOcorre.size();
            quandoOcorre.emplace_back();
        }
        int ind = mapaQuandoOcorre[str2];
        for(int j = 0; j < quandoOcorre[ind].size(); j++){
            ocorrencias.emplace_back(str2, i - quandoOcorre[ind][j]);
        }
        quandoOcorre[ind].push_back(i);
    }
}

void getDivisores(int num, vector<int> &vet){
    for(int i = 1; i * i <= num; i++){
        if(num % i == 0){
            vet.push_back(i);
            int aux = num / i;
            if(aux != i){
                vet.push_back(aux);
            }
        }
    }
}

void calculaHistogramaPorCent(string& message, int ini, int keySize, vector<float> &out){
    out.resize(26);
    fill(out.begin(), out.end(), 0);
    int messageSize = message.size();
    int qtd = 0;
    
    for(int i = ini; i < messageSize; i += keySize){

        if(!isalpha(message[i])){
            i++;
            continue;
        }
        
        out[tolower(message[i]) - 'a']++;
        qtd++;
    }
    for(int i = 0; i < 26; i++){
        // out[i] *= 100/qtd;
        out[i] *= 100;
        out[i] /= qtd;
    }
}

char melhorLetra(const vector<float>& histograma1, const vector<float>& histograma2){
    float val = 0;
    char letra = 'a';
    for(int i = 0; i < 26; i++){
        float aux = 0;
        for(int j = 0; j < 26; j++){
            aux += histograma1[j] * histograma2[(j + i) % 26];
        }
        if(aux > val){
            val = aux;
            letra = 'a' + i;
        }
    }
    return letra;
    // float val = std::numeric_limits<float>::max();;
    // char letra = 'a';
    // for(int i = 0; i < 26; i++){
    //     float aux = 0;
    //     for(int j = 0; j < 26; j++){
    //         aux += abs(histograma1[j] - histograma2[(j + i) % 26]);
    //     }
    //     if(aux < val){
    //         val = aux;
    //         letra = 'a' + i;
    //     }
    // }
    // return letra;
}  

void melhorChave(string& message, int keySize, string &strOut, const vector<float>& histogramaEscolhido){
    
    strOut.resize(keySize);
    for(int i = 0; i < keySize; i++){

        vector<float> histogramaMsg;
        calculaHistogramaPorCent(message, i, keySize, histogramaMsg);
        strOut[i] = melhorLetra(histogramaEscolhido, histogramaMsg);
    }   
}
int main(int argc, char *argv[]){

    ifstream fileInput;
    ifstream keyInput;
    ofstream fileOutput;
    bool hasEncript = true;
    bool hasDencript = false;
    bool hasBreak = false;
    bool hasOutput = false;
    int state = 0;
    const vector<float> *hisogragaEcolhido = nullptr;

    for(int i = 1; i < argc; i++){
        // cout << argv[i] << endl;
        if(state == 0){
            if(strcmp(argv[i], "-i") == 0){
                state = 1;
            } else if(strcmp(argv[i], "-o") == 0){
                state = 2;
            } else if(strcmp(argv[i], "-k") == 0){
                state = 3;
            } else if(strcmp(argv[i], "-len") == 0){
                hisogragaEcolhido = &histogramaEng;
            } else if(strcmp(argv[i], "-lpt") == 0){
                hisogragaEcolhido = &histogramaPort;
            } else if(strcmp(argv[i], "-e") == 0){
                state = 0;
                hasEncript = true;
                hasDencript = false;
                hasBreak = false;
            } else if(strcmp(argv[i], "-d") == 0){
                state = 0;
                hasEncript = false;
                hasDencript = true;
                hasBreak = false;
            } else if(strcmp(argv[i], "-b") == 0){
                state = 0;
                hasEncript = false;
                hasDencript = false;
                hasBreak = true;
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
        vigenere(message, key, encript, message);
        
    }

    if(hasBreak){
        vector<pair<string, int>> ocorrencias;
        getOcorrencias(message, ocorrencias);
        string messageAlfa; 
        for(int i = 0; i < message.size(); i++){
            if(isalpha(message[i])){
                messageAlfa.push_back(tolower(message[i]));
            }
        }
        map<int, int> histogramaOcorrencias;
;

        for(int i = 0; i < ocorrencias.size(); i++){
            vector<int> divisores;
            getDivisores(ocorrencias[i].second, divisores);
            for(int j = 0; j < divisores.size(); j++){
                histogramaOcorrencias[divisores[j]]++;
            }
        }
        vector<pair<int, int>> sizes(histogramaOcorrencias.begin(), histogramaOcorrencias.end());
        sort(sizes.begin(), sizes.end(), [](pair<int, int> a, pair<int, int> b){
            if(a.second == b.second){
                return a.first < b.first;
            }
            return a.second > b.second;
        });
        string chave1;
        string chave2;
        int opcao1 = -1;
        while(opcao1 != 0){
            cout << "Melhores opções de tamanho de chave:";
            for(int i = 0; i < sizes.size(); i++){
                // cout << sizes[i].first << " " << sizes[i].second << "\n";
                cout << " " << sizes[i].first;
            }
            cout << "\n";
            cout << "Escolha o melhor tamanho, ou digite 0 para sair: ";
            cin >> opcao1;
            int opcao2 = -1;
            melhorChave(messageAlfa, opcao1, chave2, *hisogragaEcolhido);
            while(opcao2 != 0){
                cout << "Minha chave: " << chave2 << "\n";
                cout << "Digite o indice da string, 0 para sair, -1 para ver o texto decifrado: ";
                cin >> opcao2;
                if(opcao2 == 0){
                    opcao2 = 0;
                } else if(opcao2 == -1){
                    string msgOut;
                    vigenere(message, chave2, decript, msgOut);
                    cout << "A mensagem foi:\n";
                    cout << msgOut << "\n";
                } else{
                    int opcao3 = -1;
                    vector<int> histograma;
                    // calculaHistograma(messageAlfa, opcao2-1, opcao1, histograma); 
                    while(opcao3 != 0){
                        cout << "Digite 1 para shiftar para esquerda, 2 para shifitar para direita, e 0 para sair:\n";
                        cin >> opcao3;
                        if(opcao3 == 1){
                            chave2[opcao2-1] = (chave2[opcao2-1] - 'a' - 1 + 26) % 26 + 'a';
                        } else if(opcao3 == 2){
                            chave2[opcao2-1] = (chave2[opcao2-1] - 'a' + 1) % 26 + 'a';
                        }
                        cout << chave2 << "\n";
                    }
                }
            }

        }



    }


    if(hasDencript){
        vigenere(message, key, decript, message);
    }

    if(hasOutput){
        fileOutput << message;
        fileOutput.close();
    } else{
        cout << message << "\n";
    }
    

    return 0;
}