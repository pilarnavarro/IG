

#include "ig-aux.h"
#include "escena.h"

#include "objeto3d.h"
#include "malla-ind.h"
#include "malla-revol.h"
#include "practicas.h"
#include "camara.h"
#include "materiales-luces.h"
#include "seleccion.h"
#include "modelo-jer.h"
#include "latapeones.h"




// -----------------------------------------------------------------------------------------------

Escena::Escena()
{
   // COMPLETAR: Práctica 4: inicializar 'col_fuentes' y 'material_ini'
   
   col_fuentes=new Col2Fuentes();
   material_ini=new Material();



   // COMPLETAR: Práctica 5: hacer 'push_back' de varias camaras perspectiva u ortogonales,
   // (sustituir la cámara orbital simple ('CamaraOrbitalSimple') por varias cámaras de 3 modos ('Camara3Modos')

  camaras.push_back(new Camara3Modos(true, {8.0,0.0,0.0}, 2.0, {0.0,0.0,0.0},60.0));
  camaras.push_back(new Camara3Modos(true, {8.0,8.0,8.0}, 1.5, {0.0,0.0,0.0},80.0));  
  camaras.push_back(new Camara3Modos(false, {0.0,0.0,8.0}, 1.0, {0.0,0.0,0.0}));

}


// visualización de las normales de los objetos de una escena.
// se puede llamar al final de 'Escena::visualizarGL' para ver las normales además del modelo.
// cambia el estado del cauce (cv.cauce_act), desactiva iluminación entre otras cosas.
// no modifica 'cv'
// requiere añadir 'visualizando_normales' al contexto de visualización
void Escena::visualizarNormales( ContextoVis & cv )
{
   // guardar y fijar los valores de algunos parámetros de configuración
   bool ilum_prev = cv.iluminacion ;
        // fco_prev  = cv.fijar_colores_objetos ;

   // recuperar el objeto raiz de esta escena y comprobar que está ok.
   assert( cv.cauce_act != nullptr );
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // desactivar iluminación
   cv.iluminacion = false ;
   glColor3f( 1.0, 0.7, 0.7 );
   cv.cauce_act->fijarEvalMIL( false );
   cv.cauce_act->fijarEvalText( false );
   cv.cauce_act->fijarModoSombrPlano( true ); // sombreado plano
   glLineWidth( 2.9 );

   // desactivar VAOs y VBOs
   glBindVertexArray( 0 );
   glBindBuffer( GL_ARRAY_BUFFER, 0 );
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

   // desactivar punteros a tablas de atributos (distinto de las posiciones)
   glDisableClientState( GL_COLOR_ARRAY );
   glDisableClientState( GL_TEXTURE_COORD_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );

   // habilitar puntero a tabla de vértices
   glEnableClientState( GL_VERTEX_ARRAY );

   // dibujar objeto raiz actual
   cv.visualizando_normales = true ;   // hace que MallaInd::visualizarGL visualize las normales.
   objetos[ind_objeto_actual]->visualizarGL( cv );
   cv.visualizando_normales = false ;

   // restaurar algunos parámetros en 'cv' a su estado previo a esta llamada
   cv.iluminacion = ilum_prev ;

}

// -----------------------------------------------------------------------------------------------
// visualiza la escena en la ventana actual, usando la configuración especificada en 'cv'

void Escena::visualizarGL( ContextoVis & cv )
{
   using namespace std ;

   // recuperar el cauce actual de 'cv' en 'cauce', activarlo
   Cauce * cauce = cv.cauce_act ; assert( cauce != nullptr );
   cauce->activar() ;

   // recuperar la cámara actual de esta escena y  fijar las matrices 'modelview'
   // y 'projection' en el cauce gráfico (es decir: activar la cámara actual)
   CamaraInteractiva * camara = camaras[ind_camara_actual] ; assert( camara != nullptr );
   const float ratio_vp = float(cv.ventana_tam_y)/float(cv.ventana_tam_x) ;
   camara->fijarRatioViewport( ratio_vp );
   camara->activar( *cauce ) ;


   // dibujar los ejes, si procede
   if ( cv.dibujar_ejes  )
      DibujarEjesSolido( *cauce ) ;

   // fijar el color por defecto en el cauce para dibujar los objetos
   glColor3f( 1.0, 1.0, 1.0 );

   // COMPLETAR: Práctica 1: Configurar el cauce en función de:
   //    cv.sombr_plano (true/false)              --> usar fijarModoSombrPlano (método del 'cauce')
   //    cv.modo_visu   (puntos,lineas o relleno) --> usar glPolygonMode

   cauce->fijarModoSombrPlano(cv.sombr_plano);
   
   switch(cv.modo_visu) {
      case ModosVisu::lineas : glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
      case ModosVisu::puntos : glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); break;
      case ModosVisu::relleno : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
   }


   if ( cv.iluminacion )
   {
      // COMPLETAR: Práctica 4: activar evaluación del MIL (y desactivar texturas)
      // * comprobar que existe la coleccion de fuentes (col_fuentes)
      // * comprobar que existe el material inicial (material_ini)
      // * activar la colección de fuentes y el material inicial
      // ....

       cauce->fijarEvalMIL(true);
       cauce->fijarEvalText(false);
       
       if(col_fuentes!=nullptr) col_fuentes->activar(*cauce);
       
       if(material_ini!=nullptr){
          cv.material_act=material_ini;
          cv.material_act->activar(*cauce);
       }
       

   }
   else // si la iluminación no está activada, deshabilitar MIL y texturas
   {  cauce->fijarEvalMIL( false );
      cauce->fijarEvalText( false );
   }

   // recuperar el objeto actual de esta escena
   Objeto3D * objeto = objetos[ind_objeto_actual] ; assert( objeto != nullptr );

   // COMPLETAR: Práctica 1: visualizar el objeto actual ('objeto')

   objeto->visualizarGL(cv);

   if(cv.visualizar_normales) visualizarNormales(cv);


   // si hay un FBO, dibujarlo:

}

