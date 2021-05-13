%% State EKF
% EKF of just dynamic states without the specific aero model

close all;
rng(11);
d2r = pi/180;

try rho;
    
catch

%{ 
TODO:

       
%}

%% Constants

% Sim version for MC
% syms rho g0 u0 Theta0
% consts = [rho g0 S m u0 Theta0];

% non-sim version for MATLAB
rho = 1.225; % kg/m^3
g0 = 9.8; % m/s^2

%% Load and Parse Flight Data
startIdx = 1365;        % This is specific to each set of flight data
% startIdx = 1;
% endIdx = 1633;
addpath('DataFiles');
[flightData] = loadFlightData("DataFiles/realFlight1.TXT",startIdx);

n_measurements = size(flightData.Time,1);

%% States

syms t

% States
syms N E D u v w phi theta psi p q r real
xs = transpose([N E D u v w phi theta psi p q r]);
ns = length(xs);

xp = transpose([]);
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs

syms de dT da dr real
cntrl = transpose([dT da de dr]);

% Dynamics

I_C_B = R_z(psi)*R_y(theta)*R_x(phi);

matlabFunction(I_C_B,'Vars',{phi,theta,psi},'File','I_C_B_Fcn');


fs = [
    % Position
    I_C_B*[u;v;w];...

    % Velocity
    0;0;0;...
    
    % Angles
    p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta);...   % phidot
    q*cos(phi) + -r*sin(phi);...                            % thetadot
    q*sin(phi)*sec(theta) + r*cos(phi)*sec(theta);...       % psidot
    
    % Angular Velocity
    0;0;0 ...
    ];

fp = zeros(np,1);

f = [fs;fp];


% Continuous time diff eq of motion
f_Fcn = matlabFunction(f,'Vars',{t,[x;cntrl]},'File','f_Fcn');

% for ode45

f_cntrl = [f;zeros(length(cntrl),1)];
f_cntrl_Fcn = matlabFunction(f_cntrl,'Vars',{t,[x;cntrl]},'File','f_cntrl_Fcn');


F = jacobian(f,x);

% df/dx jacobian
F_jac_Fcn = matlabFunction(F,'Vars',{x,cntrl},'File','F_jac_Fcn');


%% Noise

% ---- Process Noise ---- %

% States
sigmaP.accel = .1; % m/s^2
sigmaP.alpha = .01; % rad/s^2
Qs = diag([sigmaP.accel^2*ones(3,1);sigmaP.alpha^2*ones(3,1)]);

Gs = zeros(ns,size(Qs,1)); 
Gs(4,1) = 1; Gs(5,2) = 1; Gs(6,3) = 1;  % accel
Gs(10,4) = 1; Gs(11,5) = 1; Gs(12,6) = 1;  % angular accel


% Parameters
Qp = [];
Gp = zeros(np,size(Gs,2));

% Combine
Q = blkdiag(Qs,Qp);
G = [Gs;Gp];

% ---- Measurement Noise ---- %

[sigmaN] = makeSigma("Combined_DATALOG");


R = diag([sigmaN.N, sigmaN.E, sigmaN.D,...
          sigmaN.Speed, sigmaN.Heading].^2);
          
 
R_Fcn = matlabFunction(R,'Vars',dT,'File','R_Fcn');




%% Sensor Measurement

h = [N;...                                          % Relative Positions
     E;...
     D;...
     norm([u;v;w]);...                              % Speed
     psi;                                           % Heading
     ];
 
 % Full measurement
h_Fcn = matlabFunction(h,'Vars',{x,cntrl},'File','h_Fcn');

% Jacobian
H = jacobian(h,x);
H_jac_Fcn = matlabFunction(H,'Vars',{x,cntrl},'File','H_jac_Fcn');

