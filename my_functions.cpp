#include "pch.h"
#include <iostream>
#include <stdlib.h> /* abs */
#include "my_functions.h"

/*	Funzione di calcolo: ZERO di funzione
	con metodo della secante.
	Prende in input struct function,
	ricava espressione ed estremi di intervallo.
	Se necessario, converte i dati deg-rad.
	Esegue l'algoritmo in modo ricorsivo,
	calcola lo zero con errore non superiore a
	TOLERANCE / 2.
	Converte in rad-deg se necessario.
	Restituisce in output il risultato.	*/
float get_zero(function function)
{
	float x0, x1;
	float(*f)(float x);

	x0 = function.lower_bound;
	x1 = function.upper_bound;
	f = function.expression;

	if (function.type == trigonometric) {			// conversione deg-rad in entrata
		x0 = from_deg_to_rad(x0);					// per gli estremi di intervallo
		x1 = from_deg_to_rad(x1);
	}

	float delta_y = f(x1) - f(x0);
	float x2 = x1 - ((x1 - x0) / delta_y) * f(x1);	// formula di calcolo

	float distance = abs(delta_y);
	if (distance < TOLERANCE)						// condizione di uscita dell'algoritmo
	{
		if (function.type == trigonometric)			// conversione rad-deg in uscita
			x2 = from_rad_to_deg(x2);				// per il risultato

		return x2;
	}
	else {
		if (function.type == trigonometric) {		// conversione rad-deg in uscita											
			x1 = from_rad_to_deg(x1);				// per la ricorsività			
			x2 = from_rad_to_deg(x2);
		}

		function.lower_bound = x1;
		function.upper_bound = x2;
		return get_zero(function);					// richiamo ricorsivo
	}

}

/*	Funzione di calcolo: MINIMO di funzione
	con metodo della trisecante.
	Prende in input struct function,
	ricava espressione ed estremi di intervallo.
	Se necessario, converte i dati deg-rad.
	Esegue l'algoritmo in modo ricorsivo,
	calcola il minimo con errore non superiore a
	TOLERANCE / 2.
	Converte in rad-deg se necessario.
	Restituisce in output il risultato.	*/
float get_minimum(function function)
{
	float result;

	float x0 = function.lower_bound;
	float x1 = function.upper_bound;
	float(*f)(float x) = function.expression;

	if (function.type == trigonometric) {		// conversione deg-rad in entrata
		x0 = from_deg_to_rad(x0);
		x1 = from_deg_to_rad(x1);
	}

	float x2, x3, distance;

	distance = abs(x1 - x0);

	if (distance < TOLERANCE) {					// condizione di uscita
		result = x0 + (distance / 2);

		if (function.type == trigonometric)		// conversione rad-deg in uscita
			result = from_rad_to_deg(result);	// per il risultato

		return result;
	}
	else {
		x2 = x0 + 0.3 * distance;
		x3 = x0 + 0.7 * distance;

		float y3 = f(x3);
		float y2 = f(x2);

		if (y3 > y2) 							// valutazione scelta nuovo estremo
		{
			if (function.type == trigonometric)	// conversione rad-deg in uscita
				x3 = from_rad_to_deg(x3);		// per la ricorsività

			function.upper_bound = x3;
		}
		else
		{
			if (function.type == trigonometric)	// conversione rad-deg in uscita
				x2 = from_rad_to_deg(x2);		// per la ricorsività

			function.lower_bound = x2;
		}
		return get_minimum(function);			// richiamo ricorsivo	
	}
}

/*	Funzione di calcolo: DERIVATA di funzione IN UN PUNTO
	con metodo rapporto incrementale.
	Prende in input il punto in derivazione e la function.
	Se necessario, converte i dati deg-rad.
	Calcola la derivata con un incremento pari a
	EPSILON.
	Converte in rad-deg se necessario.
	Restituisce in output il risultato.	*/
float get_derivative_at_point(float x, function f) {
	float result;

	if (f.type == trigonometric)	// conversione deg-rad in entrata
		x = from_deg_to_rad(x);

	result = (f.expression(x + EPSILON) - f.expression(x)) / EPSILON;

	if (f.type == trigonometric)	// conversione rad-deg in uscita
		result = from_rad_to_deg(result);

	return result;
}

/*	Print_graphic stampa il grafico della funzione.
	Prende in input la funzione, ricava gli estremi e l'espressione della funzione.
	Converti gli estremi - solo in entrata - se necessario.

	Crea sette variabili di appoggio: 2 di tipo vettore, 5 di tipo float.
	In una prima variabile float 'step_x' salva il passo di ascissa costante. Sfruttando quest'ultima,
	in quelle di tipo vettore salva i valori discreti di ascissa - in uno - e di ordinata - nell'altro.
	Trova il valore massimo ed il valore minimo nel vettore delle ordinate.

	Si ricavano i valori scalati della posizione dell'asse delle ascisse e dei punti di ordinata,
	in maniera deterministica nel caso di funzioni costanti, attraverso un coefficiente di scalatura
	altrimenti.

	Si stampa l'asse delle ordinate, si stampano per righe i punti e l'asse delle ascisse.	*/
