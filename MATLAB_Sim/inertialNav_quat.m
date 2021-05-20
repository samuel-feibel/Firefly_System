%% Inertial Nav + GPS
% Finds attitude and position from sensors only, no model

close all;
rng(12);
d2r = pi/180;

try r_NED;
    
catch

%{ 
TODO:
    % Figure out velocity behavior
%}

%% Constants

% non-sim version for MATLAB
rho = 1.225; % kg/m^3
g0 = 9.8; % m/s^2
u0 = 0;

%% Load and Parse Flight Data
startIdx = 1;        % This is specific to each set of flight data

addpath('DataFiles');
[flightData] = loadFlightData("DataFiles/compassTuning_XY.TXT",startIdx);

n_measurements = size(flightData.Time,1);

%% States

syms t

% States
syms N E D u v w q1 q2 q3 q4  real
xs = transpose([N E D u v w q1 q2 q3 q4]);
ns = length(xs);

xp = transpose([]);
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs

syms X Y Z p q r real
cntrl = transpose([X Y Z p q r]);

% Dynamics

I_C_B = [q1^2-q2^2-q3^2+q4^2, 2*(q1*q2 + q3*q4), 2*(q1*q3 - q2*q4);...
         2*(q2*q1-q3*q4), -q1^2 + q2^2 - q3^2 + q4^2,2*(q1*q4 + q2*q3);...
         2*(q3*q1+q2*q4),2*(q2*q3 -q1*q4),-q1^2 - q2^2 + q3^2 + q4^2]';
     
qVec = [q1 q2 q3 q4]';

matlabFunction(I_C_B,'Vars',{qVec},'File','I_C_B_Fcn');


fs = [
    % Position
    I_C_B*[u+u0;v;w];...

    % Velocity
    0;0;0;...
    
    % Angles
    0;0;0;0 ...
    ];

