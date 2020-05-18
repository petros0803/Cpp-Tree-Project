#include<iostream>
#include<fstream>
#include<cstring>

using namespace std;

char operators[3][3] = { "+-", "*/", "" };

char expression[200];

char* p;

struct node {
	double value;
	char operation;

	node* left;
	node* right;

	node(double value = 0, char operation = 0, node* left = 0, node* right = 0) {
		this->value = value;
		this->operation = operation;
		this->left = left;
		this->right = right;
	}
};

node* tree;

node* buildTree(int level) {
	node* first;
	node* second;

	if (level == 2) {
		if (*p == '(') {
			p++;
			first = buildTree(0);//operatie de graul 0
			p++;
		}
		else {
			first = new node(); /*daca nu este “(” este numar. Deci se creeaza un
								nod in care se stocheaza numarul si se adauga
								pe pozitia (nodul) curenta.*/
			while (isdigit(*p)) {
				/* cat timp pointerul este un numar, se creeaza numarul interg.*/
				first->value = first->value * 10 + *p - '0';
				p++;
			}
		}
	}
	else {
		first = buildTree(level + 1); //ridicam gradul pentru prioritizarea operatiilor
		while (strchr(operators[level], *p)) {/* verificam operatia, daca este de grad 0
											  se verifica daca este “+” sau ”-”.
											  Daca este de grad 1, se verifica daca este “*” sau “/”.
											  Daca are gradul 2 nu intra pe aceasta ramura */

			second = new node(0, *p++, first, buildTree(level + 1)); /*creem un nod nou in care se pune
																	 operatia deasupra pentru cele doua noduri. */
			first = second;//Se adauga operatiile de acelasi grad in continuare.
		}
	}
	return first;// returnezi nodul creat.
}

double evaluate(node* argument) {
	switch (argument->operation) {
	case '+':
		return evaluate(argument->left) + evaluate(argument->right);
	case '-':
		return evaluate(argument->left) - evaluate(argument->right);
	case '*':
		return evaluate(argument->left) * evaluate(argument->right);
	case '/':
		if (evaluate(argument->right) == 0)
		{
			ofstream fout("Result.out");
			fout << "Nu poti imparti la 0";
			std::exit(1);
		}
		else
			return evaluate(argument->left) / evaluate(argument->right);

	default:
		return argument->value;
	}
}
/* Se evalueaza in mod recursiv fiecare nod al arborelui*/

int main() {
	p = expression;; //se pune pointerul la inceputul expresiei
	ifstream fin("Expression.in");
	ofstream fout("Result.out");
	fin >> p;
	expression[strlen(expression)] = '=';
	tree = buildTree(0); //Se construieste arborele
	fout << "Rezultatul expresiei este: " << evaluate(tree);/* se afiseaza valoarea
															expresiei prin intermediul arborelui */
	return 0;
};