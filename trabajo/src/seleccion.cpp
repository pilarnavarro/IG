#include "ig-aux.h"
#include "tuplasg.h"
#include "practicas.h"
#include "camara.h"
#include "fbo.h"
#include "seleccion.h"

// framebuffer object usado para selección
static Framebuffer * fbo = nullptr ;

// ---------------------------------------------------------------------

Framebuffer * FBOActual()
{
   return fbo ;
}

// ---------------------------------------------------------------------
// fijar el color actual en el cauce usando un identificador entero

void FijarColVertsIdent( Cauce & cauce, const int ident )  // 0 ≤ ident < 2^24
{
   // COMPLETAR: práctica 5: fijar color actual de OpenGL usando 'ident' (glColor3ub)
   const unsigned char 
      byteR = (ident) % 0x100U,  // rojo = byte menos significativo
      byteG = (ident/0x100U ) % 0x100U,   // verde = byte intermedio
      byteB = (ident/0x10000U ) % 0x100U; // azul = byte más significativo
      glColor3ub( byteR, byteG, byteB );  // cambio de color en OpenGL.
}

// ----------------------------------------------------------------------------------
// leer un identificador entero codificado en el color de un pixel en el
// framebuffer activo actualmente

int LeerIdentEnPixel( int xpix, int ypix )
{
   // COMPLETAR: práctica 5: leer el identificador codificado en el color del pixel (x,y)
  
   unsigned char bytes[3] ; // para guardar los tres bytes
   // leer los 3 bytes del frame-buffer
   glReadPixels( xpix,ypix, 1,1, GL_RGB,GL_UNSIGNED_BYTE, (void *)bytes);
   // reconstruir el indentificador y devolverlo:
   return bytes[0] + ( 0x100U*bytes[1] ) + ( 0x10000U*bytes[2] ) ;  
}

// -------------------------------------------------------------------------------
// Función principal de selección, se llama al hacer click con el botón izquierdo
//
// (x,y)       = posición donde se ha hecho click en coordenadas del sistema de ventanas (enteras)
// objeto_raiz = objeto raiz (no subobjeto de otro) que se está visualizando en la ventana
// cv_dib      = contexto de visualización usado para dibujar el objeto
//
// devuelve: true si se ha seleccionado algún objeto, false si no

bool Seleccion( int x, int y, Escena * escena, ContextoVis & cv_dib )
{
   using namespace std ;
   assert( escena != nullptr );

   // COMPLETAR: práctica 5:
   // Visualizar escena en modo selección y leer el color del pixel en (x,y)
   // Se deben de dar estos pasos:

   //cout << "Seleccion( x == " << x << ", y == " << y << ", obj.raíz ==  " << objeto_raiz.leerNombre() << " )" << endl ;

   // 1. Crear (si es necesario) y activar el framebuffer object (fbo) de selección
   
   if(fbo==nullptr){
     fbo= new Framebuffer(cv_dib.ventana_tam_x, cv_dib.ventana_tam_y);
   }

   // 2. crear un 'ContextoVis' apropiado, en ese objeto:
   //    * activar modo selecion, desactivar iluminación, poner modo relleno
   //    * usar el mismo cauce, y la misma cámara que en 'cv_dib'
   //    * fijar el tamaño de la ventana igual que en 'cv_dib'

  /*
   ContextoVis cv();

   cv.modo_seleccion=true;
   cv.iluminacion=false;
   cv.modo_visu=ModosVisu::relleno;
   cv.cauce_act=cv_dib.cauce_act;
   cv.ventana_tam_x=cv_dib.ventana_tam_x;
   cv.ventana_tam_y=cv_dib.ventana_tam_y;
  */ 

   ContextoVis cv(cv_dib);

   cv.modo_seleccion = true;
   cv.iluminacion = false;
   cv.dibujar_ejes = false;
   cv.modo_visu=ModosVisu::relleno;

   FijarColVertsIdent(*cv.cauce_act,0);


   // 3. Activar fbo, cauce y viewport. Configurar cauce (modo solido relleno, sin ilum.
   //    ni texturas). Limpiar el FBO (color de fondo: 0)
   
    fbo->activar(cv.ventana_tam_x, cv.ventana_tam_y);
    cv.cauce_act->activar();
    cv.cauce_act->fijarEvalMIL(false);

   glViewport(0,0,cv.ventana_tam_x, cv.ventana_tam_y);   

   glClearColor(0.0,0.0,0.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   // 4. Activar la cámara (se debe leer de la escena con 'camaraActual')
   
   escena->camaraActual()->activar(*cv.cauce_act);


   // 5. Visualizar el objeto raiz actual (se debe leer de la escena con 'objetoActual()')
   
   escena->objetoActual()->visualizarGL(cv);


   // 6. Leer el color del pixel (usar 'LeerIdentEnPixel')
   // (hay que hacerlo mientras está activado el framebuffer de selección)

   int ident=LeerIdentEnPixel(x,y);

   // 7. Desactivar el framebuffer de selección
   
   fbo->desactivar();


   // 8. Si el identificador del pixel es 0, imprimir mensaje y terminar (devolver 'false')
   
   if (ident==0){
      cout<<"Aquí no hay ningún objeto seleccionable\n";
      return false;
   } 


   // 9. Buscar el objeto en el objeto_raiz (puede ser un grafo de escena)
   //    e informar del nombre del mismo (si no se encuentra, indicarlo)
   //   (usar 'buscarObjeto')
   
   if(ident>0){
      Matriz4f mmodelado=MAT_Ident();
      Objeto3D ** objeto=new Objeto3D*; //¿?
      Tupla3f centro_wc;

      bool encontrado;
      encontrado=escena->objetoActual()->buscarObjeto(ident,mmodelado,objeto,centro_wc);

      if (!encontrado){
          cout<<"No se ha encontrado ningún objeto\n";
          return false;
      }else{
         cout<<"Objeto con identificador "<<ident<<" seleccionado. Se trata de: "<<(*objeto)->leerNombre()<<"\n";
      }
   
      escena->camaraActual()->mirarHacia(centro_wc);
   }
   
   // al final devolvemos 'true', ya que hemos encontrado un objeto
   return true ;
}
