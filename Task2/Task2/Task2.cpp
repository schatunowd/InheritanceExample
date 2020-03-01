#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <vector>
using namespace std;

class objectofcomputergame
{
private:
	string name;
public:
	objectofcomputergame(const string _name): name(_name) {}
	objectofcomputergame(const objectofcomputergame& obj): name(obj.name) {}
	~objectofcomputergame() {}

	explicit virtual operator string()
	{
		return string(typeid(*this).name()) + ": (" + _print() + ")";
	}

	string get_name() const
	{
		return name;
	}

protected:
	virtual string _print()
	{
		return "title: " + name;
	}
};

class character : public objectofcomputergame
{
private:
	int x, y, health, maxhealth, mana, maxmana;
public:
	character(const string _name, const int _maxhealth, const int _maxmana) : objectofcomputergame(_name), x(0), y(0), health(_maxhealth), maxhealth(_maxhealth), mana(_maxmana), maxmana(_maxmana) {}
	character(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y) : objectofcomputergame(_name), x(_x), y(_y), health(_maxhealth), maxhealth(_maxhealth), mana(_maxmana), maxmana(_maxmana) {}
	character(const character& obj) : objectofcomputergame(obj), x(obj.x), y(obj.y), health(obj.maxhealth), maxhealth(obj.maxhealth), mana(obj.maxmana), maxmana(obj.maxmana) {}
	~character() {}

	int getx() const
	{
		return x;
	}

	int gety() const
	{
		return y;
	}

	int gethealth() const
	{
		return health;
	}

	int getmana() const
	{
		return mana;
	}

	virtual void move(int dx, int dy) = 0;
	virtual void take_damage(int damage) = 0;
	virtual void mana_use(int mana_cost) = 0;

protected:
	void _move(const int dx, const int dy)
	{
		x += dx;
		y += dy;
	}

	void _take_damage(const int damage)
	{
		health = std::max(0, health - damage);
	}

	void _mana_use(const int manaCost)
	{
		mana = std::max(0, mana - manaCost);
	}

	std::string _print() override
	{
		return objectofcomputergame::_print() + ", x: " + to_string(x) + ", y: " + to_string(y) +
			", health: " + to_string(health) + ", max health: " + to_string(maxhealth) +
			", mana: " + to_string(mana) + ", max mana: " + to_string(maxmana);
	}
};

class arsenal: public objectofcomputergame
{
private:
	int damage;
public:
	arsenal(const string _name, const int _damage) : objectofcomputergame(_name), damage(_damage) {}
	arsenal(const arsenal& obj): objectofcomputergame(obj), damage(obj.damage) {}
	~arsenal() {}

	int get_damage() const
	{
		return damage;
	}

protected:
	string _print() override
	{
		return objectofcomputergame::_print() + ", damage: " + to_string(damage);
	}
};

class magicstuff: virtual public arsenal
{
private:
	int magicdamage;
public:
	magicstuff(const string _name, const int _damage, const int _magicdamage): arsenal(_name, _damage), magicdamage(_magicdamage) {}
	magicstuff(const magicstuff& obj): arsenal(obj), magicdamage(obj.magicdamage) {}
	~magicstuff() {}

	int get_magicdamage() const
	{
		return magicdamage;
	}

protected:
	string _print() override
	{
		return arsenal::_print() + ", magicdamage: " + to_string(magicdamage);
	}
};


class mythicalanimal : virtual public character
{
private:
	string specialty; 
public:
	mythicalanimal(const string _name, const string _specialty, const int _maxhealth, const int _maxmana): character(_name, _maxhealth, _maxmana), specialty(_specialty) {}
	mythicalanimal(const string _name, const string _specialty, const int _maxhealth, const int _maxmana, const int _x, const int _y): character(_name, _maxhealth, _maxmana, _x, _y), specialty(_specialty) {}
	mythicalanimal(const mythicalanimal& obj): character(obj), specialty(obj.specialty) {}
	~mythicalanimal() {}