// -----------------------------------------------------------------------------------------------
// pasa la cámara actual a la siguiente

void Escena::siguienteCamara()
{
   assert( ind_camara_actual < camaras.size() );
   ind_camara_actual = (ind_camara_actual+1 ) % camaras.size();
   using namespace std ;
   cout << "Cámara actual cambiada a: " << (ind_camara_actual+1) << " (de " << camaras.size() << ")" << endl ;
}

// -----------------------------------------------------------------------------------------------
// pasa el objeto actual al siguiente

void Escena::siguienteObjeto()
{
   if ( objetos.size() == 0 )
      return ;
   assert( ind_objeto_actual < objetos.size() );
   ind_objeto_actual = (ind_objeto_actual+1 ) % objetos.size();
   using namespace std ;
   cout << "Objeto actual cambiado a: " << objetoActual()->leerNombre()
        << " (" << (ind_objeto_actual+1) << "/" << objetos.size() << ")." << endl  ;
}

// -----------------------------------------------------------------------------------------------
// devuelve puntero al objeto actual

Objeto3D * Escena::objetoActual()
{
   assert( ind_objeto_actual < objetos.size() );
   assert( objetos[ind_objeto_actual] != nullptr );
   return objetos[ind_objeto_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la cámara actual

CamaraInteractiva * Escena::camaraActual()
{
   assert( ind_camara_actual < camaras.size() );
   assert( camaras[ind_camara_actual] != nullptr );
   return camaras[ind_camara_actual] ;
}
// -----------------------------------------------------------------------------------------------
// devuelve un puntero a la colección de fuentes actual

ColFuentesLuz * Escena::colFuentes()
{
   assert( col_fuentes != nullptr );
   return col_fuentes ;
}
// -----------------------------------------------------------------------------------------------

Escena1::Escena1()
{
   using namespace std ;
   cout << "Creando objetos de escena 1 .... " << flush ;

   // añadir el objeto 'Cubo' a la lista de objetos de esta escena:
   objetos.push_back( new Cubo() );
   
   // COMPLETAR: Práctica 1: creación del resto objetos de la práctica 1
   // Añadir objetos al vector 'objetos', con:
   //     objetos.push_back( new .... )
   // .........

   objetos.push_back( new Tetraedro({0.5,0.25,0.75}) );
   objetos.push_back( new CuboColores() );
   //objetos.push_back( new Diamante());



   cout << "hecho." << endl << flush ;
}


// -------------------------------------------------------------------------
// COMPLETAR: Práctica 2
// Añadir la implementación del constructor de la clase Escena2 para construir
// los objetos que se indican en los guiones de las práctica 2
// .......

Escena2::Escena2()
{
   using namespace std ;
   cout << "Creando objetos de escena 2 .... " << flush ;

   objetos.push_back(new MallaPLY("../recursos/plys/beethoven.ply"));
   objetos.push_back(new MallaPLY("../recursos/plys/big_dodge.ply"));
   objetos.push_back(new MallaPLY("../recursos/plys/ant.ply"));
   objetos.push_back(new MallaRevolPLY("../recursos/plys/peon.ply",20));
   objetos.push_back(new Cilindro(10,20));
   objetos.push_back(new Esfera(20,30));
   objetos.push_back(new Cono(10,20));
   //objetos.push_back(new Puente(10,20));
   //objetos.push_back(new Prueba1(10,20));
   //objetos.push_back(new MallaRevolPLY("./plys/prueba2.ply",10));


   cout << "hecho." << endl << flush ;
}

// -------------------------------------------------------------------------
// COMPLETAR: Práctica 3
// Añadir la implementación del constructor de la clase Escena3 para construir
// los objetos que se indican en los guiones de las práctica 3
// .......

Escena3::Escena3()
{
   using namespace std ;
   cout << "Creando objetos de escena 3 .... " << flush ;

   //objetos.push_back(new Oreja(30));
   //objetos.push_back(new Pupila(0.0));
   //objetos.push_back(new Ojo(1));
   //objetos.push_back(new Cabeza());
   //objetos.push_back(new Pierna(0));
   objetos.push_back(new C(0));

   
   cout << "hecho." << endl << flush ;
}

// ----------------------------------------------------------------------
// COMPLETAR: Práctica 4
// Añadir la implementación del constructor de la clase Escena4 para construir
// los objetos que se indican en los guiones de las práctica 4
// .......

Escena4::Escena4()
{
   using namespace std ;
   cout << "Creando objetos de escena 4 .... " << flush ;

   objetos.push_back( new NodoCubo24() );
   objetos.push_back(new Lata("../recursos/imgs/lata-coke.jpg"));
   objetos.push_back(new LataPeones());
   

   cout << "hecho." << endl << flush ;
}


// ----------------------------------------------------------------------
// COMPLETAR: Práctica 5
// Añadir la implementación del constructor de la clase Escena5 para construir
// los objetos que se indican en los guiones de las práctica 5
// .......

Escena5::Escena5()
{
   using namespace std ;
   cout << "Creando objetos de escena 5 .... " << flush ;

   objetos.push_back(new VariasLatasPeones());
   
   cout << "hecho." << endl << flush ;
}

