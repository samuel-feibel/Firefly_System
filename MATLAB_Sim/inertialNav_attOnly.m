%% Inertial Nav + GPS
% Finds attitude and position from sensors only, no model

close all;
rng(12);
d2r = pi/180;

try r_NED;
    
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
startIdx = 1792;        % This is specific to each set of flight data

addpath('DataFiles');
[flightData] = loadFlightData("DataFiles/ParamEstFlight1.TXT",startIdx);

n_measurements = size(flightData.Time,1);

%% States

syms t

% States
syms phi theta psi real
xs = transpose([phi theta psi]);
ns = length(xs);
angleEls = 1:3;

xp = transpose([]);
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs

syms p q r real
cntrl = transpose([p q r]);

% Dynamics

I_C_B = (R_z(psi)*R_y(theta)*R_x(phi));

matlabFunction(I_C_B,'Vars',{phi,theta,psi},'File','I_C_B_Fcn');


fs = [0;0;0 ...
    ];

fs = fs + [p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta);...   % phidot
            q*cos(phi) + -r*sin(phi);...                            % thetadot
            q*sin(phi)*sec(theta) + r*cos(phi)*sec(theta);          % psidot
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

[sigmaN] = makeSigma("Combined_DATALOG");


% ---- Process Noise ---- %

% States
Qs = diag([sigmaN.Gyr.x,sigmaN.Gyr.y,sigmaN.Gyr.z].^2);

Gs = zeros(ns,size(Qs,1)); 
Gs = eye(3);  % angular accel

% Parameters
Qp = [];
Gp = zeros(np,size(Gs,2));

% Combine
Q = blkdiag(Qs,Qp);
G = [Gs;Gp];

syms dT
Q_Fcn = matlabFunction(Q,'Vars',dT,'File','Q_Fcn');


% ---- Measurement Noise ---- %

R = diag([sigmaN.Mag.x, sigmaN.Mag.y,sigmaN.Mag.z,...
          sigmaN.Heading].^2);       
 
R_Fcn = matlabFunction(R,'Vars',dT,'File','R_Fcn');

%% Sensor Measurement

[bias,magVec0] = makeBias("magTuning_NorthLevel.txt");

h = [I_C_B'*magVec0;...
     psi];
 
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

Z_input = [flightData.Gyr.x';...
           flightData.Gyr.y';...
           flightData.Gyr.z';...
           ] - ...
           [bias.Gyr.x';...
           bias.Gyr.y';...
           bias.Gyr.z';...
           ];

 Z =[flightData.Mag.x';...
    flightData.Mag.y';...
    flightData.Mag.z';...
    flightData.Heading'...
    ];

end

%% Simulation Data

dT = 0;

% Q = Q_Fcn(dT);
% Z_input = 0 + diag(sqrt(Q)).*randn(3,n_measurements);
% 
% R = R_Fcn(dT);
% Z = magVec0 + diag(sqrt(R)).*randn(3,n_measurements);

%% Initial Conditions

clear xhat1u xhat1p P1u P1p

% xs = transpose([phi theta psi p q r]);

xs0 = [0;10;180]*d2r;
  
xp0 = [];
   
x0 = [xs0;xp0];

Ps0 = diag([[20;20;20]*d2r].^2);
Pp0 = diag([]);
P0 = diag([diag(Ps0);diag(Pp0)]);

% Instantiate Vars
xhat1p = nan(n,n_measurements); P1p=nan(n,n,n_measurements);
xhat1u = nan(n,n_measurements); P1u=nan(n,n,n_measurements);

xhat1u(:,1)=x0;P1u(:,:,1)=P0;


%% Estimator

condP = nan(n_measurements,1);

tic
for k=1:(n_measurements-1)
    % Display
    if mod(k,n_measurements)==0
        disp(num2str(100*k/n_measurements));
    end
    
    delt = (flightData.Time(k+1)-flightData.Time(k));
    
    % Predict State
    xhat1p(:,k+1)=predict_stateparam_IN(xhat1u(:,k),Z_input(:,k),delt);
    xhat1p(angleEls,k+1) = mod(xhat1p(angleEls,k+1),2*pi);
    
    x_recent = xhat1p(:,k+1);
    % Predict Covariance
    [F] = getF_stateparam(xhat1u(:,k),Z_input(:,k),delt);
    Q = Q_Fcn(dT);
    P1p(1:n,1:n,k+1) = F*P1u(1:n,1:n,k)*F' + G*Q*G'*delt^2;
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),Z_input(:,k+1));
    R = R_Fcn(dT);
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
    
    try condDen(k) = cond((H*P1p(1:n,1:n,k+1)*H' + R));
    catch
        break
    end
    if condDen(k) > 1E6
        break
    end
    
    % Update
    xhat1u(:,k+1) = xhat1p(:,k+1) + K *(Z(:,k+1) - h_Fcn(xhat1p(:,k+1),Z_input(:,k+1)));
    xhat1u(angleEls,k+1) = mod(xhat1u(angleEls,k+1),2*pi);
    P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    x_recent = xhat1u(:,k+1);
        
    if k==39
        1;
    end
    
end
toc


% Angles
figure
subplot(3,1,1)
els = 1;
plot(flightData.Time,xhat1u(els,:)/d2r,'r')
hold on
% plot(flightData.Time,2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
% plot(flightData.Time,-2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
ylabel('\phi');

subplot(3,1,2)
els = 2;
plot(flightData.Time,xhat1u(els,:)/d2r,'r')
hold on
% plot(flightData.Time,2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
% plot(flightData.Time,-2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
ylabel('\theta');

subplot(3,1,3)
els = 3;
plot(flightData.Time,xhat1u(els,:)/d2r,'r')
hold on
% plot(flightData.Time,2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
% plot(flightData.Time,-2*sqrt(squeeze(P1u(els,els,:))/d2r),'b--');
ylabel('\psi');

xlabel('Time')

figure 
subplot(2,1,1)
plot(flightData.Time,flightData.Heading/d2r)
hold on
plot(flightData.Time,xhat1u(els,:)/d2r)
legend('Measurement','Estimate')
% xlim([518 600])
% 
% subplot(2,1,2)
% plot(flightData.Time,flightData.Speed)
% xlim([518 600])














