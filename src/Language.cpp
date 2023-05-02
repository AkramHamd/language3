/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/** 
 * @file Language.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 * 
 * Created on 12 February 2023, 10:40
 */

#include "../include/Language.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

const string Language::MAGIC_STRING_T="MP-LANGUAGE-T-1.0";

//Constructor sin parámetros
Language::Language() {
    _languageId = "unknown";
    _size = 0;
}

//Constructor con parámetros
Language::Language(int numberBigrams) {
    if (numberBigrams <= 0 || numberBigrams > DIM_VECTOR_BIGRAM_FREQ) {
        throw std::out_of_range("El número de bigramas está fuera de rango.");
    }

    _languageId = "unknown";
    _size = numberBigrams;

    for (int i = 0; i < _size; i++) {
        _vectorBigramFreq[i] = BigramFreq(Bigram(), 0);
    }
}

//Devuelve el identificador del Language
const std::string& Language::getLanguageId() const {
    return _languageId;
}

//Asignamos un nuevo identificador
void Language::setLanguageId(const std::string& id) {
    _languageId = id;
}

//Devuelve referencia constante al BigramFreq con el índice dado
const BigramFreq& Language::at(int index) const {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("El índice proporcionado no es válido");
    }
    return _vectorBigramFreq[index];
}

//Devuelve referencia al BigramFreq con el índice dado
BigramFreq& Language::at(int index) {
    if (index < 0 || index >= _size) {
        throw std::out_of_range("El índice proporcionado no es válido");
    }
    return _vectorBigramFreq[index];
}

//Devuelve el número de objetos BigramFreq
int Language::getSize() const {
    return _size;
}

double Language::getDistance(const Language& otherLanguage) const{
    int size1 = this->getSize();
    int size2 = otherLanguage.getSize();
    if (size1 == 0) {
        throw std::invalid_argument("Cannot calculate distance from an empty Language");
    }
    int i = 0, j = 0;
    double distance = 0.0;
    while (i < size1) {
        const BigramFreq& bigram1 = this->at(i);
        int rank1 = i;
        int rank2 = size2;
        bool found = false;
        while (j < size2 && !found) {
            const BigramFreq& bigram2 = otherLanguage.at(j);
            if (bigram1.getBigram().toString() == bigram2.getBigram().toString()) {
                rank2 = j;
                found = true;
            }
            ++j;
        }
        distance += std::abs(rank1 - rank2);
        ++i;
    }
    return distance / (size1 * size1);
}

int Language::findBigram(const Bigram& bigram) const {
    for (int i = 0; i < _size; i++) {
        if (_vectorBigramFreq[i].getBigram().getText() == bigram.getText()) {
            return i;
        }
    }
    return -1;
}

std::string Language::toString() const {
    std::string str;
    str += std::to_string(_size) + "\n";
    for (int i = 0; i < _size; i++) {
        str += _vectorBigramFreq[i].getBigram().getText() + " " + std::to_string(_vectorBigramFreq[i].getFrequency()) + "\n";
    }
    return str;
}

void Language::swapElements(int first, int second) {
    if (first < 0 || first >= _size || second < 0 || second >= _size)
    {
        throw std::out_of_range("Índice fuera de rango");
    }
    std::swap(_vectorBigramFreq[first], _vectorBigramFreq[second]);
}

void Language::sort() {
    bool cambiado;
    int i, j;

    // Utilizo Ordenamiento de burbuja
    for (i = 0; i < _size - 1; i++) {
        cambiado = false;
        for (j = 0; j < _size - i - 1; j++) {
            if (_vectorBigramFreq[j].getFrequency() < _vectorBigramFreq[j + 1].getFrequency()) {
                swapElements(j, j + 1);
                cambiado = true;
            }
        }
        if (!cambiado) {
            break;
        }
    }
}

void Language::save(const char fileName[]) const {
    ofstream outputFile(fileName);
    if (!outputFile.is_open()) {
        throw std::ios_base::failure("Error al abrir el fichero.");
    }

    outputFile << MAGIC_STRING_T << endl;
    outputFile << _languageId << endl;
    outputFile << this->getSize() << endl;

    for (int i = 0; i < this->getSize(); i++) {
        outputFile << _vectorBigramFreq[i].toString() << endl;
    }

    outputFile.close();
}

void Language::load(const char fileName[]) {
    ifstream file(fileName);
    if (!file.is_open()) {
        throw std::ios_base::failure("Error al abrir el fichero");
    }

    string magic;
    file >> magic;
    if (magic != MAGIC_STRING_T) {
        throw std::invalid_argument("Formato de fichero inválido");
    }

    file >> _languageId;
    file >> _size;

    if (_size > DIM_VECTOR_BIGRAM_FREQ) {
        throw std::out_of_range("Número de bigramas en el fichero supera la capacidad");
    }

    string bigram;
    int frequency;

    for (int i = 0; i < _size; i++) {

        file >> bigram >> frequency;

        _vectorBigramFreq[i].setBigram(bigram);
        _vectorBigramFreq[i].setFrequency(frequency);

    }

    file.close();
}

void Language::append(const BigramFreq& bigramFreq) {
    int indice = findBigram(bigramFreq.getBigram());

    if (indice == -1) {
        if (_size == DIM_VECTOR_BIGRAM_FREQ) {
            throw std::out_of_range("El array está lleno");
        }
        _vectorBigramFreq[_size++] = bigramFreq;
    } else {
        _vectorBigramFreq[indice].setFrequency(bigramFreq.getFrequency());
    }
}

void Language::join(const Language& language) {
    if (_languageId != language._languageId) {
        throw std::invalid_argument("Los lenguajes no coinciden");
    }

    for (int i = 0; i < language._size; i++) {
        // Compruebo si el bigrama ya está en el idioma
        int indice = findBigram(language._vectorBigramFreq[i].getBigram());
        if (indice != -1) {
            // Si está, añade las frecuencias
            _vectorBigramFreq[indice].setFrequency(_vectorBigramFreq[indice].getFrequency() + language._vectorBigramFreq[i].getFrequency());
        } else {
            // Si no lo está, se agrega el nuevo par al final de la lista
            append(language._vectorBigramFreq[i]);
        }
    }
}