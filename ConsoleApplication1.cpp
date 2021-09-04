#include <iostream>
#include <vector>
using namespace std;

int main()
{
	float N_aux = 0.0;
	int N = 0;
	float Xi[10], Yi[10];
	float r = 0.0, AvgX = 0.0, AvgY = 0.0, Numerador = 0.0, AuxX = 0.0, AuxY = 0.0;
	float Zero = 0.0;
	char* msg = new char[255];

	cout << "Cual es el numero de datos que conforman el conjunto de datos (x, y) a ser analizados: ";
	cin >> N;
	N_aux = (float)N;

	for (int i = 0; i < N; i++) {
		float x, y;
		cout << "Cual es el valor de la variable x para el punto: ";
		cin >> x;
		cout << "Cual es el valor de la variable y para el punto: ";
		cin >> y;
		Xi[i] = x;
		Yi[i] = y;
	}

	_asm {

		FINIT; Inicializa el coprocesador

		MOV ESI, 00h; Inicializar el registro indice en cero(desplazamiento)
		MOV ECX, N; Preparar ecx para contar un ciclo de N iteraciones
		more : ; Etiqueta para marcar un sitio de retorno de un ciclo

			FLD AvgX; Inserta en la pila lo almacenado en AvgX, la sumatoria de los valores X
			FADD Xi[ESI]; Acumula en la pila el contenido del arreglo Xi, indice esi
			FSTP AvgX; Guarda en AvgX el contenido de la pila

			FLD AvgY; Inserta en la pila lo almacenado en AvgY, la sumatoria de los valores Y
			FADD Yi[ESI]; Acumula en la pila el contenido del arreglo Yi, indice esi
			FSTP AvgY; Guarda en AvgY el contenido de la pila

			ADD	ESI, 04h; Incrementa el indice en 4 bytes(palabra doble)
		LOOP more; Se repite el cico si ecx no es cero


		FLD AvgX
		FDIV N_aux
		FSTP AvgX; Se almacena en la variable AvgX el promedio de las Xi

		FLD AvgY
		FDIV N_aux
		FSTP AvgY; Se almacena en la variable AvgY el promedio de las Yi


		MOV ESI, 0
		MOV ECX, N
		FINIT
		num :
			FLD Yi[ESI]					; Numerador = (Yi[ESI] - AvgY) * (Xi[ESI] - AvgX) + Numerador
			FSUB AvgY
			FLD Xi[ESI]
			FSUB AvgX
			FMUL
			FLD Numerador
			FADD
			FSTP Numerador
			ADD	ESI, 04h
		LOOP num

		MOV ESI, 0
		MOV ECX, N
		FINIT
		den :
			FLD Xi[ESI]; AuxX = (Xi[ESI] - AvgX) ^ 2 + AuxX
			FSUB AvgX
			FLD Xi[ESI]
			FSUB AvgX
			FMUL
			FLD AuxX
			FADD
			FSTP AuxX
			FLD Yi[ESI]; AuxY = (Yi[ESI] - AvgY) ^ 2 + AuxY
			FSUB AvgY
			FLD Yi[ESI]
			FSUB AvgY
			FMUL
			FLD AuxY
			FADD
			FSTP AuxY
			ADD	ESI, 04h
		LOOP den

		FLD AuxX
		FMUL AuxY
		FSQRT

		FLD Numerador
		FDIV ST(0), ST(1)
		FSTP r

		FLD r
		FLD Zero
		FCOMIP ST(0), ST(1); Si la distancia entre centros es 0 y los radios son diferentes, entonces la relacion de clasificacion es : concentricas.
			JA negativa

		FLD Zero
		FLD r
		FCOMIP ST(0), ST(1); Si la distancia entre centros es 0 y los radios son diferentes, entonces la relacion de clasificacion es : concentricas.
			JA positiva


		MOV EAX, msg;					Metodo para ingresar la cadena respectiva de texto BYTE por BYTE
		MOV[EAX], 'E'
		INC EAX
		MOV[EAX], 'l'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'c'
		INC EAX
		MOV[EAX], 'o'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 'f'
		INC EAX
		MOV[EAX], 'i'
		INC EAX
		MOV[EAX], 'c'
		INC EAX
		MOV[EAX], 'i'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 'n'
		INC EAX
		MOV[EAX], 't'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'd'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'c'
		INC EAX
		MOV[EAX], 'o'
		INC EAX
		MOV[EAX], 'r'
		INC EAX
		MOV[EAX], 'r'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 'l'
		INC EAX
		MOV[EAX], 'a'
		INC EAX
		MOV[EAX], 'c'
		INC EAX
		MOV[EAX], 'i'
		INC EAX
		MOV[EAX], 'o'
		INC EAX
		MOV[EAX], 'n'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 's'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'c'
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 'r'
		INC EAX
		MOV[EAX], 'o'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'y'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 's'
		INC EAX
		MOV[EAX], 'u'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'v'
		INC EAX
		MOV[EAX], 'a'
		INC EAX
		MOV[EAX], 'l'
		INC EAX
		MOV[EAX], 'o'
		INC EAX
		MOV[EAX], 'r'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 'e'
		INC EAX
		MOV[EAX], 's'
		INC EAX
		MOV[EAX], ':'
		INC EAX
		MOV[EAX], ' '
		INC EAX
		MOV[EAX], 0
		JMP endmsg

		negativa :
			MOV EAX, msg;					Metodo para ingresar la cadena respectiva de texto BYTE por BYTE
			MOV[EAX], 'E'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'f'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'n'
			INC EAX
			MOV[EAX], 't'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'd'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], 'a'
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'n'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'n'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'g'
			INC EAX
			MOV[EAX], 'a'
			INC EAX
			MOV[EAX], 't'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'v'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'y'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], 'u'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'v'
			INC EAX
			MOV[EAX], 'a'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], ':'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 0
			JMP endmsg

		positiva :
			MOV EAX, msg;					Metodo para ingresar la cadena respectiva de texto BYTE por BYTE
			MOV[EAX], 'E'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'f'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'n'
			INC EAX
			MOV[EAX], 't'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'd'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], 'a'
			INC EAX
			MOV[EAX], 'c'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'n'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'p'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 't'
			INC EAX
			MOV[EAX], 'i'
			INC EAX
			MOV[EAX], 'v'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'y'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], 'u'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'v'
			INC EAX
			MOV[EAX], 'a'
			INC EAX
			MOV[EAX], 'l'
			INC EAX
			MOV[EAX], 'o'
			INC EAX
			MOV[EAX], 'r'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 'e'
			INC EAX
			MOV[EAX], 's'
			INC EAX
			MOV[EAX], ':'
			INC EAX
			MOV[EAX], ' '
			INC EAX
			MOV[EAX], 0




		endmsg :

	}
	cout << "\n" << msg << r;
	
	return 0;

}

// Ejecutar programa: Ctrl + F5 o men� Depurar > Iniciar sin depurar
// Depurar programa: F5 o men� Depurar > Iniciar depuraci�n

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de c�digo fuente
//   3. Use la ventana de salida para ver la salida de compilaci�n y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de c�digo, o a Proyecto > Agregar elemento existente para agregar archivos de c�digo existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
