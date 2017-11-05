/*!A constant file */
#ifndef CONSTANT_HPP
#define CONSTANT_HPP

typedef unsigned int step; ///to count time in step
typedef size_t Index; ///for tab index

static constexpr double H = 0.1; //!<time partition
static const step N = 1; //!<to run the simulation faster

///Constants specific to the time
const step T_START = 100.0/H;
const step T_STOP = 400.0/H;	
		
const double D = 1.5; //!<delay [ms]
const step DELAY = D/H; //!<delay in step
	
const double MU_EXT = 2.0; //!<potential extern
const double G = 5.0; //!<rate

const double J_EXCITATORY = 0.1; //!<amplitude between vthr and vreset in mV
const double J_INHIBITORY = -G*J_EXCITATORY; //!<amplitude for an inhibitory neuron
const double J_EXT = 0.1; //!<amplitude from the background noise

#endif
