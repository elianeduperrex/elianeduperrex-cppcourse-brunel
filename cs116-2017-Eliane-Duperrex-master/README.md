# cs116-2017-Eliane-Duperrex

Presentation of the program:

The program is a simulation of a network of neurons, which is based on the paper "Dynamics of Sparsely Connected Networks of Excitatory
and Inhibitory Spiking Neurons" from Nicolas Brunel. 
It can generate the different graphs described in the article (Figure 8 p.15).

The network contains 12500 neurons by default (10000 excitatory and 2500 inhibitory). 
The probability of connexion is 10%.

The simulation time is asked at the start of the simulation.

The file times_spike is created in the res repository during the simulation. 
It stores the time when a neuron spike and its number.

How to run the program:

- entrer cmake ../src will compile the program
- enter make in the build repository will build the program. 
- It will ask you for a time of simulation.
- Update the network with the constants
- Store the times of spike in a file "times_spike"
- You can generate the graph if from the repository 'src', you run with python the file spike_graph.py
- you can generate doxygen from the 'build' repository (enter make documentation and the documentation will be stored in a repository in build)

In 'res' repository, there are the different graphs stored from the Brunel article.

The documentation is provided by doxygen in 'build/documentation_doxygen'. It extracts all members of the two classes (Neuron and Network) and includes all cpp and hpp files.
