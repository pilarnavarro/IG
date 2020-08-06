#include <iostream>
#include <math.h>
#include "modelo-jer.h"
#include "malla-revol.h"

using namespace std;

Oreja::Oreja(const float ang_z){
    ponerNombre("Oreja");
    unsigned ind1= agregar(MAT_Rotacion(ang_z,{0,0,1}));
    agregar(MAT_Escalado(1,0.5,0.3));
    agregar(MAT_Traslacion(1,0,0));
    agregar(new Material(new Textura("./imgs/hoja.jpg"),0.7,0.2,0.1,2));
    agregar(new Esfera());
    ponerColor({0.283,0.788,0.69});

    pm_rotz_oreja=leerPtrMatriz(ind1);
}

void Oreja::act_ang_z(const float tSec){
    float vmin=-60;
    float vmax=60;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.2*tSec);
    
    *pm_rotz_oreja=MAT_Rotacion(v,{0,0,1});
}

/*void Oreja::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        act_ang_z(tSec);
        break;
    default:
        break;
    }
}*/


Pupila::Pupila(const float pos_inicial){
    ponerNombre("Pupila");
    unsigned ind1= agregar(MAT_Traslacion(pos_inicial,0,0));
    agregar(MAT_Traslacion(0,0,0.1));
    agregar(MAT_Escalado(0.15,0.15,0.1));
    agregar(new Material(0.2,0.3,0.4,30));
    agregar(new Esfera());
    ponerColor({0,0,0});

    pm_des_hor=leerPtrMatriz(ind1);
}

//La pupila se mueve entre [-0.3,0.3] en el eje x
void Pupila::act_des_hor(const float t_sec){
    float vmin=-0.15;
    float vmax=0.15;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.5*t_sec);
    
    *pm_des_hor=MAT_Traslacion(v,0,0);

}

Ojo::Ojo(const float tam_ojo){
    ponerNombre("Ojo"); 
    unsigned ind1=agregar(MAT_Escalado(tam_ojo,tam_ojo,1));
    p= new Pupila(0.0);
    agregar(p);
    agregar(new Material(0.5,0.3,0.2,5));
    agregar(MAT_Escalado(0.3,0.3,0.1));
    agregar(new Esfera());   

    pm_tam_ojo=leerPtrMatriz(ind1); 
}

void Ojo::act_tam(const float tsec){
    float vmin=0.8;
    float vmax=1.5;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.3*tsec);
    
    *pm_tam_ojo=MAT_Escalado(v,v,1);
}


void Ojo::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        p->act_des_hor(tSec);
        break;
    case 1:
        act_tam(tSec);
        break;
    default:
        break;
    }
}

Cabeza::Cabeza(){
    
    ponerNombre("Cabeza");
    //ponerIdentificador(-1);
    
    NodoGrafoEscena *base=new NodoGrafoEscena();
    base-> ponerColor({0.043,0.47,0.93});   
    base->agregar(MAT_Escalado(1.5,1.5,1.5));
    base->agregar(new Material(new Textura("./imgs/hojas3.jpg"),0.6,0.2,0.2,3));
    base->ponerIdentificador(30);
    base->ponerNombre("Cabeza");
    base->agregar(new Cono(10,40));
    agregar(base);
     
    NodoGrafoEscena * mod_oreja2=new NodoGrafoEscena();
    oreja2=new Oreja(30);
    oreja2->ponerIdentificador(20);
    oreja2->ponerNombre("Oreja derecha");
    mod_oreja2-> agregar(MAT_Traslacion(0.45,1,0));  
    mod_oreja2->agregar(oreja2);
    agregar(mod_oreja2);

    NodoGrafoEscena * mod_oreja1=new NodoGrafoEscena();
    oreja1=new Oreja(30);
    oreja1->ponerIdentificador(21);
    oreja1->ponerNombre("Oreja izquierda");
    mod_oreja1->agregar(MAT_Escalado(-1,1,1));
    mod_oreja1-> agregar(MAT_Traslacion(0.45,1,0));
    mod_oreja1->agregar(oreja1);
    agregar(mod_oreja1);
    

    NodoGrafoEscena * mod_ojo2=new NodoGrafoEscena();
    //mod_ojo2->agregar(MAT_Escalado(-1,1,1));
    ojo2=new Ojo(1);
    ojo2->ponerIdentificador(11);
    ojo2->ponerNombre("Ojo izquierdo");
    mod_ojo2->agregar(MAT_Traslacion(-0.5,0.5,1));   
    mod_ojo2->agregar(MAT_Rotacion(-45,{0,1,0}));
    mod_ojo2->agregar(MAT_Rotacion(-30,{1,0,0}));    
    mod_ojo2->agregar(ojo2);
    agregar(mod_ojo2);

    NodoGrafoEscena * mod_ojo1=new NodoGrafoEscena();
    ojo1=new Ojo(1);
    ojo1->ponerIdentificador(10);
    ojo1->ponerNombre("Ojo derecho");
    mod_ojo1->agregar(MAT_Traslacion(0.5,0.5,1));   
    mod_ojo1->agregar(MAT_Rotacion(45,{0,1,0}));
    mod_ojo1->agregar(MAT_Rotacion(-30,{1,0,0}));   
    mod_ojo1->agregar(ojo1);
    agregar(mod_ojo1);
    
}


