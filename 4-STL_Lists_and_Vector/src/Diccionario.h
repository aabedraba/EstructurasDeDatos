/* 
 * File:   Diccionario.h
 * Author: aabedraba
 *
 * Created on September 19, 2017, 9:55 AM
 */

#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include "Palabra.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>

class Diccionario {
    
public:
    Diccionario( const std::string &nomFich );
    Diccionario( const Diccionario& orig );
    virtual ~Diccionario();
    
    Palabra& busca( const std::string &termino, unsigned int &pos );
    void inserta( const std::string &palabra, unsigned int& pos, bool &insertado );
    void elimina ( const std::string &palabra, bool& eliminado );
    void usaCorpus ( std::string nomFich );
    void entrena ( const std::string frase );
    
private:
    std::vector<Palabra> _vec;
    int numPalabras;
};
#endif /* DICCIONARIO_H */

