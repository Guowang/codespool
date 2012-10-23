#include <iostream>
using namespace std;
#include "animal.h"

// the Animal class (base class)
Animal::Animal()
{
    id = 0;
    cout << "creating an animal (ID: " << id << ")\n";
}

Animal::Animal(int n)
{
    id = n;
    cout << "creating an animal (ID: " << id << ")\n";
}

Animal::~Animal()
{ cout << "destructing animal " << id << endl; }

void Animal::talk()
{ cout << "I am an animal; my ID is " << id << endl; }

void Animal::eat()
{ cout << "I want food\n"; }

// the Dog class
Dog::Dog()
{
    id = 0;
    cout << "creating a dog (ID: " << id << ")\n";
}

Dog::Dog(int n)
{
    id = n;
    cout << "creating a dog (ID: " << id << ")\n";
}

Dog::~Dog()
{ cout << "destructing dog " << id << endl; }

void Dog::talk()
{ cout << "I am a dog.  My ID is " << id << endl; }

void Dog::bark()
{ cout << "I can bark\n"; }

// the Cat class
Cat::Cat()
{
    id = 0;
    cout << "creating a cat (ID: " << id << ")\n";
}

Cat::Cat(int n)
{
    id = n;
    cout << "creating a cat (ID: " << id << ")\n";
}

Cat::~Cat()
{ cout << "destructing cat " << id << endl; }

void Cat::talk()
{ cout << "I am a cat.  My ID is " << id << endl; }
