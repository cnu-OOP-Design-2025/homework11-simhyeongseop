
#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "character.h"
using namespace std;

class Undead {
public:
    virtual string name() const = 0;
    virtual int power() const = 0;
    virtual int agility() const = 0;
    virtual int endurance() const = 0;
    virtual ~Undead() {}
};

class Zombie : public Undead {
public:
    string name() const override { return "Zombie"; }
    int power() const override { return 15; }
    int agility() const override { return 5; }
    int endurance() const override { return 20; }
};

class Skeleton : public Undead {
public:
    string name() const override { return "Skeleton"; }
    int power() const override { return 10; }
    int agility() const override { return 15; }
    int endurance() const override { return 10; }
};

class Lich : public Undead {
public:
    string name() const override { return "Lich"; }
    int power() const override { return 25; }
    int agility() const override { return 12; }
    int endurance() const override { return 18; }
};

// Adapter: Undead → Character
class UndeadAdapter : public Character {
    shared_ptr<Undead> undead;
public:
    UndeadAdapter(shared_ptr<Undead> u) { 
        undead = u;
        description = undead ? undead->name() : "Undead";
        if (description == "Zombie") {
            type = CharacterType::Zombie;
        } else if (description == "Skeleton") {
            type = CharacterType::Skeleton;
        } else if (description == "Lich") {
            type = CharacterType::Lich;
        } else {
            type = CharacterType::Unknown;
        }
    }
    int getAttack() const override { return undead ? undead->power() : 0; }
    int getSpeed() const override { return undead ? undead->agility() : 0; }
    int getDefense() const override { return undead ? undead->endurance() : 0; }
};
