#pragma once
#include <stdexcept>

class Price {
    int value;
public:
    Price(int val) : value(val) { if (val < 0) throw std::invalid_argument("Цена < 0"); }
    int getValue() const { return value; }
    double asRubles() const { return value / 100.0; }
};

class Quantity {
    int value;
public:
    Quantity(int val) : value(val) { if (val < 0) throw std::invalid_argument("Кол-во < 0"); }
    int getValue() const { return value; }
    void change(int delta) { if (value + delta < 0) throw std::invalid_argument("Кол-во < 0"); value += delta; }
};

class Weight {
    double grams;
public:
    Weight(double g) : grams(g) { if (g < 0) throw std::invalid_argument("Вес < 0"); }
    double asKg() const { return grams / 1000.0; }
};