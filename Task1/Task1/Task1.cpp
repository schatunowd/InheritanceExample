// Example2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;
class B1
{
    int a;
public:
	B1() { cout << "object of " << typeid(*this).name() << " was created\n"; }
	B1(int x) : B1() { a = x; }
	~B1() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class B2
{
	int b;
public:
	B2() { cout << "object of " << typeid(*this).name() << " was created\n"; }
	B2(int x) : B2() { b = x; }
	~B2() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D1: virtual private B1,  virtual public B2
{
	int c;
public:
	D1(int x, int i, int j) : B1(i), B2(j) { cout << "object of " << typeid(*this).name() << " was created\n"; }
	D1(int x) : D1() { c = x; }
	~D1() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D2 : virtual public B1, virtual private B2
{
	int d;
public:
	D2(int x, int k, int l) : B1(k), B2(l) { cout << "object of " << typeid(*this).name() << " was created\n"; }
	D2(int x) : D2() { d = x; }
	~D2() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

class D3 : private D1, public D2
{
	int e;
public:
	D3(int x, int k, int l, int m, int n, int o) : D1(x, k, l), D2(m, n, o) { cout << "object of " << typeid(*this).name() << " was created\n"; }
	D3(int x) : D2() { e = x; }
	~D3() { cout << "object of " << typeid(*this).name() << " was destroyed\n"; }
};

int main() {
	D3(1, 2, 3, 4, 5, 6, 7);
}

