clc, clear, close all

A = readmatrix("TEST.csv");
t = A(1,:);

if (size(A,1) == 11)
    
    figure, hold on
    plot(t,A([2 3],:));
    plot(t,100.*A(4,:));
    
    title("pos");
    legend('x','y','100*theta','location', 'best');
    grid on
    figure
    plot(t,A(5:6,:));
    
    title("acc");
    
    grid on
    
else
    
    figure
    subplot(211)
    plot(t,A([2:3 7:8],:));
    grid on, title('pos'), legend('x_d','y_d','x_c','y_c','location','best')
    subplot(212)
    plot(t,A([5:6 9:10],:));
    grid on, title('acc'), legend('x_d','y_d','x_c','y_c','location','best')
    
end