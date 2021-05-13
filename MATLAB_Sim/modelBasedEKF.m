%% Estimate Parameters
% The goal of this script is to take in data from flight and use it to
% generate the parameters of the flight vehicle

close all;

d2r = pi/180;

try r_NED;
    
catch

%{ 
TODO:
       - Initial States and Covariances
%}

%% Constants

% Sim version for MC
% syms rho g0 u0 Theta0
% consts = [rho g0 S m u0 Theta0];

% non-sim version for MATLAB
rho = 1.225; % kg/m^3
g0 = 9.8; % m/s^2
Theta0 = 0; % rads
u0 = 15;

%% Load and Parse Flight Data
startIdx = 1792;        % This is specific to each set of flight data
addpath('DataFiles');
[flightData] = loadFlightData("DataFiles/ParamEstFlight1.txt",startIdx);

n_measurements = size(flightData.Time,1);

load('ParamVec0_individual.mat');

%% States

syms t

% States
syms N E D u v w p q r phi theta psi real
xs = transpose([N E D u v w p q r phi theta psi]);
ns = length(xs);

% Parameters
% syms Xu Xw Zu Zw MuComb MwComb MqComb ... % Pitch A
%     Xde XdT Zde ZdT MdeComb MdTComb ZdT ... % Pitch B
%     Yv Yp Yr Lv Lp Lr Nv Np Nr... % Roll A
%     Ydr Lda Ldr Nda Ndr real % Roll B
% xp = transpose([Xu Xw Zu Zw MuComb MwComb MqComb ...
%     Xde XdT Zde ZdT MdeComb MdTComb ZdT ...
%     Yv Yp Yr Lv Lp Lr Nv Np Nr...
%     Ydr Lda Ldr Nda Ndr]);
xp = [];
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs

syms de dT da dr real
cntrl = transpose([dT da de dr]);

% Dynamics

I_C_B = R_z(psi)*R_y(theta)*R_x(phi);

fs = [% Position
      I_C_B*[u+u0;v;w]
      
      % Velocity
      Xu*u + Xw*w - g0*theta;...                          % udot
      Yv*v+Yp*p-(u0-Yr)*r+g0*cos(Theta0)*phi;...          % vdot
      Zu*u + Zw*w + u0*q;...                              % wdot
      
      % Rates
      Lv*v+Lp*p+Lr*r;...                                  % pdot
      MuComb*u + MwComb*w + MqComb*q;...                  % qdot
      Nv*v+Np*p+Nr*r;...                                  % rdot
      
      % Angles
      p + q*sin(phi)*tan(theta) + r*cos(phi)*tan(theta);...   % phidot
      q*cos(phi) + -r*sin(phi);...                            % thetadot
      q*sin(phi)*sec(theta) + r*cos(phi)*sec(theta);...       % psidot
      ];

