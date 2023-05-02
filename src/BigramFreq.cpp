//
// Created by pabolanez on 3/04/23.
//
/**
 * @file BigramFreq.cpp
 * @author Pablo Bolaños Martínez
 *
 */

#include "../include/BigramFreq.h"
#include <iostream>
#include <string>

using namespace std;

BigramFreq::BigramFreq(){
    _bigram = Bigram();
    _frequency = 0;
}

BigramFreq::BigramFreq(const Bigram &bg, int freq) {
    _bigram = bg;
    _frequency = freq;
}

const Bigram& BigramFreq::getBigram() const {
    return _bigram;
}

const int& BigramFreq::getFrequency() const{
    return _frequency;
}

void BigramFreq::setBigram(const Bigram& bigram) {
    _bigram = bigram;
}

void BigramFreq::setFrequency(int frequency) {
    if (frequency < 0) {
        throw std::out_of_range("La frecuencia debe ser un número positivo");
    }
    _frequency = frequency;
}

std::string BigramFreq::toString() const {
    string text = _bigram.toString() + " " + to_string(_frequency);
    return text;
}