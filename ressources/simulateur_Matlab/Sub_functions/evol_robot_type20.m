function x_pt = evol_robot_type20(x,u)

% Function making the computation of the kinematic evolution of a robot.
% The modeling is based on a classic tank-like virtual robot.
%
% x_pt = [x_dot;y_dot;theta_dot;v_dot]: output signals, velocity on x, y,
%                                       angular velocity of the orientation
%                                       theta, and linear acceleration
% x = [x;y;theta;v]: state vector of the robot, position (x,y), 
%                    absolute orientation theta and linear velocity
% u = [v;theta_pt]: control signal, velocity and angular velocity of
% orientation 
%

x_pt = [x(4)*cos(x(3));...
        x(4)*sin((x(3)));...
        u(1);...
        u(2)];
