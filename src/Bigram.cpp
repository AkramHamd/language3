//
// Created by pabolanez on 3/04/23.
/**
* @file Bigram.cpp
* @author Pablo Bolaños Martínez
*
*/

#include "../include/Bigram.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

Bigram::Bigram(const string& text) {
    if (text.length() != 2) {
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
    } else {
        _text[0] = text[0];
        _text[1] = text[1];
        _text[2] = '\0';
    }
}

Bigram::Bigram(char first, char second) {
    _text[0] = first;
    _text[1] = second;
    _text[2] = '\0';
}

Bigram::Bigram(const char text[]) {
    if (strlen(text) != 2) { // si el tamaño no es 2
        _text[0] = '_';
        _text[1] = '_';
        _text[2] = '\0';
    } else {
        _text[0] = text[0];
        _text[1] = text[1];
        _text[2] = '\0';
    }
}

std::string Bigram::getText() const {
    return std::string(_text);
}

std::string Bigram::toString() const
{
    return std::string(_text);
}

const char &Bigram::at(int index) const {
    if (index == 0 || index == 1) {
        return _text[index];
    }
    throw std::out_of_range("Índice fuera de rango.");
}

char &Bigram::at(int index){
    if (index == 0 || index == 1) {
        return _text[index];
    }
    throw std::out_of_range("Índice fuera de rango.");
}

void Bigram::toUpper() {
    for(int i = 0; i < 2; i++){
        _text[i] = std::toupper(_text[i]);
    }
};

bool isValidCharacter(char character, const std::string& validCharacters) {
    return validCharacters.find(character) != std::string::npos;
}

