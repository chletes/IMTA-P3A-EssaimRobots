## Simulation in C

Added to the generated code by Matlab, we added a motion planning system. We use the trapezoidal timing law to generate the trajectory between two positions.

### How to build it

Type `make` in a command window in this folder. 

### How to launch it

Type `main.exe` in a command window in this folder. The simulation takes time. 

### Outputs. 

After the simulation, you will notice two output `.mat` files. 
- `traj_input.mat` are the desired trajectories positions. 
- `traj_output.mat` are the real trajectories positions. 

You can use these two files to plot in Matlab. 

Important parameters definition are in the file parameters.h
- PID parameters:  P_t  I_t  D_t                          
- Filter parameter of PID block:  N_t   
- Length of robot(cm):  L
- Max speed (cm/s) of robot: Vm
- Sampling time (s): Ts
