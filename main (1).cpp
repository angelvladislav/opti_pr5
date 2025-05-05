 /*
 *  Programa principal.
 *
 *
 *               Autores : Angel Vladislav Alonso Yemelyantseva
 *               Correo : alu0101489827
 *               Cursos  : 2024-25
 */

 #include <string.h>
 #include "grafo.h"
 
 void pressanykey()
 {   
     char c;
     //system("pause"); s�lo en windows
     cout << endl;
     cout << "pulsa [c] para continuar: ";
     cin >> c;
 }
 
 void menu (unsigned dirigido, char &opcion)
 //Expresion del menu de opciones segun sea un grafo dirigido o no dirigido
 {
     cout << "Optimiza!cion en Grafos, 2021-2022 NOMBRE DEL ESTUDIANTE" << endl;
     cout << "c. [c]argar grafo desde fichero" << endl;
     if (dirigido == 0) //Grafo no dirigido
             {
             cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
             cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
             cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
             cout << "n. Mostrar el MST mediante algoritmo de Solli[n]" << endl;
         //Aqu� se a�aden m�s opciones al men� del grafo no dirigido
             }
     else
             {
             cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
             cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
             cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
             cout << "o. Mostrar c[o]mponentes fuertemente conexas del grafo" << endl;
             cout << "x. Mostrar componentes cone[x]as del grafo" << endl;
             cout << "w. Mostrar caminos minimos usando Floyd_[W]arshall" << endl;
         //Aqu� se a�aden m�s opciones al men� del grafo dirigido
             };
     cout << "q. Finalizar el programa" << endl;
     cout << "Introduce la letra de la accion a ejecutar  > ";
     cin >> opcion;
 };
 
 
 // El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
 int main(int argc, char *argv[])
 {
     int error_apertura;
     char nombrefichero[85], opcion;
     int l;
     clrscr();
     //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
     if (argc > 1)
     {
     cout << "Cargando datos desde el fichero dado como argumento" << endl;
         strcpy(nombrefichero, argv[1]);
     }
     else
     {
         cout << "Introduce el nombre completo del fichero de datos" << endl;
         cin >> nombrefichero;
     };
     GRAFO G(nombrefichero, error_apertura);
     if (error_apertura == 1)
     {
         cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
         pressanykey();
         clrscr();
     }
     else
     {
         cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
         pressanykey();
         clrscr();
         do
         {
             menu(G.Es_dirigido(), opcion);
             switch (opcion)
             {
                 case 'c' :
                     clrscr();
                  cout << "Introduce el nombre completo del fichero de datos" << endl;
                     cin >> nombrefichero;
                     G.actualizar(nombrefichero, error_apertura);
                     if (error_apertura == 1)
                     {
                         cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
                     }
                     else
                     {
                         cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
                     };
                     pressanykey();
                     clrscr();
                     break;
 
                 case 'i' :
                     clrscr();
                     cout << "Grafo cargado desde " << nombrefichero << endl;
                     G.Info_Grafo();
                     pressanykey();
                     clrscr();
                     break;

                 case 's' :
                     clrscr();
                     l = 1;
                     G.Mostrar_Listas(l);
                     pressanykey();
                     clrscr();
                     break;

                 case 'p' :
                     clrscr();
                     l = -1;
                     G.Mostrar_Listas(l);
                     pressanykey();
                     clrscr();
                     break;

                 case 'a' :
                     clrscr();
                     l = 0;
                     G.Mostrar_Listas(l);
                     pressanykey();
                     clrscr();
                     break;
                 
                 case 'o' :
                     clrscr();
                      if (G.Es_dirigido() == 0){
                         G.ComponentesConexas();
                      } else {
                         G.ComponentesFuertementeConexas();
                      }
                     pressanykey();
                     clrscr();
                     break;

                 case 'x' :
                     clrscr();
                     l = 0;
                     G.ComponentesConexasDirigido();
                     pressanykey();
                     clrscr();
                     break;
                 
                 case 'n' :
                     clrscr();
                     if (G.Es_dirigido() == 0){
                        G.Sollin();
                     }
                     pressanykey();
                     clrscr();
                     break;

                 case 'w' :
                     clrscr();
                     if (G.Es_dirigido() == 1){
                        G.Floyd_Warshall();
                     }
                     pressanykey();
                     clrscr();
                     break;
 
          //Situar aqu� el resto de opciones del men�
             }
     }
     while (opcion != 'q');
     }
     cout << "Fin del programa" << endl;
     return(0);
 };
 
