clc, clear, close all;

%% discrete system variables
dt = 10e-3; %discrete time step
fs = 1/dt; %sampling frequncy 
time = 0:dt:20;             %time vector in steps of T_steps


%% Thrust vector
g=9.81;
weight = 3;
N=g*weight;

thrustVector = -N*exp(-0.5*time)+N;       %thrust that starts at 0 and settles on 30Newton gradually over 5 seconds

 plot(time, flip(thrustVector));

%% Rotanional velocity vector

rotationalVelocity = zeros(size(time));         %rotational vecocity of zeros for length of time

rotationalVelocity(13*fs:15*fs-1) = 0.5; % 0.5 rad per sec for 2 seconds from 13 to 15 seconds
rotationalVelocity(15*fs:17*fs-1) = -1.0; % -0.5 rad per sec for 2 seconds from 15 to 17 seconds
 plot(time, rotationalVelocity);

%% Assembly of Input States Matrix

InputMatrix = zeros(3,length(time));
InputMatrix(1,:) = time;
InputMatrix(2,:) = flip(thrustVector);
InputMatrix(3,:) = rotationalVelocity;


%% Output CSV

writematrix(InputMatrix.', "InputMatrix.csv");

% 
% A = [0   2   4;...
%      30  25   0;...
%      0   0   0];
% 
% A = [0  2    4       6       10;...
%      0  2    1       1        0.5;...
%      0  0   0.5     -0.5     0];
 

% writematrix(A.', "NietOnnodigIngewikkeld.csv");