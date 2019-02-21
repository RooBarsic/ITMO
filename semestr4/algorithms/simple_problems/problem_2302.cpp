/// problem : 2302. (множества) Множество на массиве

#include <iostream>
#include <string>

#define MAXSETSIZE 100
#define DIGIT 0
#define COMMA 2
#define DEFIS 3
#define BLANK 4
#define OTHER 5

using namespace std;

//структура множества на массиве
struct SETINARRAY {
	int m[MAXSETSIZE]; // массив, хранящий элементы множества
	int n; // действительное число эл-тов в множестве
};

// Прототипы функций
void Union(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res); // Res = A union B
void Cross(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res);// Res = A cross B.
void Difference(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res); // Разность Res = A \ B.
short SymClass(char z); //Классификатор символов
int StringToIntArray(string &p, int *r); // разбор строки в массив целых чисел
string ArrayToString(int *p, int np); // для вывода

int main() { // Точка входа в программу
	SETINARRAY X, Y, Z;
	string s;
	cin >> s;
	X.n = StringToIntArray(s, X.m);
	cin >> s;
	Y.n = StringToIntArray(s, Y.m);

	Union(X, Y, Z);
	cout << ArrayToString(Z.m, Z.n);
	Cross(X, Y, Z);
	cout << "\n" + ArrayToString(Z.m, Z.n);
	Difference(X, Y, Z);
	cout << "\n" + ArrayToString(Z.m, Z.n);
	return 0;
}

void Union(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// НАПИШИТЕ САМИ
	// функция вычисляет объединение множеств a,b
	// результат помещается в *Res
	// предполагается что множества не содержат дубликатов
	int id_a = 0;  /// первый элемент множества А
	int id_b = 0;  /// первый элемент множества В
	Res.n = 0;
	while((id_a < A.n) && (id_b < B.n)){   /// пока в обоих множествах ещё остались не рассмотренные элементы
        if(A.m[id_a] == B.m[id_b]){        /// добавляем если A.m[id_a] == B.m[id_b]
            Res.m[Res.n] = A.m[id_a];
            Res.n++;
            id_a++;
            id_b++;
        }
        else if(A.m[id_a] < B.m[id_b]){     /// добавляем если A.m[id_a] < B.m[id_b]
            Res.m[Res.n] = A.m[id_a];
            id_a++;
            Res.n++;
        }
        else {
            Res.m[Res.n] = B.m[id_b];          /// добавляем если A.m[id_a] > B.m[id_b]
            id_b++;
            Res.n++;
        }
	}
    while(id_a < A.n){                 /// пока только в множестве А - остались не рассмотренные элементы -> добавим их в Res
        Res.m[Res.n] = A.m[id_a];
        id_a++;
        Res.n++;
    }
    while(id_b < B.n){                 /// пока только в множестве B - остались не рассмотренные элементы -> добавим их в Res
        Res.m[Res.n] = B.m[id_b];
        id_b++;
        Res.n++;
    }
}

void Cross(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// НАПИШИТЕ САМИ
	// функция вычисляет пересечение множеств a,b
	// результат помещается в *Res
    int id_a = 0;  /// первый элемент множества А
	int id_b = 0;  /// первый элемент множества В
	Res.n = 0;
	while((id_a < A.n) && (id_b < B.n)){   /// пока в обоих множествах ещё остались не рассмотренные элементы
        if(A.m[id_a] == B.m[id_b]){         /// добавляем если A.m[id_a] == B.m[id_b]
            Res.m[Res.n] = A.m[id_a];       /// остальные случаеи пропускаем
            Res.n++;
            id_a++;
            id_b++;
        }
        else if(A.m[id_a] < B.m[id_b]) id_a++;
        else id_b++;
	}
}

