#ifndef NEURON_HPP
#define NEURON_HPP
#include <fstream>
#include <cmath>
#include <vector>

class Neuron {
	private :
		//membrane potential
		double membrane_potential_;
		
		//times when spikes occure
		std::vector<double> times_;
		
		double clock_;
		
		bool isRefractory(const double& t) const;
	
	public:		
		Neuron();
		~Neuron();
		
		//getters
		double getMembranePotential() const;	
		int getTimeSize() const;
		double getTimeSpike(const int& i) const;
		std::vector<double> getTimeSpikeTab() const;
		
		bool update(const double& t, const double& input_current);
		void addSpikeTime(const double& t);
		
		//methods to store data in a file
		void spikeTimeEnter(std::ofstream& file) const;	
		void potentialEnter(std::ofstream& file) const;	
};

#endif
