class Animal {
public:
    Animal();
    Animal(int);
    ~Animal();
    virtual void talk();
    void eat();
protected:
    int id;
};

class Dog : public Animal {
public:
    Dog();
    Dog(int);
    ~Dog();
    void talk();
    void bark();
private:
    char *owner;
};

class Cat : public Animal {
public:
    Cat();
    Cat(int);
    ~Cat();
    void talk();
private:
    int lives;
};

