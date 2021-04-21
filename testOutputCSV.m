clc, clear, close all;

A = readmatrix("ExportFile.csv");
t = A(1,:);

figure
plot(t,A(2:4,:));


title("pos");
legend('x','y','theta','location', 'best');
grid on
figure
plot(t,A(5:6,:));

title("acc");

grid on