/* 
 * File:   Diccionario.cpp
 * Author: aabedraba
 * 
 * Created on September 19, 2017, 9:55 AM
 */

#include "Diccionario.h"

/**
 * Constructor parametrizado de diccionario.
 * @param nomFich fichero con el que queremos crear nuestro diccionario.
 */
Diccionario::Diccionario( const std::string &nomFich )
    : _vec()
{
    std::ifstream fe;
    std::string linea;
    fe.open( nomFich.c_str() ); //convierte nomFich en legible por ifstream::open
    
    if ( !fe.good() ) {
        fe.close();
        throw std::invalid_argument("[Diccionario::cargaPalabras]No se pudo abrir"
                " el fichero. Sugerencia: ¿nombre de archivo invalido?");
    }
    
    while ( !fe.eof() ) {
        getline( fe, linea );
        if ( linea != "" ) {
            Palabra palabra(linea);
            _vec.insertar( palabra ); //La lista está ordenada
        }
    }
    fe.close();
}

Diccionario::Diccionario( const Diccionario& orig ) 
    : _vec ( orig._vec )
{}

Diccionario::~Diccionario() {
}


/**
 * Metodo que inserta una palabra en el diccionario a traves de un string.
 * @param palabra string de la nueva palabra que queremos introducir.
 * @param pos posicion donde colocaremos la nueva palabra y que se actualizará cuando se haga.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra ya existe.
 */
void Diccionario::inserta(const std::string &palabra, bool &insertado) {
    Palabra p( palabra );
    insertado = _vec.insertar( p );   
}

/**
 * Metodo que busca una palabra en el diccionario a traves de un string.
 * @param termino string de la palabra que queremos buscar.
 * @param pos posicion donde se encuentra dicha palabra y que se actualizara cuando se encuentre.
 * @return devuelve un objeto de tipo palabra con la palabra buscada.
 * @throw lanza una excepcion de tipo invalid_argument si la palabra no existe.
 */
Palabra &Diccionario::busca( const std::string &termino ) {
    Palabra aBuscar( termino );
    Palabra *p = new Palabra;
    if ( _vec.buscar( aBuscar, *p ) ) //true si se encuentra
        return *p;
    throw std::invalid_argument ("[Diccionario::busca]Palabra no encontrada");
}

/**
 * Metodo que entrena el diccionario con un archivo repleto de frases.
 * @param nomFich string con el nombre del fichero que usaremos para entrenar.
 * @throw excepcion de tipo invalid_argument si el archivo no se puede abrir.
 */
void Diccionario::usaCorpus(std::string nomFich) {
    std::ifstream fe;
    std::string frase;
    fe.open( nomFich.c_str() );
    if ( !fe.good() ){
        fe.close();
        throw std::invalid_argument( "[Diccionario::usaCorpus] No se pudo abrir"
                " el archivo. (¿Archivo incorrecto?)");
    }
    while ( !fe.eof() ){
        getline( fe, frase );
        entrena( frase );
    }
    fe.close();
}

/**
 * Metodo que a partir de una frase analizará las palabras que contiene y observará 
 el término que la precede y actualizará con él su lista de sucesores en el diccionario.
 * @param frase string que contiene la frase que usaremos.
 */
void Diccionario::entrena(const std::string frase) {
    std::stringstream ss( frase );
    std::string palabra, sucesor;
    
    ss >> palabra; 
    while ( !ss.eof() ){
        ss >> sucesor;
        if ( sucesor != "" ){
            Palabra pal( palabra );
            _vec.recuperaDato( pal ).introducirSucesor( sucesor );
            palabra = sucesor;
            sucesor = "";
        }   
    }
}