void print_graphic(function function) {

	// DICHIARAZIONE VARIABILI
	float x0 = function.lower_bound;			// estremo inferiore dell'intervallo
	float x1 = function.upper_bound;			// estremo superiore dell'intervallo
	float(*f)(float x) = function.expression;	// funzione

	float step_x; // intervallo dei punti x_i da considerare

	float vector_points_x[LENGTH_AXIS_X + 1];	// punti x_i
	float vector_f[LENGTH_AXIS_X + 1];			// punti f(x_i)

	float min_y, max_y;		// massimo f(x_i) e minimo f(x_j)

	float scaling;		// coefficiente di scalatura
	float zero_point;	// posizione dell'asse X

	// CODICE

	if (function.type == trigonometric) {	// conversione in radianti se necessario
		x0 = from_deg_to_rad(x0);
		x1 = from_deg_to_rad(x1);
	}

	step_x = (float)(abs(x0 - x1) / LENGTH_AXIS_X);	// passo x

	for (int i = 0; i <= LENGTH_AXIS_X; i++) {		// si popolano 
		vector_points_x[i] = x0 + (i * step_x);		// il vettore x_i
		vector_f[i] = f(vector_points_x[i]);		// il vettore f(x_i)
	}
	
	min_y = get_min_element(vector_f);	// calcola il minimo di f(x_i)
	max_y = get_max_element(vector_f);	// calcola il massimo di f(x_i)
	
	if (max_y == min_y) {		// caso in cui la funzione è costante
			zero_point = LENGTH_AXIS_Y / 2;
		if (max_y != 0) {
			for (int i = 0; i <= LENGTH_AXIS_X; i++) {
				if (max_y < 0)
					vector_f[i] = LENGTH_AXIS_Y / 4;
				else
					vector_f[i] = LENGTH_AXIS_Y / 4 + zero_point;
			}	
		}
	}
	else {						// altrimenti 
		scaling = LENGTH_AXIS_Y / (max_y - min_y);
		zero_point = abs(min_y) * scaling;

		for (int i = 0; i <= LENGTH_AXIS_X; i++)
			vector_f[i] = vector_f[i] * scaling + zero_point;
	}
		
	cout << "-------------------------------------------------------------------------------- > Y" << endl;

	for (int i = 0; i <= LENGTH_AXIS_X; i++) {
		if (vector_f[i] < zero_point) {
			for (int j = 1; j < vector_f[i]; j++) {
				cout << " ";
			}
			cout << "*";
			for (int k = vector_f[i] + 1; k < zero_point; k++) {
				cout << " ";
			}
			cout << "|" << endl;
		}
		else if (zero_point < vector_f[i]) {
			for (int k = 0; k < zero_point; k++)
				cout << " ";
			cout << "|";
			for (int j = zero_point + 1; j < vector_f[i]; j++)
				cout << " ";
			cout << "*" << endl;
		}
		else
		{
			for (int j = 0; j < vector_f[i]; j++)
				cout << " ";
			cout << "*" << endl;
		}
	}
	for (int i = 0; i < zero_point; i++)
		cout << " ";
	cout << "V  X" << endl;
}


/*	Massimo elemento di un vettore.
	Prende in input un vettore, inizializza massimo 
	col primo elemento del vettore. Confronta ogni volta
	massimo con tutti gli elementi successivi al primo.
	Se trova un elemento più grande del massimo, allora
	sostituisce quello a questo, fino a che non vengono
	scorsi tutti gli elementi del vettore. Alla fine
	ritorna il massimo.	*/
float get_max_element(float v[]) {
	float max = v[0];
	for (int i = 1; i <= LENGTH_AXIS_X; i++) {
		if (max < v[i])
			max = v[i];
	}
	return max;
}

/*	Minimo elemento di un vettore.
	Prende in input un vettore, inizializza minimo
	col primo elemento del vettore. Confronta ogni volta
	minimo con tutti gli elementi successivi al primo.
	Se trova un elemento più piccolo del minimo, allora
	sostituisce quello a questo, fino a che non vengono
	scorsi tutti gli elementi del vettore. Alla fine
	ritorna il minimo.	*/
float get_min_element(float v[]) {
	float min = v[0];
	for (int i = 1; i <= LENGTH_AXIS_X; i++) {
		if (v[i] < min)
			min = v[i];
	}
	return min;
}


/*	Funzione di conversione: DA DEG A RAD
	Converte un valore da gradi sessagesimali
	a gradi radianti.	*/
float from_deg_to_rad(float x) {
	return x * PI / 180;
}

/*	Funzione di conversione: DA RAD A DEG
	Converte un valore da gradi radianti
	a gradi sessagesimali.	*/
float from_rad_to_deg(float x) {
	return x * 180 / PI;
}