fs = fs + [[0;0;0];...                                  % Position
           Xde*de + XdT*dT;...                          % udot
           Ydr*dr;...                                   % vdot
           Zde*de + ZdT*dT;...                          % wdot
           
           Lda*da + Ldr*dr;...                          % pdot
           MdeComb*de + MdTComb*dT;...                  % qdot
           Nda*da + Ndr*dr;...                          % rdot
           [0;0;0];...                                  % Angle
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
sigmaP.accel = .5; % m/s^2
sigmaP.alpha = pi/4; % rad/s^2
Qs = diag([sigmaP.accel^2*ones(3,1);sigmaP.alpha^2*ones(3,1)]);

Gs = zeros(ns,size(Qs,1)); 
Gs(4,1) = 1; Gs(5,2) = 1; Gs(6,3) = 1;  % accel
Gs(7,4) = 1; Gs(8,5) = 1; Gs(9,6) = 1;  % rotational accel

% Parameters
Qp = [];
Gp = zeros(np,size(Gs,2));

% Combine
Q = blkdiag(Qs,Qp);
G = [Gs;Gp];

% ---- Measurement Noise ---- %

[sigmaN] = makeSigma("Combined_DATALOG");



R = diag([sigmaN.N,sigmaN.E,sigmaN.D,...
          sigmaN.Speed,...
          sigmaN.Acc.x, sigmaN.Acc.y, 3*sigmaN.Acc.z,...
          sigmaN.Gyr.x, sigmaN.Gyr.y, sigmaN.Gyr.z,...
          sigmaN.Mag.x, sigmaN.Mag.y,sigmaN.Mag.z,...
          sigmaN.Heading].^2);
        
 
R_Fcn = matlabFunction(R,'Vars',dT,'File','R_Fcn');




%% Sensor Measurement

[bias,magVec0] = makeBias("magTuning_NorthLevel.txt");


h = [N;E;D;...                                      % Position
     norm([u+u0;v;w]);...                              % Speed
     [fs(4);fs(5);fs(6)] + (I_C_B')*[0;0;-g0];...    % Specific Force
     p;q;r;...                                      % Rotation Rates
     I_C_B'*magVec0;...
     psi;...                                        % Heading
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

 Z =[r_NED;...
     flightData.Speed';...
     flightData.Acc.x';...
     flightData.Acc.y';...
     flightData.Acc.z';...
     ([flightData.Gyr.x';...
     flightData.Gyr.y';...
     flightData.Gyr.z'] - ...
     [bias.Gyr.x';...
     bias.Gyr.y';...
     bias.Gyr.z'])
     flightData.Mag.x';...
     flightData.Mag.y';...
     flightData.Mag.z';...
     flightData.Heading'...
     ];

% Control
cntrlDat = [flightData.Throttle' - 50;...
            flightData.Aileron' - 90;...
            flightData.Elevator' - 90;...
            flightData.Rudder' - 90];

end

%% Initial Conditions

clear xhat1u xhat1p P1u P1p


% xs = transpose([N E D u v w p q r phi theta psi]);

xs0 = [0;0;0;...
       0;0;0;...
       0;0;0;...
       [0;10;180]*d2r;
       ];
   
%    xp = transpose([Xu Xw Zu Zw Mu Mwd Mw Mq...
%     Xde XdT Zde ZdT Mde MdT ZdT...
%     Yv Yp Yr Lv Lp Lr Nv Np Nr...
%     Ydr Lda Ldr Nda Ndr]);

% xp0 = ParamVec0';
xp0 = [];

x0 = [xs0;xp0];

Ps0 = diag([0;0;0;...
            5;5;5;...
            .1;.1;.1;...
            [20;20;20]*d2r].^2);
Pp0 = diag(0*ones(np,1).^2);
P0 = diag([diag(Ps0);diag(Pp0)]);



%% Simulation

% [tTruth, xTruth] = ode45(@f_cntrl_Fcn,0:.05:10,[x0;zeros(4,1)]);
% xTruth = xTruth';
% 
% figure
% plot3(xTruth(2,:),xTruth(1,:),-xTruth(3,:));
% axis equal
% xlabel('E'); ylabel('N'); zlabel('D');
% 
% for i=1:length(tTruth)
%     cntrlDat(:,i) = zeros(4,1);
%     
%     Z(:,i) = h_Fcn(xTruth(1:12,i),cntrlDat(:,i))+sqrt(R_Fcn(0))*randn(14,1);
% end
% 
% n_measurements = length(tTruth);


% Instantiate Vars
xhat1p = nan(n,n_measurements); P1p=nan(n,n,n_measurements);
xhat1u = nan(n,n_measurements); P1u=nan(n,n,n_measurements);

xhat1u(:,1)=x0;P1u(:,:,1)=P0;



%% Estimator

condP = nan(n_measurements,1);

tic
for k=1:(n_measurements-1)
    delt = (flightData.Time(k+1)-flightData.Time(k));
%         delt = (tTruth(k+1)-tTruth(k));
    
    % Predict State
    xhat1p(:,k+1)=predict_stateparam(xhat1u(:,k),cntrlDat(:,k),delt,n);
    
    % Predict Covariance
    [F] = getF_stateparam(xhat1u(:,k),cntrlDat(:,k),delt);
    P1p(1:n,1:n,k+1) = F*P1u(1:n,1:n,k)*F' + 100*G*Q*G'*delt^2;
    
    condP(k) = cond(P1p(1:n,1:n,k+1));
    
    if condP(k)>1E20
        break
    end
    
    if k==91
        1;
    end
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),cntrlDat(:,k+1));
    R = R_Fcn(cntrlDat(1,k+1)+90);
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
    
    % Update
    xhat1u(:,k+1) = xhat1p(:,k+1) + K *(Z(:,k+1) - h_Fcn(xhat1p(:,k+1),cntrlDat(:,k+1)));
    P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    
end
toc

% plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u,1:3,{'N','E','D'},xTruth,{'Est','Truth'})
% 
% figure
% plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u,4:6,{'u','v','w'},xTruth,{'Est','Truth'})
% 
% figure
% plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u/d2r,10:12,{'\phi','\theta','\psi'},xTruth/d2r,{'Est','Truth'})


plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u,1:3,{'N','E','D'})

figure
plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u,4:6,{'u','v','w'})

figure
plotStates(flightData.Time(1:size(xhat1u,2)),xhat1u/d2r,10:12,{'\phi','\theta','\psi'})






