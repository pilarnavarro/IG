// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "tuplasg.h"
#include "lector-ply.h"
#include "matrices-tr.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{

// COMPLETAR: Práctica 2: completar: creación de la malla....

/* //Barrido
 int num_verts=perfil.size();
   vertices.clear();
   triangulos.clear();
   for(int i=0;i<num_copias;i++){
      for(int j=0;j<num_verts;j++){
         Tupla3f q=MAT_Traslacion(0,0,(float)i/(num_copias-1))*perfil[j];
         vertices.push_back(q);
      }
   }

   for(int i=0;i<num_copias-1;i++){
      for(int j=0;j<num_verts-1;j++){
         int k=i*num_verts+j;
         triangulos.push_back({k,k+num_verts,k+num_verts+1});
         triangulos.push_back({k,k+num_verts+1,k+1});
      }
   }
*/

   //Cálculo de las normales
   vector<Tupla3f> nor_aristas;
   Tupla3f m;
   for (int i=0;i<perfil.size()-1;i++){
      m=perfil[i+1]-perfil[i];
      nor_aristas.push_back({m(1),-m(0),0.0});  //¿?
      if(nor_aristas[i](0)!=0 || nor_aristas[i](1)!=0 || nor_aristas[i](2)!=0)
       nor_aristas[i]=nor_aristas[i].normalized();
   }

   vector<Tupla3f> nor_ver_aux;

   nor_ver_aux.push_back(nor_aristas[0]);

   for (int i=1;i<perfil.size()-1;i++){
      nor_ver_aux.push_back(nor_aristas[i-1]+nor_aristas[i]);
      if(nor_ver_aux[i](0)!=0 || nor_ver_aux[i](1)!=0 || nor_ver_aux[i](2)!=0)
         nor_ver_aux[i]=nor_ver_aux[i].normalized();
   }

   nor_ver_aux.push_back(nor_aristas[nor_aristas.size()-1]);

   
   //Cálculo de coordenadas de textura

   vector<float> d;

   for(int i=0;i<perfil.size()-1;i++){
      d.push_back(sqrt(pow(perfil[i+1](X)-perfil[i](X),2.0)+pow(perfil[i+1](Y)-perfil[i](Y),2.0)));
   }

   float tam=0.0;
   
   for (int i=0;i<d.size();i++){
      tam+=d[i];
   }

   vector<float> t (perfil.size(),0.0);

   for (int i=0;i<t.size()-1;i++){
      for (int j=0;j<i;j++){
         t[i]+=d[j];
      }

      t[i]=t[i]/tam;
   }

   t.back()=1.0;  

   //Tabla de vértices  
   int num_verts=perfil.size();
   vertices.clear();
   triangulos.clear();
   Tupla3f q,n;
   for(int i=0;i<num_copias;i++){
      for(int j=0;j<num_verts;j++){
         q=MAT_Rotacion((2*180*i)/(num_copias-1),{0,1,0})*perfil[j];
         vertices.push_back(q);

         n=MAT_Rotacion((2*180*i)/(num_copias-1),{0,1,0})*nor_ver_aux[j]; //¿?
         nor_ver.push_back(n);

         cc_tt_ver.push_back({1.0-(float)i/(num_copias-1),1-t[j]});
      }
   }

   //Tabla de triángulos
   for(int i=0;i<num_copias-1;i++){
      for(int j=0;j<num_verts-1;j++){
         int k=i*num_verts+j;
         triangulos.push_back({k,k+num_verts,k+num_verts+1});
         triangulos.push_back({k,k+num_verts+1,k+1});
      }
   }
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   
   vector<Tupla3f> perfil;
   
   LeerVerticesPLY(nombre_arch,perfil);

   inicializar(perfil,nperfiles);

}

//x=1
Cilindro::Cilindro(const int num_verts_per, const unsigned nperfiles){

   ponerNombre( std::string("malla por revolución: cilindro" ));
   
   vector<Tupla3f> perfil;
   perfil.push_back({0,0,0});
   perfil.push_back({1,0,0});
   float y;
   for(float i=0 ;i < num_verts_per; i++){
      y=i/(num_verts_per-1);
      perfil.push_back({1,y,0});
   }

   perfil.push_back({1,1,0});
   perfil.push_back({0,1,0});

   inicializar(perfil,nperfiles);

}

