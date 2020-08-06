#include <iostream>
#include <math.h>
#include "latapeones.h"
#include "malla-revol.h"

using namespace std;

Lata::Lata(const std::string & nombreArchivoJPG){

    ponerNombre("Lata");

    agregar(MAT_Escalado(4.0,4.0,4.0));
    agregar(new Material(new Textura(nombreArchivoJPG),0.5,0.5,0.9,20));
    agregar(new MallaRevolPLY("../recursos/plys/lata-pcue.ply",50));

    agregar(new Material(0.3,0.3,0.7,30));
    agregar(new MallaRevolPLY("../recursos/plys/lata-psup.ply",50));

    agregar(new Material(0.3,0.3,0.7,30));
    agregar(new MallaRevolPLY("../recursos/plys/lata-pinf.ply",50));
}

LataPeones::LataPeones(){

    ponerNombre("Lata y peones");

    NodoGrafoEscena * lata_coke=new NodoGrafoEscena();
    lata_coke->ponerIdentificador(411);
    lata_coke->ponerNombre("Lata de Coca-Cola");
    lata_coke->agregar(new Lata("../recursos/imgs/lata-coke.jpg"));
    agregar(lata_coke);

    agregar(MAT_Traslacion(0.0,1.4,3.0));


    NodoGrafoEscena * peon_m=new NodoGrafoEscena();
    peon_m->ponerIdentificador(421);
    peon_m->ponerNombre("Peon de madera");
    peon_m->agregar(new Material(new TexturaXY("../recursos/imgs/text-madera.jpg"),0.2,0.3,0.4,30));   
    peon_m->agregar(new MallaRevolPLY("../recursos/plys/peon.ply",40));

    agregar(peon_m);

    agregar(MAT_Traslacion(2.5,0.0,0.0));
    NodoGrafoEscena * peon_b=new NodoGrafoEscena();
    peon_b->ponerIdentificador(422);
    peon_b->ponerNombre("Peon blanco");
    peon_b->agregar(new Material(0.1,0.9,0.0,1));
    peon_b->ponerColor({1.0,1.0,1.0});
    peon_b->agregar(new MallaRevolPLY("../recursos/plys/peon.ply",40));

    agregar(peon_b);

    agregar(MAT_Traslacion(2.5,0.0,0.0));
    NodoGrafoEscena * peon_n=new NodoGrafoEscena();
    peon_n->ponerIdentificador(423);
    peon_n->ponerNombre("Peon negro");
    peon_n->agregar(new Material(0.2,0.05,0.75,5));
    peon_n->ponerColor({0.2,0.2,0.2});
    peon_n->agregar(new MallaRevolPLY("../recursos/plys/peon.ply",40));

    agregar(peon_n);
}

VariasLatasPeones::VariasLatasPeones(){

    ponerNombre("Varias Latas y Peones");

    agregar(new LataPeones());

    agregar(MAT_Traslacion(4.0,0.0,0.0));
    NodoGrafoEscena * lata_pepsi=new NodoGrafoEscena();
    lata_pepsi->ponerIdentificador(412);
    lata_pepsi->ponerNombre("Lata de Pepsi");
    lata_pepsi->agregar(new Lata("../recursos/imgs/lata-pepsi.jpg"));
    agregar(lata_pepsi);
    
    agregar(MAT_Traslacion(4.0,0.0,0.0));
    NodoGrafoEscena * lata_ugr=new NodoGrafoEscena();
    lata_ugr->ponerIdentificador(413);
    lata_ugr->ponerNombre("Lata UGR"); 
    lata_ugr->agregar(new Lata("../recursos/imgs/window-icon.jpg"));
    agregar(lata_ugr);
}