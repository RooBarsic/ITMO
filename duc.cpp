#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
//#include <czconf>
#include <algorithm>
#include <map>
#include <deque>
#include <set>
#include <vector>
using namespace std;

int fileCharactersNumber = 0;         // обшее количество символов в файле
map<char, int > characterFrequency;   // тут храним количества повторений каждого символа
vector< char > characters;            // набор всех символов файла по одному разу
char convertChar(char e){
    switch (e){     // заменяем символы пробел, " ' \ ( ) * , - ! : ; ? . на '.' 
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
bool compareCharacters(char a, char b){  // функция для сравнения двух символов по количеству их встречаемости
    if(characterFrequency[a] < characterFrequency[b]) return 1;
    return 0;
}
void calcFrequency(const string fileName){ // подсчёт количества повторений символов
    ifstream fileReader;
    fileReader.open(fileName);                               // открываем файл для чтения
    string fileRow;
    while(getline(fileReader, fileRow)){                     // построчно читаем файл
        for(int i = 0; i < fileRow.size(); i++){             // пробегаемся по каждому символу строки 
            characterFrequency[convertChar(fileRow[i])]++;
        }
    }
    for(auto a : characterFrequency){          // набор всех символов файла по одному разу
        characters.push_back(a.first);
        fileCharactersNumber += a.second;      // вычисляем обшее количество символов в файле
    }

}
map< int, vector< pair< int, string > > > vrr;
map< int, string > nodeValById;
vector< pair< char, string > > xaffmanAnswer;
int buildXaffmanGraph(){  // Строит Дерево Хаффмана и возврашает номер корневой вершины
    int nodeId = 0;
    set< pair<int, int > > stt;
    for(auto a : characterFrequency){
        string str = "";
        str += a.first;
        nodeId++;
        nodeValById[nodeId] = str;
        stt.insert({a.second, nodeId});
    }
    string link = "http://mxwell.github.io/draw-graph/?q=digraph{";
    while(stt.size() > 1){
        pair< int, int > A = *(stt.begin());
        stt.erase(stt.begin());
        pair< int, int > B = *(stt.begin());
        stt.erase(stt.begin());

        nodeId++;
        nodeValById[nodeId] = nodeValById[A.second] + nodeValById[B.second];
        vrr[nodeId].push_back({A.second, "1"});
        vrr[nodeId].push_back({B.second, "0"});
        link += nodeValById[nodeId] + "->" + nodeValById[A.second] + "[label=\"1\"];";
        link += nodeValById[nodeId] + "->" + nodeValById[B.second] + "[label=\"0\"];";
        pair< int, int > AB;
        AB.first = A.first + B.first;
        AB.second = nodeId;
        stt.insert(AB);
    }

    link += "}#";
    cout << link << '\n';
    return nodeId;
}
void calcXaffmanCodes(int nodeId, string code){
    if(vrr[nodeId].size() == 0){
        xaffmanAnswer.push_back({nodeValById[nodeId][0], code});
    }
    else {
        calcXaffmanCodes(vrr[nodeId][0].first, code + vrr[nodeId][0].second);
        calcXaffmanCodes(vrr[nodeId][1].first, code + vrr[nodeId][1].second);
    }
}
void runXaffman(){   
    int rootId = buildXaffmanGraph();   // запускаем алгоритм построения графа кодов по Хаффману
    calcXaffmanCodes(rootId, "");       // вычисляем коды символов по Хаффману 
}


vector< pair< char, string > > shenonAnswer;
void findShenonCodes(vector< char > nodeState, string code, int globalSum){   // метод реализующий алгоритм поиска кодов Шеннона Фано
    if(nodeState.size() == 1){
        shenonAnswer.push_back({nodeState[0], code});
    }
    else if(nodeState.size() > 0){
        vector< char > left;
        int leftSum = 0;
        vector< char > right;
        int rightSum = 0;
        for(int i = nodeState.size() - 1; i >= 0; i--){
            if(leftSum < rightSum){
                left.push_back(nodeState[i]);
                leftSum += characterFrequency[nodeState[i]];
            }
            else {
                rightSum += characterFrequency[nodeState[i]];
                right.push_back(nodeState[i]);
            }
        }
        findShenonCodes(left, code + "1", leftSum);
        findShenonCodes(right, code + "0", rightSum);
    }
}
bool compareCharacter2(pair< char, string > left, pair< char, string > right){
    if(left.second.size() < right.second.size()) return 1;
    //if(characterFrequency[left.first] < characterFrequency[right.first]) return 1;
    return 0;
}
int main() {
    freopen("output.txt","w",stdout);
    calcFrequency("test.txt");  // вычисляем количество повторений каждого символа
    
    sort(characters.begin(), characters.end(), compareCharacters);   // сортируем символы по возрастанию их встречаемости
    findShenonCodes(characters, "", fileCharactersNumber);
    cout << " Shenon answer : " << '\n';
    sort(shenonAnswer.begin(), shenonAnswer.end(), compareCharacter2);
    double averageShenonLength = 0.0;  // средняя длина кодов по Шеннону Фано
    for(auto a : shenonAnswer){
        string code = a.second;        // код Шеннона Фанно для конкретного символа
        double probability = (1.0 * characterFrequency[a.first]) / (1.0 * fileCharactersNumber);   // вероятность появления конкретного символа
        averageShenonLength += (code.size() * 1.0) * probability;    
        cout << a.first << "\t" << characterFrequency[a.first] << "\t" << a.second << "\t" << a.second.size() << '\n';
    }
    cout << fixed << setprecision(7) << " averageShenonLength = " << averageShenonLength << '\n';
    
    runXaffman();
    cout << " \n\n Xaffman answer : " << " \n";
    sort(xaffmanAnswer.begin(), xaffmanAnswer.end(), compareCharacter2);
    double averageXaffmanLength = 0.0;    // средняя длина кодов по Хаффману
    for(auto a : xaffmanAnswer){
        string code = a.second;           // код Хаффмана для конкретного символа
        double probability = (1.0 * characterFrequency[a.first]) / (1.0 * fileCharactersNumber);   // вероятность появления конкретного символа
        averageXaffmanLength += (code.size() * 1.0) * probability;
        cout << a.first << "\t" << characterFrequency[a.first] << "\t" << a.second << "\t" << a.second.size() << '\n';
    }
    cout << fixed << setprecision(7) << " averageXaffmanLength = " << averageXaffmanLength << '\n';
    return 0;
}
