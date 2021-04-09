clc, clear, close all

A = readmatrix("TEST.csv");
t = A(1,:);

figure
plot(t,A([2:3 7:8],:));
grid on
figure
plot(t,A([5:6 9:10],:));
grid on