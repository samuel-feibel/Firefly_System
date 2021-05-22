% Simulation of Dynamics
clear all
close all
load('ParamVec0_individual');

A_roll = [Yv Yp -(u0-Yr) 9.8;...
           Lv Lp Lr 0;...
           Nv Np Nr 0 ;...
           0 1 0 0];
       
B_roll = [0 Ydr;...
           Lda Ldr;...
           Nda Ndr;...
           0 0];
       
C = eye(4);
D = zeros(4,2);

sys = ss(A_roll,B_roll,C,D);

t = 0:.01:20.01;
u = [zeros(2,length(t)/2),[zeros(1,100);ones(1,100)],zeros(2,length(t)/2-100)];
% u = zeros(2,length(t));

x0 = [0 0 0 0]';
[y,tOut,x] = lsim(sys,u,t,x0);
x=x'; y=y';

figure
subplot(4,1,1)
plot(tOut,x(1,:))
ylabel('\Delta v');

subplot(4,1,2)
plot(tOut,x(2,:))
ylabel('\Delta p');

subplot(4,1,3)
plot(tOut,x(3,:))
ylabel('\Delta r');

subplot(4,1,4)
plot(tOut,x(4,:))
ylabel('\Delta \phi');
xlabel('Time [s]')

lambda = eig(A_roll);

zeta = sqrt(1/(1+(imag(lambda(3))/real(-lambda(3)))^2 ));

omega = -real(lambda(3))/zeta;

T = 2*pi/(omega*sqrt(1-zeta^2));

%Pitch
%{
A_pitch = [Xu Xw 0 -9.8;...
           Zu Zw u0 0;...
           MuComb MwComb MqComb 0 ;...
           0 0 1 0];
       
B_pitch = [Xde XdT;...
           Zde ZdT;...
           MdeComb MdTComb;...
           0 0];
       
C = eye(4);
D = zeros(4,2);

sys = ss(A_pitch,B_pitch,C,D);

t = 0:.01:10.01;
u = [zeros(2,length(t)/2),[zeros(1,100);ones(1,100)],zeros(2,length(t)/2-100)];
% u = zeros(2,length(t));

x0 = [0 0 0 0]';
[y,tOut,x] = lsim(sys,u,t,x0);
x=x'; y=y';

figure
subplot(4,1,1)
plot(tOut,x(1,:))
ylabel('\Delta u');

subplot(4,1,2)
plot(tOut,x(2,:))
ylabel('\Delta w');

subplot(4,1,3)
plot(tOut,x(3,:))
ylabel('\Delta q');

subplot(4,1,4)
plot(tOut,x(4,:))
ylabel('\Delta \theta');
xlabel('Time [s]')

lambda = eig(A_pitch);

zeta = sqrt(1/(1+(imag(lambda(3))/real(-lambda(3)))^2 ));

omega = -real(lambda(3))/zeta;

T = 2*pi/(omega*sqrt(1-zeta^2));
%}