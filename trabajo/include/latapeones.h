#ifndef LATAPEONES_HPP
#define LATAPEONES_HPP


#include "grafo-escena.h"
#include "malla-ind.h"
#include "materiales-luces.h"

class LataPeones: public NodoGrafoEscena{
    public:
    LataPeones();
};

class Lata: public NodoGrafoEscena{
    public:
    Lata(const std::string & nombreArchivoJPG);
};

class VariasLatasPeones: public NodoGrafoEscena{
    public:
    VariasLatasPeones();
};


#endif