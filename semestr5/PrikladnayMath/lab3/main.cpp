#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

int fileCharactersNumber = 0;
map<char, int > characterFrequency;
map<char, int > characterId;
vector< char > characters;
double eps = 0.00000000001;
double MX = 1.0;
int FIXED_SZ = 20;
int blokSize = 5;
int bigSize = 0;
char convertChar(char e){
    switch (e){
        case ' ':
        case '"':
        case '\'':
        case '(':
        case ')':
        case '*':
        case ',':
        case '-':
        case '!':
        case ':':
        case ';':
        case '?':
        case '.':
            return '.';
    }
    return e;
}

/**
 * Создаём новый файл из исходного, в котором заменяем некоторые специфические символы на .
 * @param fileName
 */
void createFixedFileFromGiven(string givenFileName, string fixedFileName){
    ifstream fileReader;
    ofstream filePrinter;
    fileReader.open(givenFileName);
    filePrinter.open(fixedFileName);
    string givenFileRow;
    while(getline(fileReader, givenFileRow)){
        string fixedRow = givenFileRow;
        for(int i = 0; i < fixedRow.size(); i++){
            fixedRow[i] = convertChar(fixedRow[i]);
        }
        filePrinter << fixedRow << '\n';
    }
}

void calcFrequency(const string fileName){ // подсчёт количества повторений символов
    ifstream fileReader;
    fileReader.open(fileName);
    string fileRow;
    while(getline(fileReader, fileRow)){
        fileCharactersNumber += fileRow.size();
        for(int i = 0; i < fileRow.size(); i++){
            characterFrequency[convertChar(fileRow[i])]++;
        }
    }
    int id = 0;
    for(auto a : characterFrequency){
        characters.push_back(a.first);
        characterId[a.first] = id;
        id++;
    }
}

/**
 * retunr 1 - if files are equal
 *        0 - if files are not equal
 *        2 - if some error with file1
 *        3 - if some error with file2
 * @param fileName1
 * @param fileName2
 * @return
 */
