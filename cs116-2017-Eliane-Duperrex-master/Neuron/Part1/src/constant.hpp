#ifndef CONSTANT_HPP
#define CONSTANT_HPP

///Constants specific to the time
const double T_SART = 100.0;
const double T_STOP = 400.0;
//dt
const double H = 0.1;
//to run the simulation faster
const double N = 1.0;

///Constants specific to the neuron
//time constant
const double TAU = 20.0;
//time constant in which the neuron is refractory
const double TAU_REFRACTORY = 2.0;
//capacity of the membrane
const double C = 1.0;
//membrane resistance
const double R = (TAU/C);
//potential threshold
const double V_threshold = 20.0;

//amplitude entre v?thr et vreset
const double J = 0.1; //mV

#endif
