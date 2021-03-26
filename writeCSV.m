clear; 
close;
clc;

%% discrete system variables
T_step = 10e-3; %discrete time step
F = 1/T_step; %sampling frequncy 
time = 0:T_step:20;             %time vector in steps of T_steps


%% Thrust vector 
thrustVector = -30*exp(-0.5*time)+30;       %thrust that starts at 0 and settles on 30Newton gradually over 5 seconds

% plot(time, thrustVector);

%% Rotanional velocity vector

rotationalVelocity = zeros(size(time));         %rotational vecocity of zeros for length of time

rotationalVelocity(13*F:15*F-1) = 0.5; % 0.5 rad per sec for 2 seconds from 13 to 15 seconds
rotationalVelocity(15*F:17*F-1) = -0.5; % -0.5 rad per sec for 2 seconds from 15 to 17 seconds

% plot(time, rotationalVelocity);

%% Assembly of Input States Matrix

InputMatrix=zeros(length(time),3);
InputMatrix(:,1) = time';
InputMatrix(:,2) = thrustVector';
InputMatrix(:,3) = rotationalVelocity';


%% Output CSV

writematrix(InputMatrix, "InputMatrix.csv");