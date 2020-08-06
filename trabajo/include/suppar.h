// *********************************************************************
// **
// ** Superficies paramétricas
// ** (declaraciones)
// **
// ** Copyright (C) 2014 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
//


#ifndef SUPPAR_HPP
#define SUPPAR_HPP


//**********************************************************************

#include <string>
#include <vector>
#include "tuplasg.h"
//#include "sbs_sbspline.hpp"


//**********************************************************************
// clase base para funciones de parametrización

class FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const = 0 ;
} ;

//**********************************************************************
// función de parametrización de un cuadrado de lado unidad

class FPCuadrado : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de una esfera

class FPEsfera : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de una semi-esfera (y>=0)

class FPSemiesfera : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización del cilindro

class FPCilindro : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de un disco

class FPDisco : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de un cono

class FPCono : public FunPar
{
   public:
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de un toro ()

class FPToro : public FunPar
{
   private:
      float rmayor,rmenor ;
   public:
   FPToro( const float p_rmayor, const float p_rmenor );
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

//**********************************************************************
// función de parametrización de un cuadrado de lado unidad en el plano XY

class FPCuadradoXY : public FunPar
{
   public:
   FPCuadradoXY( );
   virtual void eval( float u, float v, Tupla3f &pos, Tupla3f &nor ) const ;
} ;

#endif
