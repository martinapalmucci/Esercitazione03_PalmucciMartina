#pragma once

// costanti
constexpr auto PI = 3.14159265358979323846;		// pi greco
constexpr auto TOLERANCE = 0.01;				// tolleranza di calcolo
constexpr auto EPSILON = 0.000001;				// epsilon
constexpr auto LENGTH_AXIS_X = 20; // lunghezza discreta dell'asse X;
constexpr auto LENGTH_AXIS_Y = 80; // lunghezza discreta dell'asse Y;

using namespace std; // namespace block

enum type { polynomial, trigonometric }; // tipo di classificazione per le funzioni matematiche

// struttura per le funzioni matematiche
struct function
{
	float(*expression)(float);	// espressione della funzione
	type type;					// tipo di classificazione

	// intervallo di definizione:
	float lower_bound;			// estremo inferiore 
	float upper_bound;			// estremo superiore

	char name[30];				// nome della funzione
};

float get_zero(function);						// calcola lo zero di funzione
float get_minimum(function);					// calcola il minimo di funzione
float get_derivative_at_point(float, function); // calcola la derivata prima di funzione in un punto

void print_graphic(function); // stampa il grafico di funzione

float get_min_element(float[]); // restituisce il minimo elemento di un vettore
float get_max_element(float[]); // restituisce il massimo elemento di un vettore

float from_deg_to_rad(float); // converte da gradi a radianti
float from_rad_to_deg(float); // converte da radianti a gradi

