#include <iostream>
#include <string>

using namespace std;

class Creature 
{
private:
	string title;
	double mass;
protected:
	Creature() : mass(0.0) {}
	Creature(const Creature& obj) : title(obj.title), mass(obj.mass) {}
	Creature(const string& _title, double _mass) : title(_title), mass(_mass) {}
	virtual ~Creature() { cout << "creature deleted" << endl << endl; }
	virtual void _print() const { cout << "title: " << title << ", mass: " << mass; }
public:
	void print() const 
	{
		cout << typeid(*this).name() << ": (";
		_print();
		cout << ")" << endl;
	}
	double get_mass() const 
	{
		return mass;
	}
};

class Animal : public Creature 
{
private:
	double speed;
public:
	Animal() : Creature() {}
	Animal(const Animal& obj) : Creature(obj), speed(obj.speed) {}
	Animal(const string& _title, double _mass, double _speed) : Creature(_title, _mass), speed(_speed) {}
	~Animal() { cout << "animal deleted" << endl; }
	double get_speed() const {
		return speed;
	}
protected:
	void _print() const 
	{
		Creature::_print();
		cout << ", speed: " << speed;
	}
};

class Bird : virtual public Animal 
{
private:
	double topfly;
public:
	Bird() : Animal() {};
	Bird(const Bird& obj) : Animal(obj), topfly(obj.topfly) {}
	Bird(const string& _title, double _mass, double _speed, double _topfly) : Animal(_title, _mass, _speed), topfly(_topfly) {}
	~Bird() { cout << "bird deleted" << endl; }
protected:
	void _print() const 
	{
		Animal::_print();
		cout << ", topfly: " << topfly;
	}
};

class Fish : public Animal 
{
private:
	double maxdeep;
public:
	Fish() : Animal() {};
	Fish(const Fish& obj) : Animal(obj), maxdeep(obj.maxdeep) {}
	Fish(const string& _title, double _mass, double _speed, double _maxdeep) : Animal(_title, _mass, _speed), maxdeep(_maxdeep) {}
	~Fish() { cout << "fish deleted" << endl; }
protected:
	void _print() const 
	{
		Animal::_print();
		cout << ", maxdeep: " << maxdeep;
	}
};

class Predator : virtual public Animal 
{
protected:
	Predator() {}
public:
	~Predator() {}
	virtual bool hunt(const Animal& obj) = 0;
};

class Eagle : public Bird, public Predator 
{
public:
	Eagle() : Bird() {}
	Eagle(const Eagle& obj) : Bird(obj) {}
	Eagle(double _mass, double _speed, double _topfly) : Bird("Îð¸ë", _mass, _speed, _topfly) {}
	bool hunt(const Animal& obj) 
	{
		return obj.get_mass() < get_mass() && obj.get_speed() < get_speed();
	}
};

int main() 
{
	setlocale(0, "Rus");
	Bird raven("Ворона", 0.3, 10, 0.1);
	Fish hammerhead("Рыба-молот", 150, 5, 0.5);
	raven.print();
	hammerhead.print();
	Predator& eagle1 = *new Eagle(1, 100, 1);
	cout << "Eagle vs raven: " << eagle1.hunt(raven) << endl;
	cout << "Eagle vs hammerhead: " << eagle1.hunt(hammerhead) << endl;
	cout << endl;
	delete& eagle1;
	return 0;
}