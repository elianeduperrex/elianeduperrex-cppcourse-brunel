#include "network.hpp"
#include "neuron.hpp"
#include <cmath>
#include "gtest/gtest.h"

///test the membrane potential
TEST (NeuronTest, MembranePotential) {
	Neuron neuron1, neuron2;
	neuron1.setInputCurrent(1.0);
	neuron1.update(1, 0);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)), neuron1.getMembranePotential(), 10e-5);
	neuron1.update(10000, 0);
	EXPECT_GT(10e-3, std::fabs(19.999 - neuron1.getMembranePotential()));
	EXPECT_EQ(0, neuron1.getSpikeTimeSize());
	
	neuron2.setInputCurrent(0.0);
	neuron2.update(1, 0);
	EXPECT_EQ(0.0, neuron2.getMembranePotential());
}
///test if the spikes occure at correct time
TEST (NeuronTest, SpikeTime) {
	Neuron neuron;
	neuron.setInputCurrent(1.01);
	for (int i(1000); i < 4000; ++i) {
		neuron.update(1, 0);
	}
	EXPECT_NEAR(92.4, neuron.getTimeSpike(0)*0.1, 10e-2);
	EXPECT_NEAR(186.8, neuron.getTimeSpike(1)*0.1, 10e-2);
	EXPECT_NEAR(281.2, neuron.getTimeSpike(2)*0.1, 10e-2);
	
	Neuron neuron2;
	neuron2.setInputCurrent(1.01);
	neuron2.update(924, 0);
	EXPECT_EQ(0, neuron2.getSpikeTimeSize());
	neuron2.update(1, 0);
	EXPECT_EQ(1, neuron2.getSpikeTimeSize());
	EXPECT_EQ(0.0, neuron2.getMembranePotential());
	neuron2.update(1868, 0);
	EXPECT_EQ(2, neuron2.getSpikeTimeSize());
}
///test the connexion between two neurons with a delay
TEST(NeuronTest, Connexion) {
	Neuron neuron1, neuron2;
	int delay(15);
	neuron1.setInputCurrent(1.01);
	for(int i(0); i < 925+delay ; ++i) {
		if(neuron1.update(1, 0)) {
			neuron2.receive(0.1, delay);
			EXPECT_EQ(0.0, neuron1.getMembranePotential());
			EXPECT_EQ(0.0, neuron2.getMembranePotential());
		}
		neuron2.update(1, 0);
	 }
	 
	EXPECT_EQ(0.1, neuron2.getMembranePotential());
	
	Neuron neur;
	step time(1000);
	neur.receive(0.1, 0);
	///creation of a neuron and give it that a neuron connected to it spiked
	///at initialisation the membrane potential is at 0.0 -> the potential varies only with J 
	neur.update(1, 0);
	EXPECT_EQ(neur.getMembranePotential(), 0.1);
}
///test the initialisation of the network
TEST(NetworkTest, Initialisation) {
	 Network networkNeurons;
	 EXPECT_EQ(12500, networkNeurons.getNbNeurons());
	 array<size_t, 2> matrixSize(networkNeurons.getConnexionMatrixSize());
	 EXPECT_EQ(12500, matrixSize[0]);
	 EXPECT_EQ(1250, matrixSize[1]);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
