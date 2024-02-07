#include <iostream>
#include <string>

//Наследование - это механизм расширения функционалла класса, путем сужения его специализации
// при котором открывается дорога к полиморфизму.
//
class Base {
public:
	
	Base():Base(0,0,0){ }
	Base(int a, int b, int c):a(a),b(b),c(c){ }
	int a;
	int A() { return a; }
	int B() { return b; }
	int C() { return c; }
protected:
	int b;
	
private:
	int c;
 };

class Derived :public Base {	//публичное наследование позвляет пользоваться внутри объекта наследника
								//родительскими полями public и protected так, как будто они являются его полями
public:
	Derived() = default;
	Derived(int a, int b, int c,int d)
		:Base(a,b,c),d(d){ }
	int M00() {
		int res{};
		res = a + b;// свободно испольщуем публичные поля
		res /= C();//  Приватные поля доступны через методы класса
		return res;
	}
	int D() { return d; }
private:
	int d;

};


class Animal {
public:
	int Age()const { return age_; }
	void Age(int newAge) { age_ = newAge; }

	void Name(std::string newName) {name_ = newName; }
	std::string Name()const { return name_; }

	//virtual помечает функцию которая должна вызываться у наследников в момент их обработки под видом родителя
	virtual void Say()const {
		std::cout << " r.\n" ;
	}
private:
	std::string name_;
	int age_;
};

class Kat :public Animal {
public:
	void Say()const override{		//override доп проверка что мы функцию написали правильно
		std::cout << " Meuw\n";
	}
};

int main() {
	setlocale(LC_ALL, "ru");

	Base obj(1,2,5);
	obj.a;
	/*obj.b;
	obj.c;*/
	Derived dObj(1,2,3,99);
	dObj.B();
	
	Animal abs;
	abs.Name("Dog");
	abs.Age(1);
	abs.Say();

	Kat kat;
	kat.Name("Fluffi");
	kat.Age(3);
	kat.Say();			//по умолчанию вызовет свою реализацию
	kat.Animal::Say();  // вызовет реализацию родителя принудительно
	
	Animal* p = &abs;
	p = &kat;

	p->Say();


	return 0;
}