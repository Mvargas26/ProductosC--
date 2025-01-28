#include <iostream>
#include <string>
#include <windows.h> // nos deja usar Sleep
#include <conio.h> //nos eja usar el _getch que ewscucha sin oprimir el enter

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

//Espera que se oprima una tecla y realiza una accion
void esperarTecla() {
    char tecla;
    while (true) {
        cout << "Presiona 'S' para continuar o 'N' para finalizar: ";
        cin.ignore(); //Limpia el buffer por los saltos de linea
        tecla = cin.get(); //obtiene el char de la letra que apretamos

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
        cout << "Presione la tecla A para continuar...";
        cin.ignore(); //Limpia el buffer por los saltos de linea
        tecla = cin.get(); //obtiene el char de la letra que apretamos

        if (tecla == 'A' || tecla == 'a') {
            break; // Continúa la ejecución 
        } else {
            cout << "Tecla invalida, intenta nuevamente." << endl;
        }
    }
}//fin esperarTecla_A

//Espera que se oprima P y realiza una accion
void interrupcionDeLa_P(char tecla,int numProducto,string nombreProducto){

        if (tecla == 'P' || tecla == 'p') {
          cout << "Interrupcion aplicada, para el producto No. " << numProducto << " - " << nombreProducto << endl;
          esperarTecla_A();
        }
}//fin interrupcionP

// Maneja las interrupciones del usuario
void interrupcionesDelUsuario(bool &debeSalir, int numProducto, string nombreProducto) {
    if (_kbhit()) {
        char tecla = _getch(); // Captura la tecla sin esperar el enter
        switch (toupper(tecla)) { // convertimos el char en mayúscula
            case 'C':
                cout << "\nInterrupcion aplicada por el usuario en el producto No. "
                     << numProducto << " - " << nombreProducto << endl;
                debeSalir = true;
                break;
            case 'F':
                cout << "\nInterrupción aplicada para finalizar el programa en el producto No. "
                     << numProducto << " - " << nombreProducto << endl;
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
        cout << "Ingrese la cantidad de productos: ";
        cin >> cantidadProductos;

        cout << "Ingrese el producto malo: ";
        cin >> productoMalo;
    } while (!validarCantidadProductos(cantidadProductos, productoMalo));

    //Pedimos la tecla para continuar
    cout << "Los datos son validos." << endl;
    esperarTecla();

    //llenamos el vector dinamico
    productos = vectorProductos(cantidadProductos);

    //Recorre el vector de Productos
    int i = 0;
    while (i < cantidadProductos) {
        cout << "*** Analizando Producto " << (i + 1) << ": " << productos[i] << " ***" << endl;
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
            cout << "\rPunto de Control: " << j << flush;
            Sleep(500);
            interrupcionesDelUsuario(debeSalir,i + 1, productos[i]);


            //si debeSalir ahora es true, sale de los puntos de control
            if(debeSalir){
                cout << "\nSaltando al siguiente producto...";
                esperarTecla_A();
                break;
            }
            j++;
        }
        // Si debeSalir es true, tambien pasamos al siguiente producto sin esperar
        if (debeSalir) {
            i++;
            continue; // Pasa al siguiente producto
        }else{
           cout << endl; 
        }
        
        cout << endl;
        i++;
    }
    cout << "Fin, Proceso Completado con exito!!!" << endl;
    

  delete[] productos; //libera la memoria del arreglo dinamico
   return 0;
}//fin del metod main


