#include <iostream>
#include <vector>

using namespace std;

// выводит вектор на стандартный вывод
void printVector(vector< int > vrr){
    for(int i = 0; i < vrr.size(); i++){
        cout << vrr[i];
    }
    cout << '\n';
}

// Возвращает остаток от деления
vector<int> getMood(vector< int > message, vector< int > polynom){
    int l = 0;
    int r = polynom.size() - 1;
    string prob = " ";
    while(r < message.size()){
        if(message[l] == 1){
            for(int i = 0; i < polynom.size(); i++){
                message[i + l] = (message[l + i] ^ polynom[i]);
            }
        }
        else {
            prob += " ";
            l++;
            r++;
        }
    }
    vector< int > ans;
    for(int i = l; i < r; i++){
        ans.push_back(message[i]);
    }
    return ans;
}

// кодирует сообщение
vector<int> codeMessage(vector<int> message, vector<int> polynom, int checkNum){
    int infoBitsStartPosition = message.size();
    for(int i = 1; i <= checkNum; i++){
        message.push_back(0);
    }

    vector< int > divMood = getMood(message, polynom);
    for(int i = 0; i < divMood.size(); i++){
        message[infoBitsStartPosition + i] = divMood[i];
    }
    return message;
}

// декодирует сообщение
vector<int> decodeMessage(vector< int > message, vector< int > polynom, int checkNum){
    int arr[] = {0, 0, 1, 4, 2, 8, 5, 10, 3, 14, 9, 7, 6, 13, 11, 12};
    vector< int > divMod = getMood(message, polynom);
    int errorId = 0;
    for(int i = 0; i < divMod.size(); i++){
        errorId = (errorId << 1) + divMod[i];
    }
    if(errorId != 0){
        errorId = message.size() - arr[errorId] - 1;
        cout << " was error in position = " << errorId;
        message[errorId] = !message[errorId];
    }
    else {
        cout << " No error ! ";
    }
    return message;
}

// переводит строку из 0 и 1 -> в вектор из 0 и 1
vector< int > strToBiVector(string str){
    vector< int > result;
    for(int i = 0; i < str.size(); i++){
        result.push_back(int(str[i]) - int('0'));
    }
    return result;
}

int main() {
    cout << " get message : ";
    string message;
    cin >> message;

    cout << " get polynom : ";
    string polynom;
    cin >> polynom;

    cout << " get number of info bits : ";
    int infoBitsNum;
    cin >> infoBitsNum;

    cout << " coded message = ";
    printVector(codeMessage(strToBiVector(message), strToBiVector(polynom), infoBitsNum));

    while(true) {
        cout << " get reseived message = ";
        string reseivMessage;
        cin >> reseivMessage;

        vector<int > resultVector = decodeMessage(strToBiVector(reseivMessage), strToBiVector(polynom), infoBitsNum);
        cout << "\n      decoded message = ";
        printVector(resultVector);
        cout << '\n';
    }

    return 0;
}

/**
01101011011
 10011
01101011011 0000
 */
