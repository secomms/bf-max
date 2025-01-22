### DFR simulation

The folder $\texttt{src}$ contains all C files to simulate the $\textsf{BF-Max}$ decoder for QC-codes with parity-check matrices formed by two circulant matrices.

In a Linux environment, this is how you compile and execute the code:
1) set simulation parameters from $\texttt{params.h}$
2) from main folder, do
     $\texttt{make clean}$
     $\texttt{make}$
3) run $\texttt{./build/main}$

The code produces two txt files:
- the one starting with $\texttt{QC}-\texttt{results}$ contains the estimated DFR values
- the one starting with $\texttt{QC}-\texttt{log}$ is updated constantly, to keep track of how the simulation is proceeding

### DFR theoretical model

The Sagemath notebook allows to compute the theoretical DFR for $\textsf{BF-Max}$.
