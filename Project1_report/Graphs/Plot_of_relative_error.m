close all
clear all
clc
%Plot of nummerical approximation with n=10, n=100 and n=1000 and
%closed-form formula

%Import data and define closed-form solution

filename = 'Results.xlsx';
sheet = 7;
xlRange = 'C4:D8';

[v,T,vT] = xlsread(filename, sheet, xlRange);
h=v(:,1);error=v(:,2);

%Plot data and closed-form solution

figure
plot(h,error,'-ko')

xlim([-6 0])
ylim([-10 0])

title('Relative error','FontSize',12)
xlabel('log(h)')
ylabel('relative error')
