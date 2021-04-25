#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <locale.h>
#include <time.h>
#include <ctime>
#include<chrono>
using namespace std;
using namespace chrono;

struct node {
	int key;
	int balance;
	bool mark;
	node *father;
	node *leftSon;
	node *rightSon;
};
node *createNewNode(int key);// Метод создающий новый узел
node *find(int key);// поиск узла или места для вставки
void balance(node *tmp);// пересчет балансов и вызов балансировок
void rightTurn(node *tmp);// малый правый поворот
void rightBigTurn(node *tmp);// большой правый поворот
void leftTurn(node *tmp);// левый малый поворот
void leftBigTurn(node *tmp);// левый большой поворот
void outputSpace(int key);// вывод пробелов между элементами
void output2(node *tmp, int cnt);// горизонтальный вывод
void output1();// вертикальный вывод
int maxDepth(node *tmp, int cnt);// максимальная глубина дерева
int minDepth(node *tmp, int min);// минимальная глубина дерева
int quantity(int key);// длина числа
bool add(int key);// добавление узла в дерево
void menu();// меню выбора

node *Head = NULL;// корень узла
node *Empty;// пустой узел (для вывода)
int maxLength;// максимальная длина числа
bool progress = false;// для вывода процента выполнения


node *createNewNode(int key)// Метод создающий новый узел
{
	node *tmp;
	tmp = new node();
	tmp->mark = false;
	tmp->key = key;
	tmp->balance = 0;
	tmp->leftSon = NULL;
	tmp->rightSon = NULL;
	return tmp;
}
node *find(int key)// поиск узла или места для вставки
{

	node *tmp = Head;
	if (tmp == NULL){
		Head = createNewNode(key);
		return Head;
	}
	while (true)
	{
		if (tmp->key < key)	{
			if (!tmp->rightSon){
				tmp->rightSon = createNewNode(key);
				tmp->rightSon->father = tmp;
				return tmp->rightSon;
			}
			else
				tmp = tmp->rightSon;
		}
		if (tmp->key > key){
			if (!tmp->leftSon){
				tmp->leftSon = createNewNode(key);
				tmp->leftSon->father = tmp;
				return tmp->leftSon;
			}
			else
				tmp = tmp->leftSon;
		}
		if (tmp->key == key)
			return NULL;
	}
}
void balance(node *tmp)// пересчет балансов и вызов балансировок
{
	if (!tmp)
		return;
	while (true){
		if (tmp == Head)
			return;
		if (tmp->father->key > tmp->key){
			tmp = tmp->father;
			tmp->balance--;
			if (tmp->balance == 0)
				return;
			if (tmp->balance == -2){
				tmp = tmp->leftSon;
				if (tmp->balance == -1)
					leftTurn(tmp);
				else{
					tmp = tmp->rightSon;
					leftBigTurn(tmp);
				}
				return;
			}
		}
		else{
			tmp = tmp->father;
			tmp->balance++;
			if (tmp->balance == 0)
				return;
			if (tmp->balance == 2){
				tmp = tmp->rightSon;
				if (tmp->balance == 1)
					rightTurn(tmp);
				else{				
					tmp = tmp->leftSon;
					rightBigTurn(tmp);
				}
				return;
			}

		}
	}
}
void rightTurn(node *tmp) {// правый поворот
	node *B = tmp, *A = tmp->father, *t = B->leftSon;
	if (A == Head) {
		Head = B;
		B->father = NULL;
	}
	else {
		if (A->father->rightSon == A)
			A->father->rightSon = B;
		else
			A->father->leftSon = B;
		B->father = A->father;
	}

	A->rightSon = B->leftSon;
	if (B->leftSon)
		B->leftSon->father = A;

	B->leftSon = A;
	A->father = B;

	A->balance = 0;
	B->balance = 0;
}
void rightBigTurn(node *tmp)// правый большой поворот
{
 	node *X = tmp, *B = tmp->father, *A = B->father;
	if (A == Head) {
		Head = X;
		X->father = NULL;
	}
	else {
		if (A->father->leftSon == A)
			A->father->leftSon = X;
		else
			A->father->rightSon = X;
		X->father = A->father;
	}

	if (X->leftSon)
		X->leftSon->father = A;
	A->rightSon = X->leftSon;

	if (X->rightSon)
		X->rightSon->father = B;
	B->leftSon = X->rightSon;

	X->leftSon = A;
	A->father = X;

	X->rightSon = B;
	B->father = X;

	if (X->balance == 1) {
		B->balance = 0;
		A->balance = -1;
	}
	else if (X->balance == -1) {
		B->balance = 1;
		A->balance = 0;
	}
	else {
		A->balance = 0;
		B->balance = 0;
	}
	X->balance = 0;
}
void leftTurn(node *tmp) {// левый поворот
	node *B = tmp, *A = tmp->father, *t = B->rightSon;
	if (A == Head) {
		Head = B;
		B->father = NULL;
	}
	else {
		if (A->father->rightSon == A)
			A->father->rightSon = B;
		else
			A->father->leftSon = B;
		B->father = A->father;
	}
	A->leftSon = B->rightSon;
	if (B->rightSon)
		B->rightSon->father = A;

	B->rightSon = A;
	A->father = B;

	A->balance = 0;
	B->balance = 0;
}
void leftBigTurn(node *tmp)//  левый большой поворот
{
	node *X = tmp, *B = tmp->father, *A = B->father;
	if (A == Head) {
		Head = X;
		X->father = NULL;
	}
	else {
		if (A->father->leftSon == A)
			A->father->leftSon = X;
		else
			A->father->rightSon = X;
		X->father = A->father;
	}

	if (X->rightSon)
		X->rightSon->father = A;
	A->leftSon = X->rightSon;

	if (X->leftSon)
		X->leftSon->father = B;
	B->rightSon = X->leftSon;

	X->rightSon = A;//
	A->father = X;//

	X->leftSon = B;
	B->father = X;

	if (X->balance == -1) {
		B->balance = 0;
		A->balance = 1;
	}
	else if (X->balance == 1) {
		B->balance = -1;
		A->balance = 0;
	}
	else {
		A->balance = 0;
		B->balance = 0;
	}
	X->balance = 0;
}
void outputSpace(int key)// вывод пробелов
{
	for (int i = 0; i < key*maxLength; i++)
		cout << " ";
}
void output2(node *tmp, int cnt)// горизонтальный вывод
{
	if (tmp){
		output2(tmp->rightSon, cnt + 1);
		outputSpace(cnt);
		cout << tmp->key << endl;
		output2(tmp->leftSon, cnt + 1);
	}
	return;
}
void output1()// вертикальный вывод
{
	queue < node > queue;
	queue.push(*Head);
	int n = maxDepth(Head, 0);
	for (int i = n; i > 0; i--)	{
		outputSpace(pow(2, i - 1) - 1);
		for (int j = 0; j < pow(2, n - i); j++)	{
			node tmp = queue.front();
			queue.pop();
			if (tmp.leftSon)
				queue.push(*tmp.leftSon);
			else
				queue.push(*Empty);
			if (tmp.rightSon)
				queue.push(*tmp.rightSon);
			else
				queue.push(*Empty);
			if (tmp.mark)
				outputSpace(1);
			else {
				if (quantity(tmp.key) < maxLength)
					for (int i = 0; i < maxLength - quantity(tmp.key); i++)
						cout << " ";
				cout << tmp.key;
			}
			outputSpace(pow(2, i) - 1);
		}
		cout << endl;
	}

}
int maxDepth(node *tmp, int cnt)// определение макс глубины
{
	if (tmp == NULL)
		return cnt;
	else
		return max(maxDepth(tmp->leftSon, cnt + 1), maxDepth(tmp->rightSon, cnt + 1));
}
int minDepth(node *tmp, int min) {
	return 0;
}
int quantity(int key)// определение длины числа
{
	int cnt = 1;
	while (key /= 10)
		cnt++;
	return cnt;
}
bool add(int key) {// добавление узла
	if (quantity(key) > maxLength)
		maxLength = quantity(key);
	if (progress) {
		cout << "0%\n";
		Sleep(50);
	}
	node *tmp = find(key);
	if (progress) {
		cout << "50%\n";
		Sleep(50);
	}
	if (!tmp) {
		if (progress) {
			cout << "100%\n";
			Sleep(50);
		}
		return true;
	}
	balance(tmp);
	if (progress) {
		cout << "100%\n";
		Sleep(50);
	}
	return false;
}
void menu() {// меню выбора
	int n = 0, input = -1, output = -1, want = -1, flag = 0, key=0, source=0;// input- способ ввода, output- способ вывода 
	// want- способ выполнения, flag- способ вывода, source- выводить исходное
	cout << "Введите количество элементов в дереве: ";
	cin >> n;
	if (n <= 0) {
		cout << "Введен некоректный параметр.";
		return;
	}

	cout << endl << "Выберите способа ввода данных:\n1) С клавиатуры 2) Из файла(input.txt, после данных в файле нужно поставь Enter) 3) Датчиком случайных чисел.\n";
	cin >> input;
	if (input < 1 || input > 3) {
		cout << "Введен некоректный номер.";
		return;
	}

	cout << "Выберите способ вывода данных:\n1) На экран 2) В файл(output.txt) 3) Не выводить.\n";
	cin >> output;
	if (output < 1 || output > 3) {
		cout << "Введен некоректный номер.";
		return;
	}
	if (output != 3) {
		cout << "Выберите способ вывода дерева:\n1) Вертикально 2) Горизонтально.\n";
		cin >> flag;
		if (flag < 1 || flag >2) {
			cout << "Введен некоректный номер.";
			return;
		}
	}
	cout << "Выберите способ выполнения:\n1) С измерением времени 2) С выводом процента выполнения и шкалы прогресса.\n";
	cin >> want;
	if (want < 1 || want > 2) {
		cout << "Введен некоректный номер.";
		return;
	}
	if (input == 1) {
		cout << "Введите элементы дерева (" << n << "):\n";
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			add(x);
		}
	}
	if (input == 2) {
		freopen("input.txt", "r", stdin);
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			add(x);
		}
		freopen("CON", "r", stdin);
	}
	if (input == 3) {
		bool t;
		FILE *file = fopen("input.txt", "w");
		for (int i = 0; i < n; i++) {
			int x = rand()*rand()*rand();
			t = add(x);
			if(i%1000==0)
			printf("\r%f", (float(i) / n)*100);
			//fprintf(file, "%d ", x);
		}
		cout << endl;
		fclose(file);
	}
	cout << "Выводить исходные данные? 1)Да 2)Нет.\n";
	cin >> source;
	if (source < 1 || source>2) {
		cout << "Введен некоректный номер.";
		return;
	}
	
	if (source == 1) {
		cout << "Исходные данные:\n";
		if (flag == 1)
			output1();
		else
			output2(Head, 0);
	}
	cout << endl << "Введите ключ для поиска со вставкой: ";
	cin >> key;

	if (want == 2)
		progress = true;
	auto start = steady_clock::now();
	bool find = add(key);
	auto end = steady_clock::now();
	if (find)
		cout << "\nУзел был найден.\n";
	else 
		cout << "\nУзел не был найден.\n";
	if (want == 1)
		cout << duration_cast<nanoseconds>(end - start).count() << " наносекунд" << endl;
	if (output == 1) {
		cout << "Полученное дерево:\n";
		if (flag == 1)
			output1();
		else
			output2(Head, 0);
	}
	if (output == 2) {
		freopen("output.txt", "w", stdout);
		cout << "Полученное дерево:\n";
		if (flag == 1)
			output1();
		else
			output2(Head, 0);
		freopen("CON", "w", stdout);
		setlocale(LC_ALL, "RUS");
	}
}
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	maxLength = 0;

	Empty = new node();
	Empty->leftSon = NULL;
	Empty->rightSon = NULL;
	Empty->mark = true;
	
	menu();
	system("pause");
}
