// ProjectLab13.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

class NullNameException : public exception {

};

class MinAgeException : public exception {
public:
	MinAgeException(const char* message)
		:exception(message) {
	}
};

class ShortNameException : public exception {

};

class Student {
	char name[50];
	int age;
public:
	Student(const char* Name, int Age) {
		if (Name == NULL) {
			throw new exception("NULL name");
		}
		if (strlen(Name) < 3) {
			throw new ShortNameException();
		}
		if (Age < 10) {
			//int values[5];
			//values[5000] = 67;
			throw new MinAgeException("Less than minimum age");
			//throw "Error";
		}
		strcpy(this->name, Name);
		this->age = Age;
	}
};

template<typename T, typename P>
class GenericBox {
	T value;
	P weight;
public:
	GenericBox(T Value, P Weight) {
		this->value = Value;
		this->weight = Weight;
	}
};



int main()
{
	Student s1("John", 12);

	while (true) {
		try {
			char name[50];
			cout << endl << "Student name: ";
			cin >> name;
			int age;
			cout << endl << "Student age: ";
			cin >> age;
			Student s2(name, age);
			cout << endl << "Ending reading student data";
			break;
		}



		catch (ShortNameException* e) {
			cout << endl << "The name is too short. At least 3 chars";
		}
		catch (MinAgeException* e) {
			cout << endl << "The age is too small. At least 10 years old";
		}
		catch (exception* e) {
			cout << endl << "We have a problem " <<
				e->what();
		}

		catch (...) {
			
			cout << endl << "Generic problem";
		}

	}

	GenericBox<Student, int> 
		box1(Student("John", 22), 70);
	GenericBox<float, int>
		box2(1.5, 70);

	cout << endl << "The END";
}

