// Esercitazione03_PalmucciMartina.cpp

// Nome e Cognome: Martina Palmucci
// Numero di matricola: 097506
// Classe: L-35 Matematica e Applicazioni

// ESERCITAZIONE N°3
// IL MANUALE DELLE FUNZIONI

/*
Questo programma prende in input
delle funzioni matematiche
considerate su limitati intervalli,
ne restituisce zero, minimo, derivata,
stampa il grafico.
*/

#include "pch.h"
#include <iostream>
#include <cstdlib> /* system("pause") */
#include "matemathical_functions.h" // header delle funzioni matematiche
#include "my_functions.h"			// header delle funzioni ausiliare 
// al calcolo dei vari output del programma

// DICHIARAZIONI ED INIZIALIZZAZIONI

/* costanti */

constexpr auto ASCII_1 = 49;	// valore '1' in codice ASCII
const int N = 7;				// # totale funzioni di esempio

/* strutture */

// inizializzate le varie funzioni di esempio
function function_1 = { f1, polynomial, 0.f, 1.f,"y = 3x^2 - 5x + 1" };			// parabola
function function_2 = { f2, trigonometric, 0.f, 95.f, "y = 1 / 2 + cos(2x)" };	// cosinusoide
function function_3 = { f3, polynomial, 0.f, 1.f, "y = 2 + e^(25x)" };			// esponenziale
function function_4 = { f4, polynomial, 0.f, 1.f, "y = x" };					// bisettrice
function function_5 = { f5, polynomial, 0.f, 2.f, "y = 2x^2 - 3x + 0.5" };		// parabola con due radici
function function_6 = { f6, polynomial, 0.f, 3.f, "y = 3" };					// costante
function function_7 = { f7, trigonometric, 0.f, 360.f, "y = sin(x)" };			// sinusoide

/* array delle funzioni */

function array_function[N] = { function_1, function_2, function_3, function_4, function_5, function_6, function_7 };

/* funzioni ausiliarie di datasheet ed interfaccia utente */

void datasheet(function);			// stampa scheda tecnica
float insert_point(float, float);	// richiesta all'utente di un punto appartenente ad un intervallo

int main()
{
	cout << "Benvenuti nel manuale delle funzioni matematiche!\n" << endl;

	char choice; // salva la scelta dell'utente
	do {
		// menu di scelta della funzione
		// eseguito con un ciclo for
		// aggiunta in fondo condizione di uscita
		cout << "MENU'\n"
			<< "Seleziona la funzione che piu' ti piace:\n" << endl;
		for (int i = 1; i <= N; i++)
			cout << i << " - " << array_function[i - 1].name << endl;
		cout << "0 - Esci dal menu'\n" << endl
			<< "La tua scelta e' "; cin >> choice;
		cout << endl;

		/*	se viene scelta una funzione
			si stampa la scheda tecnica,
			se si scegli di uscire
			il programma saluta e termina,
			altrimenti messaggio di errore */
		if ( (choice >= '1') & (choice <= char(ASCII_1 + N - 1)) )
		{
			// conversione della scelta utente in indice per l'array delle funzioni
			int index = int(choice) - ASCII_1; 
			// funzione selezionata
			function selectedFunction = array_function[index];
			
			// scheda tecnica
			datasheet(selectedFunction);
			
			// pausa
			system("pause");
			cout << endl;
		}
		else if (choice == '0') {
			cout << "Arrivederci!\n" << endl;
		}
		else {
			cout << "Inserimento errato. Riprova.\n" << endl;
		}
	} while (choice != '0');


	return 0;
}

/*	Stampa la scheda tecnica.
	Prende in input una struttura
	funzione. Organizza e stampa i
	risultati delle funzioni di calcolo. */
void datasheet(function function)
{
	cout << "SCHEDA TECNICA DELLA FUNZIONE " << function.name << endl;
	if (function.type == trigonometric)
		cout << "nota: tutti i valori sono espressi in gradi sessagesimali" << endl
		<< endl;

	cout << " *** intervallo predefinito [ " << function.lower_bound << ", " << function.upper_bound << " ] ***\n"
		<< endl
		<< "La funzione presenta" << endl
		<< " - uno zero in x = " << get_zero(function) << endl
		<< " - un minimo in x = " << get_minimum(function) << endl
		<< endl

		<< "Derivata:\n";

	float x, lower, upper;

	lower = function.lower_bound;
	upper = function.upper_bound;

	x = insert_point(lower, upper);

	cout << "La derivata calcolata in x = " << x
		<< " vale " << get_derivative_at_point(x, function) << endl
		<< endl

		<< "Il grafico si presenta nel seguente modo:\n" << endl
		<< endl;

	print_graphic(function);

	cout << endl << endl
		<< "Annotazioni:\n"
		<< "Lo zero e il minimo della funzione sono stati calcolati con una tolleranza di " << TOLERANCE << ".\n"
		<< "La derivata e' stata calcolata su un incremento di " << EPSILON << ".\n" << endl;
}

/*	Inserimento di un punto: prende in input 
	l'estremo inferiore e l'estremo superiore 
	di un intervallo, restituisce in output
	l'interimento dell'utente: un punto dell'intervallo	*/
float insert_point(float lower, float upper) {
	float point; // salva la selezione utente
	do {
		cout << "In quale punto dell'intervallo aperto vuoi calcolare la derivata? ";
		cin >> point;

		// se l'inserimento non appartiene all'intervallo
		// si stampa un messaggio di errore
		if ((point <= lower) | (point >= upper))
			cout << "Valore non valido. Riprova.\n" << endl;

	} while ((point <= lower) | (point >= upper));

	return point;
}


// fine