void Difference(SETINARRAY &A, SETINARRAY &B, SETINARRAY &Res) {
	// НАПИШИТЕ САМИ
	// функция вычисляет разность множеств a,b
	// результат помещается в *Res
	int id_a = 0;  /// первый элемент множества А
	int id_b = 0;  /// первый элемент множества В
	Res.n = 0;
	while((id_a < A.n) && (id_b < B.n)){   /// пока в обоих множествах ещё остались не рассмотренные элементы
        if(A.m[id_a] == B.m[id_b]){
            id_a++;
            id_b++;
        }
        else if(A.m[id_a] < B.m[id_b]){     /// добавляем если A.m[id_a] != B.m[id_b]
            Res.m[Res.n] = A.m[id_a];       /// остальные случаеи пропускаем
            id_a++;
            Res.n++;
        }
        else id_b++;
	}
    while(id_a < A.n){                 /// пока только в множестве А - остались не рассмотренные элементы -> добавим их в Res
        Res.m[Res.n] = A.m[id_a];
        id_a++;
        Res.n++;
    }
}

short SymClass(char z) {
	if (z >= '0' && z <= '9') {
		return DIGIT;
	}
	if (z == ',') {
		return COMMA;
	}
	if (z == '-') {
		return DEFIS;
	}
	if (z == ' ') {
		return BLANK;
	}
	return OTHER;
}

int StringToIntArray(string &p, int *r) {
	int k, p1 = -1, p2 = -1;
	char buf[20];
	short sClass;
	int i = 0; // номер символа набираемого числа
	int n = 0; // число страниц (текущая длина p)
	int LastPunkt = -1; // последний символ из DEFIS или COMMA
						// -1 значит никакого

	if (!p.size()) {
		return 0;
	}
	for (int j = 0; j < p.size(); j++) {
		sClass = SymClass(p[j]);
		switch (sClass) {
		case DIGIT:
			buf[i++] = p[j];
			break;
		case COMMA:
			buf[i] = '\0';
			if (LastPunkt == -1 || LastPunkt == COMMA) {
				p1 = atoi(buf);
				r[n++] = p1;
			}
			if (LastPunkt == DEFIS) {
				p2 = atoi(buf);
				if (p1 == -1 || p2 == -1) {
					return -1;
				}
				if (p2<p1) {
					return -1;
				}
				for (k = p1; k <= p2; k++) {
					r[n++] = k;
				}
				p1 = p2 = -1;
			}
			i = 0;
			LastPunkt = COMMA;
			break;
		case DEFIS:
			buf[i] = '\0';
			p1 = atoi(buf);
			p2 = -1;
			LastPunkt = DEFIS;
			i = 0;
			break;
		case BLANK:
			break;
		default:
			return -1;
		} // switch
	}
	buf[i] = '\0';
	if (LastPunkt == -1 || LastPunkt == COMMA) {
		p1 = atoi(buf);
		r[n++] = p1;
	}
	if (LastPunkt == DEFIS) {
		p2 = atoi(buf);
		if (p1 == -1 || p2 == -1) {
			return -1;
		}
		for (k = p1; k <= p2; k++) {
			r[n++] = k;
		}
	}
	// сортировка
	bool b = true;
	int t;
	while (b) {
		b = false;
		for (i = 0; i<n - 1; i++) {
			if (r[i]>r[i + 1]) {
				t = r[i];
				r[i] = r[i + 1];
				r[i + 1] = t;
				b = true;
			}
		}
	}
	return n;
}

string ArrayToString(int *p, int np) {
	if (!np) {
		return "Empty";
	}
	int i, cnt = 0;
	string s = to_string(p[0]);
	bool DiffOne, SerStart = false, fOne = false;
	for (i = 1; i < np; i++) {
		DiffOne = (p[i] - p[i - 1] == 1);
		if (!SerStart && DiffOne) {
			SerStart = true;
		}
		if (DiffOne) {
			cnt++;
			if (i == np - 1) {
				if (cnt > 1) {
					s += "-";
				}
				else {
					s += ",";
				}
				s += to_string(p[i]);
			}
			else if (((p[i + 1] - p[i]) != 1) && cnt==1) {
				s += "," + to_string(p[i]);
			}
		}
		else {
			if (cnt <= 1) {
				s += ",";
				s += to_string(p[i]);
			}
			else {
				fOne = false;
				s += "-";
				s += to_string(p[i - 1]);
				s += ",";
				s += to_string(p[i]);
				cnt = 0;
			}
		}
	}
	return s;
}