void Cabeza::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        oreja2->act_ang_z(tSec);
        break;
    case 1:
        oreja1->act_ang_z(tSec);
        break;
    case 2:
    case 3:
        ojo2->actualizarEstadoParametro((iParam-2),tSec);
        break;
    case 4:
    case 5:
        ojo1->actualizarEstadoParametro((iParam-4),tSec);
        break;
    default:
       break;
    }

}

Pierna::Pierna(/*const float tam_inicial,*/ const float ang_inicial){
    ponerNombre("Pierna");
    ponerColor({0.612,0.5176,0.96});
   
    //unsigned ind1=agregar(MAT_Traslacion(0,0,0));
    //unsigned ind2=agregar(MAT_Escalado(1,tam_inicial,1));
    
    agregar(MAT_Traslacion(0.7,0,0));
    unsigned ind1=agregar(MAT_Rotacion(ang_inicial,{1,0,0}));
    agregar(MAT_Traslacion(0,-1.7,0));
    NodoGrafoEscena * pie= new NodoGrafoEscena();
    pie->agregar(MAT_Escalado(0.5,0.3,0.5));
    pie->agregar(new Material(new Textura("./imgs/cesped2.jpg"),0.6,0.3,0.1,2));
    pie->agregar(new Esfera());
    agregar(pie);

    NodoGrafoEscena * mod_pierna=new NodoGrafoEscena();
    
    mod_pierna-> agregar(MAT_Escalado(0.2,2,0.2));
    mod_pierna->agregar(new Material(new Textura("./imgs/bambu.jpg"),0.5,0.2,0.3,5));
    mod_pierna->agregar(new Cilindro(10,30));
    agregar(mod_pierna);

    pm_rot_pierna=leerPtrMatriz(ind1);

    /*pm_rot_pierna=leerPtrMatriz(ind1);
    pm_esc_pierna=leerPtrMatriz(ind2);*/
}

void Pierna::act_rot_pierna(const float tsec){
    float vmin=-45;
    float vmax=45;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.4*tsec);

    *pm_rot_pierna=MAT_Rotacion(v,{1,0,0});
}


/*void Pierna::act_tam_pierna(const float tsec){
    float vmin=1.5;
    float vmax=0.75;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.4*tsec);

    *pm_rot_pierna=MAT_Traslacion(0,(1-(2*v)),0);
    *pm_esc_pierna=MAT_Escalado(1,v,1);
}*/
        
/*
void Pierna::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        act_rot_pierna(tSec);
        break;
    /*case 1:
        act_rot_pierna(tSec);
        break;*/
    /*default:
        break;
    }

}
*/

C::C(/*const float pos_inicial,*/const float ang_inicial){

    ponerNombre("C");
    ponerIdentificador(-1);
    
    unsigned ind1=agregar(MAT_Rotacion(ang_inicial,{0,1,0}));
    //unsigned ind2=agregar(MAT_Traslacion(pos_inicial,0,0));
    //agregar(MAT_Traslacion(-1.5,0,0));

    c=new Cabeza();
    c->ponerIdentificador(-1);
    agregar(c);
    

    //NodoGrafoEscena * mod_p2=new NodoGrafoEscena();
    p2=new Pierna(0);
    p2->ponerIdentificador(40);
    p2->ponerNombre("Pierna derecha");    
    agregar(p2); 
    //agregar(mod_p2);  

    //NodoGrafoEscena * mod_p=new NodoGrafoEscena();
    p1=new Pierna(0);
    p1->ponerIdentificador(41);
    p1->ponerNombre("Pierna izquierda");
    agregar(MAT_Escalado(-1,1,1));   
    agregar(p1);
    //agregar(mod_p);

    pm_rot=leerPtrMatriz(ind1);
    //pm_pos=leerPtrMatriz(ind2);
}

void C::act_rot(const float tsec){
    
    *pm_rot=MAT_Rotacion((2*M_PI*3*tsec),{0,1,0});
}

/*
void C::act_pos(const float tsec){
    float vmin=-1;
    float vmax=1;
    float a=(vmin + vmax )/2;
    float b =(vmax-vmin )/2;
    float v=a+b*sin(2*M_PI*0.3*tsec);
    
    *pm_pos=MAT_Traslacion(v,0,0);
}*/

void C::actualizarEstadoParametro(const unsigned iParam,const float tSec){
    switch(iParam)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        c->actualizarEstadoParametro(iParam,tSec);
        break;
    case 6:
        p1->act_rot_pierna(tSec);
        break;
    case 7:
        p2->act_rot_pierna(tSec+1.25);
        break;
    case 8:
        act_rot(tSec);
        break;
    //case 9:
        //act_pos(tSec);
    default:
        break;
    }

}