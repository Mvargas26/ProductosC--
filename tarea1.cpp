#include <iostream>
#include <string>
#include <windows.h> // nos deja usar Sleep
#include <conio.h> //nos eja usar el _getch que escucha sin oprimir el enter

using namespace std;

//*************************************************************************************************************************** */
//******************************    Metodos Internos                                 **************************************** */
//*************************************************************************************************************************** */

//Valida los datos de ingreso entre 5 y 10
bool validarCantidadProductos(int cantidadProductos, int productoMalo) {
     if (cantidadProductos < 5 || cantidadProductos > 10 ) {
        return false;
    }
    if (productoMalo != 0 && productoMalo > cantidadProductos) {
        return false;
    }
    return true;
}//fin validarCantidadProductos

//Metodo que crea vector dinamico dependiendo de la cant de productos
string* vectorProductos(int cantidadProductos) {
    string productosDisponibles[10] = {
        "Arroz", "Frijoles", "Galletas", "Aceite", "Azucar", 
        "Sal", "Harina", "Leche", "Pasta", "Cloro"
    };
    
    // vector dinámico con el tamaño del parametro; El asterisco es un puntero a la 1 casilla del string
    string* productosSeleccionados = new string[cantidadProductos];
    
    for (int i = 0; i < cantidadProductos; i++) {
        productosSeleccionados[i] = productosDisponibles[i];
    }
    
    return productosSeleccionados;
}//fin vectorProductos

//Espera S o N para saber si sigue
void esperarTecla() {
    char tecla;
    while (true) {
        cout << "Presiona 'S' para continuar o 'N' para finalizar: "<< endl;
        //cin.ignore(); //Limpia el buffer por los saltos de linea
        tecla = _getch(); //obtiene el char de la letra que apretamos

        if (tecla == 'S' || tecla == 's') {
            break; // Continúa la ejecución si se presiona 'P' o 'p'
        } else if (tecla == 'N' || tecla == 'n') {
            cout << "Ejecucion finalizada." << endl;
            exit(0); // Finaliza el programa si se presiona 'F' o 'f'
        } else {
            cout << "Tecla invalida, intenta nuevamente." << endl;
        }
    }
}//fin esperarTecla

//Espera que se oprima A y realiza una accion
void esperarTecla_A() {
    char tecla;
    while (true) {
        cout << " Presione A para seguir..";
        //cin.ignore(); //Limpia el buffer por los saltos de linea
        tecla = _getch(); //obtiene el char de la letra que apretamos

        if (tecla == 'A' || tecla == 'a') {
            break; // Continúa la ejecución 
        } else {
            cout << "Tecla invalida.";
        }
    }
}//fin esperarTecla_A

//Espera que se oprima A y realiza una accion
void esperarTecla_Enter() {
     cout <<" -Tecla para seguir..";
        _getch();
  
}//fin esperarTecla_Enter

//Espera que se oprima P y realiza una interrupcion simulada
void interrupcionDeLa_P(char tecla,int numProducto,string nombreProducto){

        if (tecla == 'P' || tecla == 'p') {
          cout << "Interrupcion aplicada, para el producto No. " << numProducto << " - " << nombreProducto << " ";
          esperarTecla_A();
          cout<< endl;
        }
}//fin interrupcionP

// Maneja las interrupciones del usuario
void interrupcionesDelUsuario(bool &debeSalir, int numProducto, string nombreProducto) {
    if (_kbhit()) {
        char tecla = _getch(); // Captura la tecla sin esperar el enter
        switch (toupper(tecla)) { // convertimos el char en mayúscula
            case 'C':
                cout << " *Interrupcion aplicada por el usuario en el producto No. "
                     << numProducto << " - " << nombreProducto << " ";
                debeSalir = true;
                break;
            case 'F':
                cout << " *Interrupcion aplicada para finalizar el programa en el producto No. "
                     << numProducto << " - " << nombreProducto << " ";
                exit(0); // Termina completamente el programa
            default:
                // No hacer nada para otras teclas
                break;
        }
    }
}
//*************************************************************************************************************************** */
//******************************   Variables Globales                             **************************************** */
//*************************************************************************************************************************** */
int cantidadProductos=0;
int productoMalo =0;
string* productos;

//*************************************************************************************************************************** */
//******************************    Metodo main                                **************************************** */
//*************************************************************************************************************************** */
int main(int argc, char const *argv[])
{
    //Pedimos los 2 datos y validamos cumpla entre 5 y 10
   do {
        cout << "Ingrese la cantidad de productos en numero: ";
        cin >> cantidadProductos;

        cout << "Ingrese el numero del producto en mal estado: ";
        cin >> productoMalo;
    } while (!validarCantidadProductos(cantidadProductos, productoMalo));

    //Pedimos la tecla para continuar
    cout << "Los datos son validos.. ";
    esperarTecla();

    //llenamos el vector dinamico
    productos = vectorProductos(cantidadProductos);

    //Recorre el vector de Productos
    int i = 0;
    while (i < cantidadProductos) {
        cout << "**Analizando Producto " << (i + 1) << ": " << productos[i] << " **";
    //Validamos que no sea el producto malo
          if (i+1 == productoMalo) {
            interrupcionDeLa_P('P',i+1,productos[i]);
            i++;
            continue; // Pasa al siguiente producto
        }
        
        //Recorre el ciclo de . de control
        bool debeSalir = false;
        int j = 1;
        while (j <= 10) {
            cout << " Conteo:" << j ;
            Sleep(400);
            interrupcionesDelUsuario(debeSalir,i + 1, productos[i]);

            //si debeSalir ahora es true, sale de los puntos de control
            if(debeSalir){
                cout << " Saltando al siguiente producto. ";
                esperarTecla_A();
                break;
            }
            j++;
        }
        // Si debeSalir es true, tambien pasamos al siguiente producto sin esperar
        if (debeSalir) {
            i++;
            continue; // Pasa al siguiente producto
        }

        esperarTecla_Enter();

        cout << "\r" << string(175, ' ') << flush;       
        cout <<"\r"<< flush;
        i++;
    }
    cout << "Fin, Proceso Completado con exito!!!" << endl;
    
  delete[] productos; //libera la memoria del arreglo dinamico
   return 0;
}//fin del metod main


