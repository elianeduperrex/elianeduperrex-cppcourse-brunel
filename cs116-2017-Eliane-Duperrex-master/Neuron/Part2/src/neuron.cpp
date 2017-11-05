#include "neuron.hpp"
#include <cassert>
#include <iostream>
Neuron::Neuron() : 	membrane_potential_(0.0), clock_(0), 
					isRefract_(false), input_current_(0.0), isExcitatory_(true) {
	for (auto& ind : timeDelayBuffer_) {
		ind = 0.0;
		}
}
Neuron::Neuron(const bool& isExcitatory) : 	membrane_potential_(0.0), clock_(0), 
					isRefract_(false), input_current_(0.0), isExcitatory_(isExcitatory) {
	for (auto& ind : timeDelayBuffer_) {
		ind = 0.0;
		}
}

Neuron::~Neuron() {}

//update the membrane potential of the neuron depending on if it is refractory
bool Neuron::update(const step& t, const int& poisson) {
	bool hasSpike(false);
	const step T_STOP_ = clock_ + t;
	
	while (clock_ < T_STOP_) {
		
		if (membrane_potential_ >= V_THRESHOLD) {
			addSpikeTime(clock_);
			hasSpike = true;	
		}
		isRefractory(clock_); 
		
		if (!isRefract_) {
			size_t size(timeDelayBuffer_.size());
			membrane_potential_ =	C1*membrane_potential_ + input_current_*C2 
									+ timeDelayBuffer_[clock_%size] + poisson*J_EXT;
			timeDelayBuffer_[clock_%size] = 0.0;
		
		} else {
			membrane_potential_ = V_RESET;
		}
		clock_ ++;
	}	
	return hasSpike;
}

void  Neuron::isRefractory(const step& t) {		 
	if (spikes_time_.size() != 0) {		
		isRefract_ = t-spikes_time_.back() < TAU_REFRACTORY;	
	} 		
}
//different getters
Index Neuron::getSpikeTimeSize() const {
	return spikes_time_.size();
}

step Neuron::getTimeSpike(const int& i) const {
	return spikes_time_[i];
}

double Neuron::getMembranePotential() const {
	return membrane_potential_;
}
std::vector<step> Neuron::getTimeSpikeTab() const {
	return spikes_time_;
}

bool Neuron::isExcitatory() const {
	return isExcitatory_;
}

//add a new spike
void Neuron::addSpikeTime(const step& time) {
	spikes_time_.push_back(time);
}

//store the times when spikes occured in a file
void Neuron::storeSpikeTime(std::ofstream& file, Index ind) const {	
	if (file.fail()) {
		std::cerr << "Error ";
	} else {
		for (size_t i(0); i < spikes_time_.size(); ++i) {
			file << spikes_time_[i]*H << '\t' << ind << '\n';
		}
	}		
}

//store the potential in a file
void Neuron::storePotentialMembrane(std::ofstream& file) const {
	if (file.fail()) {
			std::cerr << "Error ";
		} else {
			file << membrane_potential_ << std::endl;
		}	
}

void Neuron::setInputCurrent(const double& input) {
	input_current_ = input;
}

void Neuron::receive(const double& amplitude, const step& delay) {
	size_t size(timeDelayBuffer_.size());
	assert((clock_+delay)%size < size);
	timeDelayBuffer_[(clock_+delay)%size] += amplitude;
}