	void move(const int dx, const int dy) override
	{
		character::_move(dx, dy);
		cout << "Mythical animal " + get_name() + " goes to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
	}

	void take_damage(const int damage) override
	{
		character::_take_damage(damage);
		cout << "Mythical animal " + get_name() + " hit by " + to_string(damage) + " damage.\n";
	}

	void mana_use(const int mana_cost) override
	{
		character::_mana_use(mana_cost);
	    cout << "Mythical animal " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
	}

protected:
	string _print() override
	{
		return character::_print() + ", specialty: " + specialty;
	}
};


class humanoid : virtual public character
{
public:
	humanoid(const string _name, const int _maxhealth, const int _maxmana): character(_name, _maxhealth, _maxmana) {}
	humanoid(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y): character(_name, _maxhealth, _maxmana, _x, _y) {}
	humanoid(const humanoid& obj): character(obj) {}
	~humanoid() {}

	void move(const int dx, const int dy) override
	{
		character::_move(dx, dy);
		cout << "Humanoid " + get_name() + " moved to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
	}

	void take_damage(const int damage) override
	{
		character::_take_damage(damage);
		cout << "Humanoid " + get_name() + " hit by " + to_string(damage) + " damage.\n";
	}

	void mana_use(const int mana_cost) override
	{
		character::_mana_use(mana_cost);
		cout << "Humanoid " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
	}

	void voice(const string str) 
	{
		cout << get_name() + " shout \"" + str + "\"\n";
	}
};

class magiccharacter : virtual public character
{
private:
	string kindofmagic;
public:
	magiccharacter(const string _name, const int _maxhealth, const int _maxmana, const string _kindofmagic): character(_name, _maxhealth, _maxmana), kindofmagic(_kindofmagic) {}
	magiccharacter(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y): character(_name, _maxhealth, _maxmana, _x, _y) {}
	magiccharacter(const string _name, const int _maxhealth, const int _maxmana, const string _kindofmagic): character(_name, _maxhealth, _maxmana), kindofmagic(_kindofmagic) {}
	magiccharacter(const string _name, const int _maxhealth, const int _maxmana, const int _x, const int _y, const string _kindofmagic): character(_name, _maxhealth, _maxmana, _x, _y), kindofmagic(_kindofmagic) {}
	magiccharacter(const magiccharacter& obj): character(obj), kindofmagic(obj.kindofmagic) {}
	~magiccharacter() {}

	void move(const int dx, const int dy) override
	{
		character::_move(dx, dy);
		cout << "Magic character " + get_name() + " goes to (" + to_string(getx()) + ", " + to_string(gety()) + ").\n";
	}

	void take_damage(const int damage) override
	{
		character::_take_damage(damage);
		cout << "Magic character " + get_name() + " hit by " + to_string(damage) + " damage.\n";
	}

	void mana_use(const int mana_cost) override
	{
		character::_mana_use(mana_cost);
		cout << "Magical creature " + get_name() + " used " + to_string(mana_cost) + " manapoints.\n";
	}

protected:
	string _print() override
	{
		return character::_print() + ", kind of magic: " + kindofmagic;
	}
};

int main()
{
	mythicalanimal animal1("Ugly monster", "Undefined", 100, 100, 40, 40);
	cout << string(animal1) << endl;
	animal1.move(10, -5);
	animal1.take_damage(30);
	magiccharacter animal2("Zombie", 50, 50, "stinks");
	cout << string(animal2) << endl;
	animal2.move(3, 19);
	animal2.mana_use(200);
	animal2.take_damage(100);
	cout << endl;
	magicstuff firestaff("Firestaff", 30, 30);
	cout << string(firestaff) << endl;
	humanoid boy("Sashka", 200, 500, 100, 200);
	boy.voice("HELLO!");
	return 0;
}