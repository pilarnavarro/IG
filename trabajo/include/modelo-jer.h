#ifndef MODELO_JER_HPP
#define MODELO_JER_HPP

//#include <obj-gra.hpp>
//#include <materiales.hpp>

#include "grafo-escena.h"
#include "malla-ind.h"


class Oreja : public NodoGrafoEscena{
    protected:
        Matriz4f *pm_rotz_oreja=nullptr;
    public:
        Oreja(const float ang_z);
        void act_ang_z(const float tsec);
        //unsigned leerNumParametros() const{return 1;};
        //void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Pupila : public NodoGrafoEscena{
    protected:
        Matriz4f *pm_des_hor=nullptr;
    public:
        Pupila(const float pos_inicial);
        void act_des_hor(const float t_sec);
};

class Ojo : public NodoGrafoEscena{    
    protected:
        Pupila *p=nullptr;
        Matriz4f *pm_tam_ojo=nullptr;
    public:
        Ojo(const float tam_ojo); 
        void act_tam(const float tsec);
        unsigned leerNumParametros() const{return 2;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);  
};

class Cabeza : public NodoGrafoEscena{
    protected:
        Ojo *ojo1=nullptr;
        Ojo *ojo2=nullptr;
        Oreja *oreja1=nullptr;  
        Oreja *oreja2=nullptr;  
    public:
        Cabeza();
        unsigned leerNumParametros() const{return 6;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};


class Pierna : public NodoGrafoEscena{
    protected:
        Matriz4f *pm_rot_pierna=nullptr;
        //Matriz4f *pm_esc_pierna=nullptr;
    public:
        Pierna(/*const float tam_inicial,*/const float ang_inicial);
        void act_rot_pierna(const float tsec);
        //void act_tam_pierna(const float tsec);
        //unsigned leerNumParametros() const{return 1;};
        //void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class C : public NodoGrafoEscena{
    protected:
       Pierna * p1=nullptr;
       Pierna * p2=nullptr;
       Cabeza * c=nullptr;
       Matriz4f *pm_rot=nullptr;
       //Matriz4f *pm_pos=nullptr;

    public:
        C(/*const float pos_inicial,*/const float ang_inicial);
        void act_rot(const float tsec);
        //void act_pos(const float tsec);
        unsigned leerNumParametros() const{return 9;};
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

#endif