int fileComparator(string fileName1, string fileName2){
    ifstream fileReader1, fileReader2;
    fileReader1.open(fileName1);
    fileReader2.open(fileName2);
    if(!fileReader1.is_open()){
        return 2;
    }
    if(!fileReader2.is_open()){
        return 3;
    }
    string fileRow1, fileRow2;
    while(getline(fileReader1, fileRow1)){
        if(getline(fileReader2, fileRow2)){
            if(fileRow1 != fileRow2){
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    if(getline(fileReader2, fileRow1)){
        return 0;
    }
    else {
        return 1;
    }
}

void zipper(string inputfileName, string outputFileName){
    ifstream inputReader;
    ofstream outputWriter;
    inputReader.open(inputfileName);
    outputWriter.open(outputFileName);
    double Qbabilitys[characters.size() + 1];
    Qbabilitys[0] = 0;
    outputWriter << characters.size() << ' ';
    for(int i = 0; i < characters.size(); i++){
        Qbabilitys[i + 1] = Qbabilitys[i] + (characterFrequency[characters[i]] * 1.0 ) / (1.0 * fileCharactersNumber);
        outputWriter << fixed << setprecision(FIXED_SZ) << characters[i] << " " << Qbabilitys[i + 1] - Qbabilitys[i] << '\n';
    }
    if((inputReader.is_open()) && (outputWriter.is_open())){
        string inputRow;
        while(getline(inputReader, inputRow)){
            double left = 0.0;
            double right = MX;
            int strLen = 0;
            for(int i = 0; i < inputRow.size(); i++){
                double len = right - left;
                //cout << fixed << setprecision(9) << "  ::::: left = " << left << " right = " << right << " len = " << len << '\n';
                int id = characterId[inputRow[i]] + 1;
                right = left + (Qbabilitys[id] * len);
                left = left + Qbabilitys[id - 1] * len;
                //cout << " Qubability(id-1) = " << Qbabilitys[id-1] << " " << " Qubability(id) = " << Qbabilitys[id];
                //cout << " zipping e = " << inputRow[i] << fixed << setprecision(9) << "  left = " << left << " right = " << right << '\n';
                //cout << " :::::: \n\n";
                strLen++;
                if(strLen == blokSize){
                    bigSize += sizeof(left);
                    outputWriter << blokSize << " 2 ";
                    outputWriter << fixed << setprecision(FIXED_SZ) << left << '\n';
                    strLen = 0;
                    left = 0.0;
                    right = MX;
                }
            }
            bigSize += sizeof(left);
            outputWriter << strLen << " 1 ";
            outputWriter << fixed << setprecision(FIXED_SZ) << left << '\n';
        }
    }
    inputReader.close();
    outputWriter.close();
}

void unZipper(string inputFileName, string outputFileName){
    ifstream inputReader;
    ofstream outputWriter;
    inputReader.open(inputFileName);
    outputWriter.open(outputFileName);
    int n;
    inputReader >> n;
    double Qubability[n + 1];
    char characterById[n + 1];
    Qubability[0] = 0.0;
    for(int i = 1; i <= n; i++){
        inputReader >> characterById[i] >> Qubability[i];
        Qubability[i] += Qubability[i - 1];
    }
    int stringLen;
    while(inputReader >> stringLen){
        double left = 0.0;
        double right = MX;
        double code;
        int devTupe;
        inputReader >> devTupe >> code;
        string resultStr = "";
        //cout << " code = " << fixed << setprecision(40) << code << '\n';
        for(int i = 1; i <= stringLen; i++){
            double len = right - left;
            //cout << fixed << setprecision(9)  << " left = " << left << " rigth = " << right << " len = << " << len << '\n';
            for(int j = 1; j <= n; j++){
                double left1 = left + Qubability[j - 1] * len;
                double right1 = left + Qubability[j] * len;
                //cout << " j = " << j << " " << characterById[j] << "  l1 = " << fixed << setprecision(9) << left1 << " r1 = " << right1  << "   Qubabbi j-1 : " << Qubability[j-1] << "   Qubabbi j : " << Qubability[j] << '\n';
                if((left1 <= code) && (code < right1)){
                    resultStr += characterById[j];
                    left = left1;
                    right = right1;
                    break;
                }
            }
            //cout << " i = " << i << " str = " << resultStr << " l:r = " << left << " " << right << '\n';
            //cout << " ------------------------- " << '\n' << '\n';
        }
        outputWriter << resultStr;
        if(devTupe == 1) outputWriter << "\n";
    }
    inputReader.close();
    outputWriter.close();

}

double calcEntropy(){
    double globalEntropy = 0.0;
    //cout << " sz = " << characters.size() << '\n';
    for(int i = 0; i < characters.size(); i++){
        char e = characters[i];
        if(characterFrequency[e] > 0){
            double probabilityy = (1.0 * characterFrequency[e]) / (1.0 * fileCharactersNumber);
            //cout << fixed << setprecision(9) << " probab = " << probabilityy;
            double characterEntropy = -((log(probabilityy) / log(2.0)));
            globalEntropy += probabilityy * characterEntropy;
        }
    }
    return (globalEntropy * (1. * fileCharactersNumber));
}

int main() {
    std::cout << "Привет Всем!" << std::endl;

    string originFileName;
    cin >> originFileName;
    string buffFile = "buffFule.txt";
    string zippedFileName = "zippa.txt";
    string unZippedFileName = "unZippa.txt";

    createFixedFileFromGiven(originFileName, buffFile);
    calcFrequency(buffFile);
    zipper(buffFile, zippedFileName);
    cout << " Размер архивированной полезной информации = " << bigSize << '\n';
    cout << fixed << setprecision(FIXED_SZ) << " Коэффициент сжатия : " << calcEntropy()  / bigSize << '\n';
    unZipper(zippedFileName, unZippedFileName);

    if(fileComparator(buffFile, unZippedFileName) == 1){
        cout << "оригинальный файл - совпадает с результатом деархивации";
    }
    else {
        cout << "оригинальный файл - НЕ совпадает с результатом деархивации";
    }
    return 0;
}