r0_ECEF = LatLonAlt2ECEF(flightData.Lat(1),flightData.Lon(1),flightData.Alt(1));
[NED_C_ECEF] = TECEF2NED(r0_ECEF);
r_ECEF = LatLonAlt2ECEF(flightData.Lat',flightData.Lon',flightData.Alt');

r_NED = zeros(3,size(r_ECEF,2));
for i=1:size(r_ECEF,2)
    r_NED(:,i) = NED_C_ECEF*(r_ECEF(:,i)-r_ECEF(:,1));
end

% Z_input =smoothdata([flightData.Acc.x';...
%     flightData.Acc.y';...
%     flightData.Acc.z';...
%     flightData.Gyr.x';...
%     flightData.Gyr.y';...
%     flightData.Gyr.z';...
%     ],2);
% 
%  Z =[r_NED;...
%     flightData.Speed';...
%     flightData.Heading'...
%     ];

end

%% Initial Conditions

% xs = transpose([N E D u v w phi theta psi p q r]);

xs0 = [0;0;0;...
       5;0;0;...
       0*d2r;0*d2r;82.8581*d2r;...
       0;0;0;...
       ];
  

xp0 = [];
   
x0 = [xs0;xp0];

Ps0 = diag([0;0;0;...
            5;5;5;...
            .01;.5;.5;...
            .1;.1;.1].^2);
Pp0 = diag([]);
P0 = diag([diag(Ps0);diag(Pp0)]);

% Instantiate Vars
xhat1p = nan(n,n_measurements); P1p=nan(n,n,n_measurements);
xhat1u = nan(n,n_measurements); P1u=nan(n,n,n_measurements);

xhat1u(:,1)=x0;P1u(:,:,1)=P0;



%% Simulator

[tTrue,xTrue] = ode45(@f_Fcn,0:1/20:20,x0);
xTrue =xTrue';

plot3(xTrue(2,:),xTrue(1,:),-xTrue(3,:));
axis equal
xlabel('E'); ylabel('N'); zlabel('D');

dT = 0;
v_input = double(subs([sigmaN.Acc.x;sigmaN.Acc.y;sigmaN.Acc.z;sigmaN.Gyr.x;sigmaN.Gyr.y;sigmaN.Gyr.z]));
v = double(subs([sigmaN.N;sigmaN.E;sigmaN.D;sigmaN.Speed;sigmaN.Heading]));

for i = 1:length(tTrue)
    Z_input(:,i) = [I_C_B_Fcn(xTrue(7),xTrue(8),xTrue(9))*[0;0;-9.8];0;0;0] + v_input.*randn(6,1);

    Z(:,i) = h_Fcn(xTrue(:,i)) + v.*randn(5,1);
end

figure
for i=1:3
subplot(3,2,2*i-1)
plot(Z_input(i,:));
end
Z_input = smoothdata(Z_input,2);
for i=1:3
subplot(3,2,2*i)
plot(Z_input(i,:));
end



%% Estimator

n_measurements = length(tTrue);

condP = nan(n_measurements,1);


tic
for k=1:(n_measurements-1)
    % Display
    if mod(k,n_measurements)==0
        disp(num2str(100*k/n_measurements));
    end
    
%     delt = (flightData.Time(k+1)-flightData.Time(k));
    delt = 1/20;
%     cntrl_k = [flightData.Throttle(k);...
    cntrl_k = [dT;...
        flightData.Aileron(k);...
        flightData.Elevator(k);...
        flightData.Rudder(k)];
    
    % Predict State
    xhat1p(:,k+1)=predict_stateparam_J(xhat1u(:,k),cntrl_k,Z_input(:,k),delt);
    
    % Predict Covariance
    [F] = getF_stateparam(xhat1u(:,k),cntrl_k,delt);
    P1p(1:n,1:n,k+1) = F*P1u(1:n,1:n,k)*F';% + G*Q*G'*delt^2;
    
    try condP(k) = cond(P1p(1:n,1:n,k+1));
    catch
        disp('');
    end
%     cntrl_kp1 = [flightData.Throttle(k+1);...
    cntrl_kp1 = [dT;...
        flightData.Aileron(k+1);...
        flightData.Elevator(k+1);...
        flightData.Rudder(k+1)];
    
    if k==100
        1;
    end
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),cntrl_kp1);
    R = R_Fcn(cntrl_kp1(1));
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
    
    % Update
    xhat1u(:,k+1) = xhat1p(:,k+1) + K *(Z(:,k+1) - h_Fcn(xhat1p(:,k+1),cntrl_kp1));
    P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    
    
end
toc

% Position
figure
for i=1:3
    subplot(3,2,2*i-1)
    els = i;
    plot(tTrue,xhat1u(els,:))
    hold on
    plot(tTrue,xTrue(els,:))
    plot(tTrue,Z(i,:),'*');
    
    subplot(3,2,2*i)
    els = i;
    plot(tTrue,xhat1u(els,:)-xTrue(els,:))
    hold on
    plot(tTrue,Z(i,:)-xTrue(els,:),'*');

end

% Angles
figure
for i=1:3
    subplot(3,2,2*i-1)
    els = i+6;
    plot(tTrue,xhat1u(els,:))
    hold on
    plot(tTrue,xTrue(els,:))
    if i==3
        plot(tTrue,Z(5,:),'*');
    end
    
    subplot(3,2,2*i)
    els = i+6;
    plot(tTrue,xhat1u(els,:)-xTrue(els,:))
    hold on
    if i==3
        plot(tTrue,Z(5,:)-xTrue(els,:),'*');
    end

end