fs = fs + [
            % Position
            0;0;0;...
            
            % Velocity
            ([X;Y;Z;] - I_C_B'*[0;0;-9.8]);...

            % Angles
            1/2*qXi([q1,q2,q3,q4]')*[p,q,r]';
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

[sigmaN] = makeSigma("Combined_DATALOG.TXT");


% ---- Process Noise ---- %

% States
Qs = diag([sigmaN.Acc.x,sigmaN.Acc.y,sigmaN.Acc.z,...
           sigmaN.Gyr.x,sigmaN.Gyr.y,sigmaN.Gyr.z].^2);

Gs = zeros(ns,size(Qs,1)); 
Gs(4,1) = 1; Gs(5,2) = 1; Gs(6,3) = 1;  % accel
Gs(7,4) = 1; Gs(8,5) = 1; Gs(9,6) = 1;  % angular accel

% Parameters
Qp = [];
Gp = zeros(np,size(Gs,2));

% Combine
Q = blkdiag(Qs,Qp);
G = [Gs;Gp];

syms dT
Q_Fcn = matlabFunction(Q,'Vars',dT,'File','Q_Fcn');


% ---- Measurement Noise ---- %

R = diag([sigmaN.N,sigmaN.E,sigmaN.D,...
    sigmaN.Speed,...
    [sigmaN.Mag.x, sigmaN.Mag.y,sigmaN.Mag.z],...
%     10*sigmaN.Heading...
    ].^2);


 
R_Fcn = matlabFunction(R,'Vars',dT,'File','R_Fcn');

%% Sensor Measurement

[bias,magVec0] = makeBias("magTuning_NorthLevelnew.txt");
[bias,magVec0] = makeMagBias(bias);

v_I = I_C_B*[u+u0;v;w];
matlabFunction(atan2(v_I(2),v_I(1)),'Vars',{x,cntrl},'File','heading_Fcn');

magVec = I_C_B'*(magVec0-[bias.Mag.x;bias.Mag.y;bias.Mag.z]);
matlabFunction(magVec,'Vars',{x,cntrl},'File','magVec_Fcn');

h = [N;E;D;...
     norm([u+u0;v;w]);...
     magVec;...
%      atan2(v_I(2),v_I(1));...
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

Z_input = [ % Acc
           flightData.Acc.x';...
           flightData.Acc.y';...
           flightData.Acc.z';...
           % Gyr
           ([flightData.Gyr.x';...
           flightData.Gyr.y';...
           flightData.Gyr.z'] - ...
           [bias.Gyr.x';...
           bias.Gyr.y';...
           bias.Gyr.z'])
           ];

 Z =[r_NED;...
     flightData.Speed';...
     ([flightData.Mag.x';...
     flightData.Mag.y';...
     flightData.Mag.z']...
     -[bias.Mag.x;bias.Mag.y;bias.Mag.z]);...
%      setAngle2Range(flightData.Heading')...
     ];

end

simOn = 0;


%% Initial Conditions

dT = 0;

clear xhat1u xhat1p P1u P1p

% xs = transpose([N E D u v w phi theta psi]);

xs0 = [0;0;0;...
       0;0;0;...
       Euler2Quat([0;0;0]*d2r)];
  
xp0 = [];
   
x0 = [xs0;xp0];

Ps0 = diag([0;0;0;...
            5;5;5;...
            Euler2Quat([20;20;20]*d2r)].^2);
Pp0 = diag([]);
P0 = diag([diag(Ps0);diag(Pp0)]);



%% Simulation Data
if simOn
cntrl  = [0;0;0;0;0;0];
[tTrue,xTrue] = ode45(@f_cntrl_Fcn,[0:.001:10],[x0;cntrl]);
xTrue =xTrue';

n_measurements = length(tTrue);

clear Z Z_input
for i=1:n_measurements
    Z(:,i) = h_Fcn(xTrue(1:10,i),xTrue(11:16,i));
    Z_input(:,i) = cntrl;
end

end
%% Initial Conditions

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
    
    if simOn
        delt = 0.001;
    else
        delt = (flightData.Time(k+1)-flightData.Time(k));
    end
    
    % Predict State
    xhat1p(:,k+1)=predict_stateparam_IN(xhat1u(:,k),Z_input(:,k),delt);
    
    % Normalize
    xhat1p(7:10,k+1)=xhat1p(7:10,k+1)/norm(xhat1p(7:10,k+1));

    % Predict Covariance
    [F] = getF_stateparam(xhat1u(:,k),Z_input(:,k),delt);
    Q = Q_Fcn(dT);
    P1p(1:n,1:n,k+1) = F*P1u(1:n,1:n,k)*F' + G*Q*G'*delt^2;
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),Z_input(:,k+1));
    R = R_Fcn(dT);
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
   
    % Update
    xhat1u(:,k+1) = xhat1p(:,k+1) + K *(Z(:,k+1) - h_Fcn(xhat1p(:,k+1),Z_input(:,k+1)));
    P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    
    % Normalize
    xhat1u(7:10,k+1)=xhat1u(7:10,k+1)/norm(xhat1u(7:10,k+1));
    
    [ex,ey,ez] = Quat2base(xhat1u(7:10,k+1));
    
    
end
toc

if simOn
    
    plotStates(tTrue,xhat1u,1:3,{'N','E','D'},xTrue,{'Sim','True'})
    
    figure
    plotStates(tTrue,xhat1u,4:6,{'u','v','w'},xTrue,{'Sim','True'})
    
    Euler1u = Quat2Euler(xhat1u(7:10,:));
    Euler1s = Quat2Euler(xTrue(7:10,:));
    
    figure
    plotStates(tTrue,Euler1u/d2r,1:3,{'\phi','\theta','\psi'},Euler1s/d2r,{'Sim','True'})
    
    
    
else
    
    % Kalman Smoother
    xhat1s(:,n_measurements)=xhat1u(:,k+1);P1s(1:n,1:n,n_measurements)=P1u(1:n,1:n,k+1);
    for k=(n_measurements-1):-1:1
        [F] = getF_stateparam(xhat1u(:,k+1),Z_input(:,k+1),delt);
        Ks = P1u(1:n,1:n,k)*F'/(P1p(1:n,1:n,k+1));
        xhat1s(:,k)=xhat1u(:,k)+Ks*(xhat1s(:,k+1)-xhat1p(:,k+1));
        P1s(1:n,1:n,k)=P1u(1:n,1:n,k)-Ks*(P1p(1:n,1:n,k+1)-P1s(1:n,1:n,k+1));
        
        % Normalize
        xhat1s(7:10,k+1)=xhat1s(7:10,k+1)/norm(xhat1s(7:10,k+1));
    end
    
    xhat1s(:,1:4)=xhat1u(:,1:4);    % Janky Fix
    
    plotStates(flightData.Time,xhat1u,1:3,{'N','E','D'})
    
    figure
    plotStates(flightData.Time,xhat1u+[0;0;0;u0;0;0;0;0;0;0],4:6,{'u+u0','v','w'})
    
    Euler1u = Quat2Euler(xhat1u(7:10,:));
    Euler1s = Quat2Euler(xhat1s(7:10,:));
    
    figure
    plotStates(flightData.Time,Euler1u/d2r,1:3,{'\phi','\theta','\psi'},Euler1s/d2r,{'Forward','Backward'});
    
    h_save = NaN(1,length(flightData.Time));
    for i=1:length(flightData.Time)
        h_save(1,i) = heading_Fcn(xhat1u(:,i),zeros(6,1));
    end
    
    figure
    plot(flightData.Time,h_save(1,:));
    hold on
    plot(flightData.Time,setAngle2Range(flightData.Heading'));
    legend('h','z')
    grid on
    ylabel('\psi [rad]')
    xlabel('Time [s]')
    
    [ex,ey,ez] = Quat2base(xhat1u(7:10,:));
    
    h_save = NaN(3,length(flightData.Time));
    for i=1:length(flightData.Time)
        h_temp = magVec_Fcn(xhat1u(:,i),zeros(6,1));
        h_save(:,i) = h_temp(1:3);
    end
    
    
    figure
    plotStates(flightData.Time,h_save,1:3,{'X','Y','Z'},[flightData.Mag.x';flightData.Mag.y';flightData.Mag.z']-[bias.Mag.x;bias.Mag.y;bias.Mag.z],{'h','z'});
    
    
    
    
end



% +37.87









