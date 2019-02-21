/// problem : 2329. (деревья) Поиск по ключу в частично-упорядоченном бинарном дереве

#include <iostream>



using namespace std;

void search(int);

struct NODE {	// Структура "Узел" для элементов дерева

	int elem;	// данные
	NODE *left;		// левое поддерево
	NODE *right;	// правое поддерево
	NODE(int el) { left = right = NULL; elem = el; }
};

NODE *root;	// глобальный корень дерева

void push(int el) { // вставка нового элемента в дерево

	if (!root) {
		root = new NODE(el);
		return;
	}

	NODE *buf;
	buf = root;

	while (true) {
		if (buf->elem >= el) {
			if (!buf->left) {
				buf->left = new NODE(el);
				return;
			}
			buf = buf->left;
		}
		else {
			if (!buf->right) {
				buf->right = new NODE(el);
				return;
			}
			buf = buf->right;
		}
	}
}

bool find_el(NODE* tree, int key){
    if(tree == NULL) return false;
    if(key == tree->elem) return true;
    if(key < tree->elem) return find_el(tree->left, key);
    else return find_el(tree->right, key);
}

void search(int key) {
	// ЭТУ ФУНКЦИЮ НУЖНО НАПИСАТЬ
    if(find_el(root, key)) cout << "Element \"" << key << "\" is found.";
    else cout << "Element \"" << key << "\" is not found.";
}

void print(NODE* cur) {	// печать, симметричный обход
	if (cur->left) {
		print(cur->left);
	}
	cout << cur->elem << endl;
	if (cur->right) {
		print(cur->right);
	}
}

int main() {
	// для отладки:
	// вывод дерева print(node) где node - указатель на корень дерева
	// поместить элемент в дерево push(element) прим. - элемент поместится в нужное место.
	// шаблон предназначен для отправки на проверку, для отладки можете самостоятельно
	// помещать свои элементы напр. push(5); push(20); push(50) и т.д. и работать со своими элементами

	// Само дерево объявлено глобально в коде
	int N;	// кол-во элементов
	cin >> N;
	for (int i = 0; i < N; i++) {	// ввод элементов в дерево
		int a;
		cin >> a;
		push(a);
	}
	cin >> N;	// искомый элемент
	search(N);	// поиск с выводом
	return 0;
}
