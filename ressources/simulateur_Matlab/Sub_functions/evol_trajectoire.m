function xref_pt = evol_trajectoire(xref,uref)

% Function making the computation of the kinematic evolution of the virtual
% robot leading to the reference trajectory.
% The modeling is based on a classic tank-like virtual robot.
%
% x_pt = [x_dot;y_dot;theta_dot]: output signals, velocity on x, y, and
%                                  angular velocity of the orientation theta
% x = [x;y;theta]: state vector of the robot, position (x,y), and absolute orientation theta 
% u = [v;theta_pt]: control signal, velocity and angular velocity of orientation 
%

xref_pt = [uref(1)*cos(xref(3));...
           uref(1)*sin((xref(3)));...
           uref(2)];

% xref_pt = [-uref(1)*sin(xref(3));...
%             uref(1)*cos((xref(3)));...
%             uref(2)];