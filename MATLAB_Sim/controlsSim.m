% Simulate Controllers
clear all
close all
load('ParamVec0_individual');
load('ResidualVec');

% Residual Stuff

meanUdot = mean(delUdot_res(60:end));
stdUdot = std(delUdot_res(60:end));
stateDot = {'Udot','Vdot','Wdot','Pdot','Qdot','Rdot'};

for i=1:6
    
    tempFirst = ResidualVec(i,60:end);
    if i==5 || i==6
        stdFirst = std(tempFirst);
        idcs = logical(abs(tempFirst)>5*stdFirst);
        temp = tempFirst(~idcs);
    else
        temp = tempFirst;
    end
    
    noise.(stateDot{i}).mean = mean(temp);
    noise.(stateDot{i}).std = std(temp);
    
    
    %     plot(tempFirst)
    %     hold on
    %     plot(temp)
    %     clf
end


noiseMeanVec = [noise.Vdot.mean noise.Pdot.mean noise.Rdot.mean 0]';
noiseMeanStd = [noise.Vdot.std noise.Pdot.std noise.Rdot.std 0]';


% Open Loop
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

sys_OL = ss(A_roll,B_roll,C,D);
sys_simOL = ss(A_roll,eye(4),C,zeros(4,4));

t = 0:.01:10.01;
badDelt = 0.1;
x0 = (noiseMeanVec+noiseMeanStd)*badDelt;
x0 = x0.*[0 0 0 0]';

iso = [1 1 1 0]';
u = noiseMeanVec.*iso+1*noiseMeanStd.*iso.*randn(4,length(t));
% u = [(noiseMeanVec+noiseMeanStd)*ones(1,length(badDelt/.01)),zeros(4,length(t)-length(badDelt/.01))];

[y_OL,tOut_OL,x_OL] = lsim(sys_simOL,u,t,x0);
x_OL=x_OL'; y_OL=y_OL';

% Closed Loop
Q = 100*diag([1 1/100 1/100 10]);
R = eye(2);

[K,S,e] = lqr(sys_OL,Q,R);


D = zeros(4,4);

A_star = A_roll-B_roll*K;
sys_CL = ss(A_star,eye(4),C,D);

% u = zeros(4,length(t));

[y_CL,tOut_CL,x_CL] = lsim(sys_CL,u,t,x0);
x_CL=x_CL'; y_CL=y_CL';

figure
subplot(5,1,1)
plot(tOut_CL,x_CL(1,:))
hold on
plot(tOut_OL,x_OL(1,:))
ylabel('\Delta v [m/s]');
legend('Closed Loop','Open Loop')
grid on

subplot(5,1,2)
plot(tOut_CL,x_CL(2,:))
hold on
plot(tOut_OL,x_OL(2,:))
ylabel('\Delta p [rad/s]');
grid on

subplot(5,1,3)
plot(tOut_CL,x_CL(3,:))
hold on
plot(tOut_OL,x_OL(3,:))
ylabel('\Delta r [rad/s]');
grid on

subplot(5,1,4)
plot(tOut_CL,x_CL(4,:))
hold on
plot(tOut_OL,x_OL(4,:))
ylabel('\Delta \phi [rad]');
grid on

u_CL = -K*x_CL;
u_CL_speed = diff(u_CL)./repmat(diff(tOut_CL),2,1);

subplot(5,1,5)
plot(tOut_CL,u_CL(1,:))
hold on
plot(tOut_OL,u_CL(2,:))
ylabel('Control Input [deg]');
legend('Aileron','Rudder')

grid on
xlabel('Time [s]')

idcsOver = logical(abs(u_CL_speed(2,:))>60/.14);
totTimeOver = sum(tOut_CL(circshift(idcsOver,1))-tOut_CL(idcsOver));
disp(totTimeOver)


lambda = eig(A_roll);

zeta = sqrt(1/(1+(imag(lambda(3))/real(-lambda(3)))^2 ));

omega = -real(lambda(3))/zeta;

T = 2*pi/(omega*sqrt(1-zeta^2));
%}

% Pitch
%{
noiseMeanVec = [noise.Udot.mean noise.Wdot.mean noise.Qdot.mean 0]';
noiseMeanStd = [noise.Udot.std noise.Wdot.std noise.Qdot.std 0]';


% Open Loop
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

sys_OL = ss(A_pitch,B_pitch,C,D);
sys_simOL = ss(A_pitch,eye(4),C,zeros(4,4));

t = 0:.01:20.01;
badDelt = 0.1;
x0 = (noiseMeanVec+noiseMeanStd)*badDelt;
x0 = x0.*[0 0 0 0]';

iso = [1 0 0 0]';
% u = noiseMeanVec.*iso+0.1*noiseMeanStd.*iso.*randn(4,length(t));
u = [(noiseMeanVec+noiseMeanStd)*ones(1,length(badDelt/.01)),zeros(4,length(t)-length(badDelt/.01))];

[y_OL,tOut_OL,x_OL] = lsim(sys_simOL,u,t,x0);
x_OL=x_OL'; y_OL=y_OL';

% Closed Loop
Q = 500*diag([1 1/100 1 10]);
R = eye(2);

[K,S,e] = lqr(sys_OL,Q,R);


D = zeros(4,4);

A_star = A_pitch-B_pitch*K;
sys_CL = ss(A_star,eye(4),C,D);

% u = zeros(4,length(t));

[y_CL,tOut_CL,x_CL] = lsim(sys_CL,u,t,x0);
x_CL=x_CL'; y_CL=y_CL';

figure
subplot(5,1,1)
plot(tOut_CL,x_CL(1,:))
hold on
plot(tOut_OL,x_OL(1,:))
ylabel('\Delta u [m/s]');
legend('Closed Loop','Open Loop')
grid on

subplot(5,1,2)
plot(tOut_CL,x_CL(2,:))
hold on
plot(tOut_OL,x_OL(2,:))
ylabel('\Delta w [m/s]');
grid on

subplot(5,1,3)
plot(tOut_CL,x_CL(3,:))
hold on
plot(tOut_OL,x_OL(3,:))
ylabel('\Delta q [rad/s]');
grid on

subplot(5,1,4)
plot(tOut_CL,x_CL(4,:))
hold on
plot(tOut_OL,x_OL(4,:))
ylabel('\Delta \theta [rad]');
grid on

u_CL = -K*x_CL;
u_CL_speed = diff(u_CL)./repmat(diff(tOut_CL),2,1);

subplot(5,1,5)
plot(tOut_CL,u_CL(1,:))
hold on
plot(tOut_OL,u_CL(2,:))
ylabel('Control Input [deg]');
legend('Throttle','Elevator')

grid on
xlabel('Time [s]')

idcsOver = logical(abs(u_CL_speed(2,:))>60/.14);
totTimeOver = sum(tOut_CL(circshift(idcsOver,1))-tOut_CL(idcsOver));
disp(totTimeOver)


lambda = eig(A_pitch);

zeta = sqrt(1/(1+(imag(lambda(3))/real(-lambda(3)))^2 ));

omega = -real(lambda(3))/zeta;

T = 2*pi/(omega*sqrt(1-zeta^2));
%}