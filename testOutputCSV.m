clc, clear, close all;

A = readmatrix("TEST.csv");
t = A(1,:);

figure
plot(t,A(2:3,:));
grid on
figure
plot(t,A(5:6,:));
grid on