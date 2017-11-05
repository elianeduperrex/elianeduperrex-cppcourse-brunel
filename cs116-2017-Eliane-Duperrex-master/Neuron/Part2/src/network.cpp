#include "network.hpp"
#include <cassert>
#include <random>
#include <iostream>
using namespace std;

Network::Network() {
	//initialisation of the network
	initialiseNeurons(N_EXCITATORY, N_INHIBITORY);
	assert(neurons_.size() == N_TOTAL);
	initialiseConnexion(N_EXCITATORY, N_INHIBITORY, C_EXCITATORY, C_INHIBITORY);
}

Network::Network(const int& excitat_numb, const int& inhibit_numb, 
				const int& excitat_connexion, const int& inhibit_connexion) {
	initialiseNeurons(excitat_numb, inhibit_numb);
	assert(neurons_.size() == excitat_numb + inhibit_numb);
	initialiseConnexion(excitat_numb, inhibit_numb, excitat_connexion, inhibit_connexion);
	assert(connexion_.size() == excitat_numb + inhibit_numb);
	assert(connexion_[0].size() ==inhibit_connexion + excitat_connexion);
}

void Network::initialiseNeurons(const int& excitatory_number, const int& inhibitory_number) {
	bool isExcitatory(true);
	int neuron_number(excitatory_number + inhibitory_number);
	for (int i(0); i < neuron_number; ++i) {
		//to set 2500 neurons inibitory
		if (i > excitatory_number) {
			isExcitatory = false;
		}
		Neuron neur(isExcitatory);
		Neuron* neuron(new Neuron (neur));
		assert (neuron != nullptr);
		neurons_.push_back(neuron);
	}
}

void Network::initialiseConnexion	(const int& excitatory_number, 
									const int& inhibitory_number, 
									const int& excitatory_connexion, 
									const int& inhibitory_connexion) 
{	
	int total_number(excitatory_number + inhibitory_number);
	int total_connexion(inhibitory_connexion + excitatory_connexion);
	//set the size to the total number of neurons
	connexion_.resize(total_number);
	
	static std::random_device r;
	static std::mt19937 generator(r());
	
	for (int i(0); i < total_number ; ++i) {
		assert(i < connexion_.size());
		for(int k(0); k < total_connexion; ++k) {			
			int indexConnexion(0);
			if (k < excitatory_connexion) {	
				uniform_int_distribution<int> distribExcit(0,excitatory_number -1);
				indexConnexion = distribExcit(generator);
			} else {
				uniform_int_distribution<int> distribInhib(excitatory_number,total_number -1);
				indexConnexion = distribInhib(generator);
			}
			assert(i < connexion_.size());
			connexion_[i].push_back(indexConnexion);
		}
	}
}

void Network::storeConnexion(ofstream& file) const {
	if (file.fail()) {
			std::cerr << "Error ";
		} else {
			file << "Neurons connexions " << endl;
			for (int i(0); i < connexion_.size(); ++i) {
				for (int j(0); j < connexion_[i].size(); ++j) {
					file << connexion_[i][j] << " ";
				}
				file << endl;
			}
		}
}


Network::~Network () {
	for (size_t i(0); i < neurons_.size(); ++i) {
		delete neurons_[i];
		neurons_[i] = nullptr;
	}
	neurons_.clear();
}

void Network::update(const step& t) {
	assert(neurons_.size() != 0);
	for (size_t i(0); i < neurons_.size(); ++i) {
		bool spike = false;
		assert(i < neurons_.size());
		assert(neurons_[i] != nullptr);
		double rate(MU_EXT);
		spike = neurons_[i]->update(t, poissonGenerator(rate));
		if (spike) {
			//give the spike to the connected neurons
			//in column are the neurons and in ligns are the receveid connexion
			double j(0.0);
			if (neurons_[i]->isExcitatory()) {
				j = J_EXCITATORY;
			} else {
				j = J_INHIBITORY;
			} 
			for (size_t k(0); k < connexion_[i].size(); ++k) {
				assert(k < connexion_[i].size());				
				neurons_[connexion_[i][k]] -> receive(j, DELAY);
			}
		}
	}
}

void Network::storeTimeSpike(std::ofstream& file) const {
	int i(1);
	for (auto& neuron : neurons_) {
		neuron -> storeSpikeTime(file, i);
		++i;
	}	
}

Index Network::getNbNeurons() const {
	return neurons_.size();
}

array<Index, 2> Network::getConnexionMatrixSize() const {
	return {connexion_.size(), connexion_[0].size()};
}

void Network::storePotential(const Index& i, std::ofstream& file) const {
		file << "Neuron " << i+1 << " : potential ";
		neurons_[i]->storePotentialMembrane(file);
}

double Network::getMembranePotentialNeuron(Index i) const {
	return neurons_[i]->getMembranePotential();
}

int Network::poissonGenerator(const double& rate) {
	int i(0);
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution <> p(rate);
	i = p(gen);
	return i;
}
