close all
clear all
clc
%Plot of nummerical approximation with n=10, n=100 and n=1000 and
%closed-form formula

%Import data and define closed-form solution

filename = 'Results.xlsx';
sheet = 4;
xlRange = 'B3:C12';

[v,T,vT] = xlsread(filename, sheet, xlRange);
x10=v(:,1);y10=v(:,2);

filename = 'Results.xlsx';
sheet = 5;
xlRange = 'B3:C102';

[v,T,vT] = xlsread(filename, sheet, xlRange);
x100=v(:,1);y100=v(:,2);

filename = 'Results.xlsx';
sheet = 6;
xlRange = 'B3:C1002';

[v,T,vT] = xlsread(filename, sheet, xlRange);
x1000=v(:,1);y1000=v(:,2);

n=1000;

h=1/(n+1);

x = 0:h:1;
y_exact = 1-(1-exp(-10))*x-exp(-10*x);

%Plot data and closed-form solution

figure
plot(x100,y100,'-.b',x1000,y1000,'m',x,y_exact,'--k')
legend('n=100','n=1000','closed-form solution')

xlim([0.2 0.3])
ylim([0.65 0.675])

title('Estimation of solution, zoom','FontSize',12)
xlabel('x')
ylabel('u(x)')
