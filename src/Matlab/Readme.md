# Matlab

This simulation and control law were tested on Matlab R2021b (Windows 10).

## How to launch the simulation 

1\. Open Matlab in `/system_control`

2\. (a) Double-click on `data.mat` from the "Current folder" window to load all the required variables. 

2\. (b) Write `load(data.mat)` in the "Command Window"

2\. (c) Import `data.mat` file using the "Model Explorer" in _Simulink_

3\. Double-click on `one_robot.slx` from the "Current folder" window to launch _Simulink_ and open the model. 

4\. Click on "Run" and after simulation, double-click on scopes to view output. 

## Code generation for an embedded system 

This simulation is ported to C using the `Code Generation` tool from Matlab. The result of this process is located in `src/simu_C`, how to compile it and launch it can be found in the readme located in the same folder. Here the process of code generation from Matlab is shown. 

1. Your Simulink should be seen as a unique block, like this: 

![Text](/assets/img/matlab/subsystem.png)

2. Right-click the subsystem and change `Block Parameters` as following: 

![Text](/assets/img/matlab/block_parameters_main.png)

![Text](/assets/img/matlab/block_parameters_code_generation.png)

3. Go to the `Terminal Window` in Matlab and run the following code to set the input values as signals: 

```
h1 = Simulink.Signal;
h2 = Simulink.Signal;
```

4. Return back to Simulink, right-click on the link between `h1` and the input of the subsystem and select `Properties` to apply the following (do the same for `h2`): 

![Text](/assets/img/matlab/h1_signal_properties.png)

5. Enter `Model Settings` under `MODELLING` as seen here : 

![Text](/assets/img/matlab/modelling_model_settings.png)

and apply the next options: 

![Text](/assets/img/matlab/model_settings_solver.png)

![Text](/assets/img/matlab/model_settings_hardware.png)

![Text](/assets/img/matlab/model_settings_code_generation.png)

![Text](/assets/img/matlab/model_settings_code_generation_interface.png)

6. When all settings are done, return to the block interface, and press the keyboard `Ctrl+B` to generate the code. A `Code Generation Report` will come out as follows.

![Text](/assets/img/matlab/code_generation_report.png)


NOTE: Before closing the project, you should better export variables and signals we use frequently from Base Workshop and import them to the project next time we use them.
