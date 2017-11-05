#include <iostream>
#include <fstream>
#include <time.h>
#include "constant.hpp"
#include "network.hpp"
using namespace std;

///initialise the time interval and the external input current
void initialiser(step& a, step& b);

int main() {
	clock_t begin = clock();
	step simTime, t_stop, t_start;
	///file where the data would be collected
	ofstream timeSpike("../res/times_spike.txt");
	///ask the user to enter data for the time interval and the membrane potential
	initialiser(t_start, t_stop);
	simTime = t_start;
	Network networkNeuron;
	cout << "Network created " << '\n';
	double current_ext(0.0);
	double counter(0.0);
	///run simulation
	while (simTime <= t_stop) {
		///there is a counter to see the percentage of the simulation
		if (((simTime-t_start)/(double)(t_stop - t_start))-counter >= 0.0) {
			counter += 0.1;
			cout << "Simulation percentage done: "  << (simTime - t_start)/(double)(t_stop - t_start)*100 << " %" << '\n';
		}
		networkNeuron.update(N);
		simTime += N;
	}
	///store the spike times
	networkNeuron.storeTimeSpike(timeSpike);
	timeSpike.close();
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "Time of the simulation " << time_spent << endl;
	return 0;
}

void initialiser(step& a, step& b) {
	double s(0.0), t(0.0);
		cout << "Choose a time interval for the simulation: (a < b), a and b must be positive numbers ";
	do {
		do {
			cout << "Choose a : ";
			cin >> s;
			while (cin.fail()) {
				cerr << "The character you entered is not a number" << '\n';
				cout << "Please enter once more ";
				cin.clear();
				cin.ignore(256, '\n');
				cin >> s;
			}
			if (s < 0.0) {
				cerr << "Your number should be positive " << endl;
				cerr << "Please try it again " << endl;
			}
		} while (s < 0.0);
		
		cout << "Choose b : ";
		cin >> t;
		while (cin.fail()) {
			cerr << "The character you entered is not a number" << '\n';
			cout << "Please enter once more ";
			cin.clear();
			cin.ignore(256, '\n');
			cin >> t;
		}
		if (t < 0.0) {
			cerr << "Your number should be positive" << endl;
			cerr << "Please try it again" << endl;
		}
		if (t < s) {
			cerr << "The end of the interval should be bigger than the start" << endl;
			cerr << "Try it again" << endl;
		}	
		a=s/H;
		b=t/H;
		cout << "[a,b] = [" << s << ", " << t << "]" << endl;
	} while (t < 0.0 or (s > t));
}
