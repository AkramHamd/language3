/*
 * Metodología de la Programación: Language3
 * Curso 2022/2023
 */

/* 
 * File:   main.cpp
 * @author Silvia Acid Carrillo <acid@decsai.ugr.es>
 * @author Andrés Cano Utrera <acu@decsai.ugr.es>
 * @author Luis Castillo Vidal <L.Castillo@decsai.ugr.es>
 *
 * Created on 7 de febrero de 2023, 14:02
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "../include/Language.h"

using namespace std;

/**
 * Shows help about the use of this program in the given output stream
 * @param outputStream The output stream where the help will be shown (for example,
 * cout, cerr, etc) 
 */
void showEnglishHelp(ostream& outputStream) {
   outputStream << "Error, run with the following parameters:" << endl;
   outputStream << "language3 [-t min|max] <file1.bgr> <file2.bgr> [ ... <filen.bgr>]" << endl;
}

/**
 * This program reads an undefined number of Language objects from the set of 
 * files passed as parameters to main(). All the Languages object, except the 
 * first one, must be stored in a dynamic array of Language objects. Then, 
 * for each Language in the dynamic array, this program prints to the 
 * standard output the name of the file of that Language and the distance from 
 * the first Language to the current Language. 
 * Finally, the program should print in the standard output, the name of 
 * the file with the Language with the minimum|maximum distance to the Language 
 * of the first file and its language identifier.
 * 
 * At least, two Language files are required to run this program.
 * Running example:
 * > language3 [-t min|max] <file1.bgr> <file2.bgr> [  ... <filen.bgr>] 
 */
int main(int argc, char* argv[]) {
    // Comprobamos el número de argumentos
    if (argc < 3) {
        showEnglishHelp(cerr);
        return 1;
    }

    // Comprobamos si es min o max
    bool esMin = true;
    if (argc >= 4 && string(argv[1]) == "-t") {
        if (string(argv[2]) == "max") {
            esMin = false;
        } else if (string(argv[2]) != "min") {
            showEnglishHelp(cerr);
            return 1;
        }
    }

    // Abrimos el primer fichero y leemos su contenido
    ifstream fichero1(argv[1]);
    if (!fichero1.is_open()) {
        cerr << "Error al abrir el fichero: " << argv[1] << endl;
        return 1;
    }
    Language* firstLanguage = new Language();
    firstLanguage->load(fichero1);

    // Leemos el resto de ficheros
    vector<Language*> languages;
    for (int i = 2; i < argc; ++i) {
        ifstream inputFile(argv[i]);
        if(!inputFile.is_open()){
            cerr << "Error al abrir el fichero: " << argv[i] << endl;
            return 1;
        }
        Language* language = new Language();
        language->read(inputFile);
        languages.push_back(language);
    }

    // Imprimimos las distancias al primer language
    for (int i = 0; i < languages.size(); ++i) {
        double distance = firstLanguage->getDistance(languages[i]);
        cout << "File " << argv[i+2] << " distance to first file: " << distance << endl;
    }

    // Find the language with the minimum/maximum distance to the first language
    double minDistance = firstLanguage->getDistance(languages[0]);
    double maxDistance = minDistance;
    int minIndex = 0, maxIndex = 0;
    for (int i = 1; i < languages.size(); ++i) {
        double distance = firstLanguage->getDistance(languages[i]);
        if (distance < minDistance) {
            minDistance = distance;
            minIndex = i;
        }
        if (distance > maxDistance) {
            maxDistance = distance;
            maxIndex = i;
        }
    }

    // Print the language with the minimum/maximum distance to the first language
        cout << "Language with " << (isMin ? "minimum" : "maximum") << " distance to "
             << firstLanguage.getName() << ": " << resultLanguage->getName() << endl;
        cout << "Language identifier: " << resultLanguage->getIdentifier() << endl;

    // Free dynamically allocated memory
        delete firstLanguagePtr;
        for (Language* language : languages) {
            delete language;
        }

        return 0;
    }


    ..........................

    // Parse command line arguments
    string flag = ""; // -t min|max
    vector<string> filenames;
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-t" && i+1 < argc) {
            flag = argv[i+1];
            i++;
        } else {
            filenames.push_back(arg);
        }
    }

    // Check for invalid arguments
    if (filenames.size() < 2) {
        showEnglishHelp(cerr);
        return 1;
    }
    if (flag != "" && flag != "min" && flag != "max") {
        cerr << "Invalid flag " << flag << endl;
        showEnglishHelp(cerr);
        return 1;
    }

    // Load first Language object from file
    Language first(filenames[0]);
    if (!first.load()) {
        cerr << "Failed to load " << filenames[0] << endl;
        return 1;
    }

    // Allocate dynamic array to store Language objects
    Language* languages = new Language[filenames.size() - 1];

    // Load remaining Language objects from files
    for (int i = 1; i < filenames.size(); i++) {
        languages[i-1].setLanguageId(filenames[i]);
        if (!languages[i-1].load()) {
            cerr << "Failed to load " << filenames[i] << endl;
            return 1;
        }
    }

    // Print distances to each Language object
    for (int i = 0; i < filenames.size() - 1; i++) {
        cout << "Distance from " << filenames[0] << " to " << filenames[i+1] << ": ";
        cout << first.getDistance(languages[i]) << endl;
    }

    // Find Language with minimum or maximum distance
    int extremaIndex = 0;
    Language extremaLanguage = languages[0];
    for (int i =0; i < numLanguages - 1; i++) {
        if ((t == "min" && distances[i] < distances[extremaIndex]) ||
            (t == "max" && distances[i] > distances[extremaIndex])) {
            extremaIndex = i;
            extremaLanguage = languages[i+1];
        }
    }
    // Print results
    cout << "Results: " << endl;
    for (int i = 1; i < numLanguages; i++) {
        cout << languages[i].getFileName() << " ";
        cout << distances[i-1] << endl;
    }
    cout << "Language with " << t << " distance to " << languages[0].getFileName() << " is " << extremaLanguage.getFileName() << " with language identifier " << extremaLanguage.getLanguageIdentifier() << endl;

    // Deallocate memory
    delete[] languages;
    delete[] distances;

    return 0;
}