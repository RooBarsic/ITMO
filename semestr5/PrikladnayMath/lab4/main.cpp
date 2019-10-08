#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#define LENGTH_SYMBOl 8
#define n 12
#define info  8
#define control 4
//check if position a is control bit or not
bool exp(int a){
    switch (a){
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
            return true;
            break;
        default:
            return false;
    }

}
//receive a code ASCII of char, return the bin array of this char
string get_bit_char(int tmp){
    string bin_code="";
    int i =0;
    while (tmp>0){
        if (tmp%2==0) bin_code.insert(0,"0");
        else bin_code.insert(0,"1");
        tmp/=2;
        i++;
    }
    while(i<LENGTH_SYMBOl){
        i++;
        bin_code.insert(0,"0");
    }
    return bin_code;
}

//bin_code.length() <=12; so number of control bit <=4, find code_hamming of bin_code(bin_code is data code, not include control bit)
string process_char(string bin_code){
    string code_hamming="";
    int arr[info+1];
    for(int i=1;i<=info;i++) {
        arr[i] = int(bin_code.at(i-1))-48;
        //cout << arr[i] ;
    }
    int ct[5];
    ct[1] = (arr[1]+arr[2]+arr[4]+arr[5]+arr[7])%2;
    ct[2] = (arr[1]+arr[3]+arr[4]+arr[6]+arr[7])%2;
    ct[3] = (arr[2]+arr[3]+arr[4]+arr[8])%2;
    ct[4] = (arr[5]+arr[6]+arr[7]+arr[8])%2;
    int i=0,j=0;
    for(int k=0;k<n;k++){
        if (exp(k+1)){
            code_hamming.push_back(char(ct[++i]+48));
        }
        else{
            code_hamming.push_back(char(arr[++j]+48));
        }
    }

    return code_hamming;
}

//encode hamming of string, solve every char in string
void encode(string s){
    string result="";
    for(int i=0;i<s.length();i++){
        string tmp = get_bit_char(int(s.at(i)));
        result.append(process_char(tmp));
    }
    cout << result << endl;
}

//get xor of bits for control bit K(_exp)
int get_xor_code(int _exp, string _encode){
    int res = 0;
    int number = int(pow(2,_exp-1)); // number of bit in range check
    int start_pos = number-1;
    while (start_pos<_encode.length()){
        for(int i=0;i<number;i++){
            if (start_pos<_encode.length()) res+=int(_encode.at(start_pos))-48;
            start_pos++;
        }
        start_pos+=number;
        }
    return (res%2);
}

//receive the string bit of code, return char after decode
char convert_bin_to_char(string s){
    int res=0;
    int number = 0;
    int ch[s.length()];
    for(int i=0;i<s.length();i++){
        if (exp(i+1)) continue;
        ch[number++]=int(s.at(i))-48;
    }
    for(int i=0;i<number;i++) if (ch[i]) res+=int(pow(2,number-1-i));
    return char(res);
}

//check _encode is right or not, encode <=12 in some case
char decode(string _encode, int pos_string){
    int len_code = _encode.length();
    int _exp = 2;
    int nk = ceil(log2(len_code));
    int ni = len_code-nk;
    int error[nk+1];
    for(int i=1;i<=nk;i++){
        error[i] = get_xor_code(i,_encode);
    }
    int pos_error = 0;
    for(int i=1;i<=nk;i++){
        pos_error += error[i]==1 ? int(pow(2,i-1)) : 0;
    }
    if (pos_error==0) {
       // cout << "Code is right" << endl;
//       break;
    }
    else{
        cout << "Code is wrong at " <<  pos_string+pos_error-1 << endl;
        if (_encode.at(pos_error-1)=='1') _encode.replace(pos_error-1,1,"0");
        else _encode.replace(pos_error-1,1,"1");
        //cout << "Right code is " << _encode << endl;
    }
    return convert_bin_to_char(_encode);
}

//do decode of string
void check_decode(string s){
    if (s.length() <= n) {cout << decode(s,0)<<endl; return;}
    if (s.length() % 12 != 0) {
        cout << "The length of code must be multiples of 12";
        return;
    }
    int sl = s.length() / 12;
    string result="";
    for(int i =0;i<sl;i++){
        string tmp = s.substr(12*i,12);
        result.push_back(decode(tmp,12*i));
    }
    cout <<"Right data is " <<  result <<endl;
}

int main()
{

    string s;
    int x;
    while (true){
        cout << "what options do you want" << endl;
        cout << "1. Encode" << endl;
        cout << "2. Decode" << endl;
        cout << "3. Exit" << endl;
        cin >> x;
        switch (x){
            case 1:
                cout << "please input string, which you want to encode"<< endl;
                cin >> s;
                encode(s);
                break;
            case 2:
                cout << "please input string, which you want to decode" << endl;
                cin >> s;
                check_decode(s);
                break;
            case 3: return 0;
            default: break;
        }
    }

//    cout << convert_bin_to_char("100011010100");

    return 0;
}
