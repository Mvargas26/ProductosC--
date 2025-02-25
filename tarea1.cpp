#include <iostream>
#include <string>
#include <windows.h> // nos deja usar Sleep
#include <conio.h> //nos eja usar el _getch que escucha sin oprimir el enter

using namespace std;

//*************************************************************************************************************************** */
//******************************    Metodos Internos                                 **************************************** */
//*************************************************************************************************************************** */

//Valida los datos de ingreso entre 5 y 10
bool validarCantidadProductos(int cantidadProductos,int QuantumDelSO, int productoMalo) {
     if (cantidadProductos < 5 || cantidadProductos > 10 ) {
        return false;
    }
     if (QuantumDelSO < 5 || QuantumDelSO > 10 ) {
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
        "Tomate", "Papa", "Sandia", "Melon", "Papaya",
        "Zanahoria", "Pepino", "Lechuga", "Cebolla", "Chile dulce"
    };

        
    // vector dinámico con el tamaño del parametro; El asterisco es un puntero a la 1 casilla del string
    string* productosSeleccionados = new string[cantidadProductos];
    
    for (int i = 0; i < cantidadProductos; i++) {
        productosSeleccionados[i] = productosDisponibles[i];
    }
    
    return productosSeleccionados;
}//fin vectorProductos

//Metodo que crea vector dinamico con los Quamtum dependiendo de la cant de productos
int* vectorQuamtum(int cantidadProductos) {
    int QuantumProductos[10] = {5,12,4,8,2,5,12,4,8,2};
    
    // vector dinámico con el tamaño del parametro; El asterisco es un puntero a la 1 casilla del string
    int* QuamtumSeleccionados = new int[cantidadProductos];
    
    for (int i = 0; i < cantidadProductos; i++) {
        QuamtumSeleccionados[i] = QuantumProductos[i];
    }
    
    return QuamtumSeleccionados;
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
}//fin interrupcionesDelUsuario

bool esNumero(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}//fin esNumero


//*************************************************************************************************************************** */
//******************************   Variables Globales                             **************************************** */
//*************************************************************************************************************************** */
int cantidadProductos=0;
string cantidadEnSitrng;
int productoMalo =0;
string porductMaloString;
string* productos;
int QuantumDelSO =0;
string QuantumString;
int* QuantumProductos;
string puntosDeControl[10] = {
    "Libre de impurezas",
    "Organicos",
    "Vencimiento",
    "Desinfeccion",
    "Control Fitosanitarias",
    "Control de Plagas",
    "Certificacion Ambiental",
    "Valor nutricional",
    "Empaque",
    "Certificacion"
};


//*************************************************************************************************************************** */
//******************************    Metodo main                                **************************************** */
//*************************************************************************************************************************** */
int main(int argc, char const *argv[])
{
    //Pedimos los 2 datos y validamos que no sea letra y cumpla entre 5 y 10
   do {
        cout << "Ingrese la cantidad de productos en numero: ";
        cin >> cantidadEnSitrng;

        cout << "Ingrese el numero del producto en mal estado: ";
        cin >> porductMaloString;

        cout << "Ingrese el Quantum del SO: ";
        cin >> QuantumString;

        //Validamos que no venga una letra
        if (!esNumero(cantidadEnSitrng) || !esNumero(porductMaloString) || !esNumero(QuantumString)) {
        cout << "Error: Ingrese solo numeros enteros.\n";
        continue;
        }else{
            cantidadProductos =stoi(cantidadEnSitrng);
            productoMalo = stoi(porductMaloString);
            QuantumDelSO = stoi(QuantumString);
        };

    } while (!validarCantidadProductos(cantidadProductos,QuantumDelSO, productoMalo));

    //Pedimos la tecla para continuar
    cout << "Los datos son validos.. ";
    esperarTecla();

    //llenamos los vectores dinamicos
    productos = vectorProductos(cantidadProductos);
    QuantumProductos = vectorQuamtum(cantidadProductos);

    //Recorre el vector de Productos
    int i = 0;
    while (i < cantidadProductos) {
        cout << "**Analizando Producto " << (i + 1) << ": " << productos[i] << " ** \n" ;
        cout << "Quantum del SO: " << QuantumDelSO <<"\n";
        cout << "Quantum del Producto: " << QuantumProductos[i] <<"\n";
    //Validamos que no sea el producto malo
          if (i+1 == productoMalo) {
            interrupcionDeLa_P('P',i+1,productos[i]);
            i++;
            continue; // Pasa al siguiente producto
        }
        
        //Recorre el ciclo de punto de control
        bool debeSalir = false;
        int j = 1;
        while (j <= 10) {
            cout <<"\rChequeo No. "<< j <<" "<< puntosDeControl[j]<<"           "<<flush ;
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

  //libera la memoria del arreglo dinamico  
  delete[] productos; 
  delete [] QuantumProductos;
   return 0;
}//fin del metod main


