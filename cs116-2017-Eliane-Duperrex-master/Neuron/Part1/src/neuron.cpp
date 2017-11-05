#include "neuron.hpp"
 #include <iostream>
#include "constant.hpp"

Neuron::Neuron() : membrane_potential_(0.0), clock_(0.0) {}

Neuron::~Neuron() {}

//update the membrane potential of the neuron depending on if it is refractory
bool Neuron::update(const double& t, const double& input_current) {
	bool spike(false);
	const double T_STOP = clock_ + t;
	while (clock_ < T_STOP) {
		if (membrane_potential_ > V_threshold) {
			addSpikeTime(t);
			spike = true;	
			membrane_potential_ = 0.0; 
		}
		
		if (!isRefractory(t)) {
			membrane_potential_ = exp(-H/TAU)*membrane_potential_ + input_current*R*(1-exp(-H/TAU));
		} else {
			membrane_potential_ = 0.0;
		}
		clock_ += t;
	}
	
	return spike;
}

//return if the neuron is refractory
bool Neuron::isRefractory(const double& t) const {
		
	//for the first loop, the vector is empty 
	if (times_.size() != 0) {		
		return (times_.back() > 0.0 and (t-times_.back()) < TAU_REFRACTORY);	
	} else {		
	//when there hasn't been any spike, the neuron cannot be refractory
		return false;
	}
}
//different getters
int Neuron::getTimeSize() const {
	return times_.size();
}

double Neuron::getTimeSpike(const int& i) const {
	return times_[i];
}

double Neuron::getMembranePotential() const {
	return membrane_potential_;
}
std::vector<double> Neuron::getTimeSpikeTab() const {
	return times_;
}

//add a new spike
void Neuron::addSpikeTime(const double& t) {
	times_.push_back(t);
}

//store the times when spikes occured in a file
void Neuron::spikeTimeEnter(std::ofstream& file) const {
	
	if (file.fail()) {
		std::cerr << "Error ";
	} else {
		file << "Spike time : " << std::endl;
		for (int i(0); i < times_.size(); ++i) {
			file << times_[i] << std::endl;
		}
	}		
}

//store the potential in a file
void Neuron::potentialEnter(std::ofstream& file) const {
	if (file.fail()) {
			std::cerr << "Error ";
		} else {
			file << membrane_potential_ << std::endl;
		}	
}
