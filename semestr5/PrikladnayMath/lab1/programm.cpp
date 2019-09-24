#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <zconf.h>
#include <algorithm>

using namespace std;
const int characterTypesNumber = 50;
int charactersNumber = 0;
int frequency[characterTypesNumber];
int pairFrequency[characterTypesNumber][characterTypesNumber];

int getCharacterId(char e){
    if(e == ' ')
        return 0;
    else if((e == '!') || (e == '"') || (e == '\'') || (e == '(') || (e == ')') || (e == '*')
        || (e == ',') || (e == '-') || (e == '.') || (e == ':') || (e == ';') || (e == '?'))
        return 1;
    else if(('a' <= e) && (e <= 'z'))
        return 2 + int(e) - int('a');
    else if(('A' <= e) && (e <= 'Z'))
        return 2 + int(e) - int('A');
    else if(('0' <= e) && (e <= '9')){
        return 2 + 26 + int(e) - int('0');
    }
}

void printCharacterById(int id){
    if(id == 0) cout <<  " ";
    else if(id == 1) cout << ".";
    else if(id <= 27) cout << char(id - 2 + int('a'));
    else cout << char(id -28 + int('0'));
}

void calcFrequencies(const string& fileName){
    fill(frequency, frequency + characterTypesNumber, 0);
    for(int i = 0; i < characterTypesNumber; i++){
        fill(pairFrequency[i], pairFrequency[i] + characterTypesNumber, 0);
    }
    ifstream fileReader;
    fileReader.open(fileName);
    string fileRow;
    while(getline(fileReader, fileRow)){
        charactersNumber += fileRow.size();
        for(int i = 0; i < fileRow.size(); i++){
            int characterId = getCharacterId(fileRow[i]);
            frequency[characterId]++;
            if(i > 0){
                pairFrequency[getCharacterId(fileRow[i - 1])][characterId]++;
            }
        }
    }
    fileReader.close();
}

double calcEntropy(){
    double globalEntropy = 0.0;
    for(int i = 0; i < characterTypesNumber; i++){
        if(frequency[i] > 0){
            double probabilityy = (1.0 * frequency[i]) / (1.0 * charactersNumber);
            double characterEntropy = probabilityy * (log(probabilityy) / log(2.0));
            globalEntropy -= characterEntropy;

            cout << " symbol '";
            printCharacterById(i);
            cout << fixed << setprecision(5) << "' "
                 << "    probability : " << probabilityy
                 << "    Entropy : " << characterEntropy << '\n';
        }
    }
    return globalEntropy;
}

double calcPairEntropy(){
    double globalEntropy = 0.0;
    for(int i = 0; i < characterTypesNumber; i++){
        double probability = (1.0 * frequency[i]) / (1.0 * charactersNumber);
        if(frequency[i] > 0) {
            for (int j = 0; j < characterTypesNumber; j++) {
                if (pairFrequency[i][j] > 0) {
                    double pairProbability = (1.0 * pairFrequency[i][j]) / (1.0 * (charactersNumber - 1));
                    double pairEntropy = pairProbability * (log(pairProbability) / log(2.0));
                    globalEntropy -= probability * pairEntropy;

                    cout << " pair '";
                    printCharacterById(i);
                    printCharacterById(j);
                    cout << "' " << fixed << setprecision(5)
                         << "    pairProbability : " << pairProbability
                         << "    pairEntropy : " << pairEntropy << '\n';
                }
            }
        }
    }
    return globalEntropy;
}

bool fileExists (const char *fname){
    return access(fname,0) != -1;
}

int main() {
    string fileName;
    cout << " Enter the file name : ";
    cin >> fileName;
    if(fileExists(fileName.data())) {
        calcFrequencies(fileName);
        double globalEntropy = calcEntropy();
        cout << fixed << setprecision(6) << " global entropy = " << globalEntropy << "\n\n";
        double globalPairEntropy = calcPairEntropy();
        cout << fixed << setprecision(6) << " global pair entropy = " << globalPairEntropy << '\n';
    }
    else {
        cout << " file not exist \n";
    }
    return 0;
}
