#include <iostream>
#include <vector>
#include <fstream>

#include "neuron.hpp"
#include "constant.hpp"

using namespace std;


void initialiser(double& a, double& b, double& current);

int main() {
	Neuron neuron;
	double  simTime(T_SART);
	double input_current_ext(0.0);
	double a, b;
	
	//file where the data would be collected
	ofstream entree_donne("times_spike");

	//ask the user to enter data for the time interval and the membrane potential
	initialiser(a, b, input_current_ext);
	entree_donne << "Membrane potential: " << endl;
	
	double input_current(0.0);
	//run simulation
	while (simTime < T_STOP) {
		
		if (simTime >= a and simTime < b) {
			input_current = input_current_ext;
		 } else { 
		 	input_current = 0.0;
		 }
		//to store the membrane potential
		neuron.potentialEnter(entree_donne);
		if (neuron.update(simTime, input_current)) {
			cout << "Spike occurs at " << simTime << " ms" << endl;
		}
		
		simTime = simTime + N*H;

	}
	//to store the spike times
	neuron.spikeTimeEnter(entree_donne);
	entree_donne.close();
	return 0;
}

void initialiser(double& a, double& b, double& input_current_ext) {
	cout << "Choose an external current: ";
	cin >> input_current_ext;
	do {	
		cout << "Choose a time interval: (a < b), a and b must be positive numbers ";
		cin >> a;
		cin >> b;
	} while (a >= b or a < 0.0 or b < 0.0) ;
	
	cout << "[a,b] = [" << a << ", " << b << "]" << endl;
}