//y=-x+1  (Recta que pasa por (1,1))
Cono::Cono(const int num_verts_per, const unsigned nperfiles){

   ponerNombre( std::string("malla por revolución: cono" ));
   
   vector<Tupla3f> perfil;
  
   perfil.push_back({0,0,0});
   perfil.push_back({1,0,0});
   for(float i= 0;i < num_verts_per;i++){
      float x=(num_verts_per-1-i)/(num_verts_per-1);
      perfil.push_back({x,-x+1,0});
   }

   /*
   for(int i = 0; i < num_verts_per; i++)
    perfil.push_back({1-(float)i/(num_verts_per-1),(float)i/(num_verts_per-1),0});
   */

   inicializar(perfil,nperfiles);

}


Esfera::Esfera(const int num_verts_per, const unsigned nperfiles){
   
   ponerNombre( std::string("malla por revolución: esfera" ));
  
  vector<Tupla3f> perfil; 
   
   for(float i = 0; i < num_verts_per; i++){
    float x=i/(num_verts_per-1);
    //float ang = 0.5*M_PI*x; Semiesfera
    float ang = M_PI*(x-(float)1/2);
    perfil.push_back({cos(ang),sin(ang),0});
  }
  
  //y=sqrt(1-x^2)
  /*vector<Tupla3f> perfil;
   for(float i= 0;i < num_verts_per ;i++){
      float x=i/num_verts_per;
      perfil.push_back({x,sqrt(1-x*x),0});
      
   }

   for(float i= 0;i < num_verts_per ;i++){
      float x=(num_verts_per-i)/num_verts_per;
      perfil.push_back({x,-sqrt(1-x*x),0});
   }*/

   inicializar(perfil,nperfiles);

}

//Fijo unos valores en el constructor vacío con los que la esfera se ve bien
//Para usarlo más cómodamente en la práctica 3
Esfera::Esfera()
: Esfera(20,30){}

/*Prueba1::Prueba1( const int num_verts_per,const unsigned nperfiles){
   
   vector<Tupla3f> perfil={
      {0,-1,0}, {1,-1,0}
   };
   
   for(float i = 0; i < num_verts_per; i++){
    float x=i/(num_verts_per-1);
    float ang = M_PI*(x-(float)1/2);
    perfil.push_back({1+(-cos(ang)*0.75),sin(ang)*0.75,0});
  }

   perfil.push_back({1,1,0});
   perfil.push_back({0,1,0});

  /*perfil.push_back({0,-1.5,0});
  perfil.push_back({1.5,-1.5,0});


  for(int i = 0; i < num_verts_curva; i++){
    float alpha = M_PI*(float)i/(num_verts_curva-1);		
    perfil.push_back({1.5-sin(alpha),-cos(alpha),0});
  }


  perfil.push_back({1.5,1.5,0});
  perfil.push_back({0,1.5,0});
*/

/*   inicializar(perfil,nperfiles);


}*/


/*Puente::Puente( const int num_verts_per,const unsigned nperfiles){
   
   vector<Tupla3f> perfil={
      {0.5,0,0}, {1,0,0}, {1,1,0}, {-1,1,0}, {-1,0,0}, {-0.5,0,0}
   };
   
   /*perfil.push_back({0.5,0,0});
   perfil.push_back({1,0,0});
   perfil.push_back({1,1,0});
   perfil.push_back({-1,1,0});
   perfil.push_back({-1,0,0});
   perfil.push_back({-0.5,0,0});*/
   
   /*for(float i = 0; i < num_verts_per; i++){
    float x=i/(num_verts_per-1);
    float ang = M_PI*(1-x);
    perfil.push_back({(float)(cos(ang))/2,(float)(sin(ang))/2,0});
  }

  inicializar(perfil,nperfiles);


}*/




