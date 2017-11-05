/*!A network class */
#ifndef NETWORK_HPP
#define NETWORK_HPP
#include <vector>
#include "neuron.hpp"
#include "constant.hpp"
#include <array>
using namespace std;

class Network {
	private :
		vector<Neuron*> neurons_; ///<neurons in the network
		/**
		 * each line correspond to a neuron
		 * each column correspond to the different neurons 
		 * which are connected to the neuron of the line
		 * each cell contains the index (in neurons_) of the connected neuron
		 * */
		vector<vector<Index> > connexion_; //!<matrix of connexions between the neurons
		/**
		 * generate the poisson distribution
		 * @param the rate of the average time for poisson distribution
		 * @return result of distribution
		 * */
		int poissonGenerator(const double& rate);
		/**
		 * initialise the vector of neurons
		 * allocates memory for the neurons
		 * first (number of excitatory neurons) indexes in vector
		 * would be initialise as excitatory
		 * the rest of the vector would be the inhibitory neurons
		 * @param number of excitatory neurons
		 * @param number of inhibitory neurons
		 * */
		void initialiseNeurons(const int& excitatory_number, const int& inhibitory_number);
		/**
		 * initialise randomly the connexion matrix
		 * resize the number of lines to total number of neurons
		 * goes through the lines
		 * add a connexion for each columns with a pushback of a random number
		 * the first (excitatory_connexion) indexes are picked from excitatory neuron
		 * the rest of the indexes correspond to inhibitory neurons
		 * @param number of excitatory neurons
		 * @param number of inhibitory neurons
		 * @param number of excitatory connexion
		 * @param number of inhibitory connexion
		 * */
		void initialiseConnexion	(const int& excitatory_number, 
									const int& inhibitory_number, 
									const int& excitatory_connexion, 
									const int& inhibitory_connexion);
	
		const int N_EXCITATORY = 10000; //!<number of excitatory neuron
		const int N_INHIBITORY = 2500; //!<number of inhibitory neuron
		const int N_TOTAL = N_EXCITATORY + N_INHIBITORY; //!<total number
		const int C_EXCITATORY = 0.1*N_EXCITATORY; //!<number of excitatory connexion (10%)
		const int C_INHIBITORY = 0.1*N_INHIBITORY; //!<number of inhibitory connexion (10%)
		const int C_TOTAL = C_EXCITATORY + C_INHIBITORY; //!<total number of connexion
	public:
		/**
		 * Constructor by default
		 * @see initialiseConnexion 
		 * @see initialiseNeurons
		 * print Network created
		 * with default constants in constant.hpp
		 * */
		Network();
		/**
		 * Constructor with initialisation
		 * @param number of excitatory neurons
		 * @param number of inhibitory neurons
		 * @param number of excitatory connexion
		 * @param number of inhibitory connexion
		 * calls initialiseConnexion and initialiseNeurons
		 * with the parameters
		*/
		Network(const int& excitat_numb, const int& inhibit_numb, 
				const int& excitat_connexion, const int& inhibit_connexion);
		/**
		 * Destructor which delete the vector of pointers on neurons
		 * */
		~Network();
		/**
		 * GETTER
		 * @return total number of neuron
		 * */
		Index getNbNeurons() const;
		/**
		 * GETTER
		 * @return connexion of matrix size 
		 * first number of column 
		 * second number of ligns for the first index
		 * */
		 array<Index, 2> getConnexionMatrixSize() const;
		/**
		 * GETTER
		 * @param index of the neuron we want to have the membrane potential
		 * @return membrane potential of a specific neuron i
		 * */
		double getMembranePotentialNeuron(Index i) const;
		/**
		 * update the network with updating all the neurons in the vector neurons_
		 * update each neuron with the poisson generator 
		 * calculate the poisson generator in method poissonGenerator
		 * if a neuron spike then he transfer his amplitude 
		 * to all the neurons he is connected to with method Neuron::receive 
		 * @param time step
		 * */
		void update(const step& t);
		/**
		 * method to store the spike time of each neurons
		 * @param file where data would be collected
		 * */
		void storeTimeSpike(std::ofstream& file) const;
		/**
		 * method to store the potential of a specific neuron
		 * */
		void storePotential(const Index& i, std::ofstream& file) const;
		/**
		 * method to store the matrix of connexion
		 * @param file where indexes will be stored
		 * */
		void storeConnexion(ofstream& file) const;
};

#endif
