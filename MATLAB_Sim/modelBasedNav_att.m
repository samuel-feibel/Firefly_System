%% Attitude + Acceleration
% Finds atti/tude and position from sensors only, no model
% This is the most recent working model

close all; clear all;
rng(2);
d2r = pi/180;

simOn = 0;

%% Constants

% non-sim version for MATLAB
rho = 1.225; % kg/m^3
g0 = 9.8; % m/s^2
u0 = 0;

%% States

syms t

% States
syms q1 q2 q3 q4 N E D u v w real
xs = transpose([q1 q2 q3 q4 N E D u v w]);
ns = length(xs);

xp = transpose([]);
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs
syms p q r real
cntrl = transpose([p q r]);

% Noise Inputs
syms aNn aEn aDn pn qn rn
noise = transpose([aNn aEn aDn pn qn rn]);

% Dynamics

I_C_B = [q1^2-q2^2-q3^2+q4^2, 2*(q1*q2 + q3*q4), 2*(q1*q3 - q2*q4);...
         2*(q2*q1-q3*q4), -q1^2 + q2^2 - q3^2 + q4^2,2*(q1*q4 + q2*q3);...
         2*(q3*q1+q2*q4),2*(q2*q3 -q1*q4),-q1^2 - q2^2 + q3^2 + q4^2]';
     
qVec = [q1 q2 q3 q4]';

matlabFunction(I_C_B,'Vars',{qVec},'File','I_C_B_Fcn');

% Dynamics
fs = [
    % Angles
    0;0;0;0; ...
    % NED
    I_C_B*[u;v;w];...
    % Velocity
    (-cross([p;q;r;],[u;v;w]));...
    ];

% Inputs
fs = fs + [
            % Angles
            1/2*qXi([q1,q2,q3,q4]')*[p,q,r]';...
            % NED
            0;0;0;...
            % Velocity
            0;0;0;...
            ];

% Noise
fs_true = fs + [
            % Angles
            1/2*qXi([q1,q2,q3,q4]')*[pn,qn,rn]';...
            % NED
            0;0;0;...
            % Velocity
            I_C_B*[aNn;aEn;aDn];...
            ];

fp = zeros(np,1);

f = [fs;fp];
f_true = [fs_true;fp];


% Continuous time diff eq of motion
matlabFunction(f,'Vars',{x,cntrl},'File','f_Fcn');
matlabFunction(f_true,'Vars',{x,cntrl,noise},'File','f_true_Fcn');

F = jacobian(f,x);
syms delt;
Phi = eye(n) + F*delt;

matlabFunction(Phi,'Vars',{delt,x,cntrl},'File','Phi_Fcn');

%% Noise

% ---- Process Noise ---- %

% States
Qs = diag([...
            .01,.01,.01...
            0.0189845388442364, 0.020660226476864607, 0.02769334420437668,...
            ].^2);
Gs = jacobian(f_true,noise);


% Parameters
Qp = [];
Gp = zeros(np,size(Gs,2));

% Combine
Q = blkdiag(Qs,Qp);
G = [Gs;Gp];
matlabFunction(G,'Vars',{x},'File','G_jac_Fcn');

syms dT
matlabFunction(Q,'Vars',dT,'File','Q_Fcn');


% ---- Measurement Noise ---- %

R = diag([...
            0.7356117692017315, 0.6273443875505387, 0.7582585400442549,...
            0.06622349896195277, 0.08050395576102345, 0.053307049839142584,...
            1,1,1,...
            ].^2);

%% Sensor Measurement

syms('magVec0Sym',[3,1]);
magVec0 = [-10.732501411437989, 13.064998292922974, 35.80500106811523]';
magVec = I_C_B'*(magVec0Sym);
syms('gravVec0Sym',[3,1]);
gravVec0 = [0.0775028327293694, -0.03650009836070239, -9.845733795166016]';
gravVec = I_C_B'*(gravVec0Sym);

h = [magVec;...
     gravVec;...
     N;E;D;...
     ];
 % Full measurement
matlabFunction(h,'Vars',{x,magVec0Sym,gravVec0Sym},'File','h_Fcn');

% Jacobian
H = jacobian(h,x);
matlabFunction(H,'Vars',{x,magVec0Sym,gravVec0Sym},'File','H_jac_Fcn');


%% Convert to C
% ccode(R,'File','ccodeFiles/modelBasedAtt/R.c');
% ccode(Q,'File','ccodeFiles/modelBasedAtt/Q.c');
% ccode(H,'File','ccodeFiles/modelBasedAtt/H.c');
% ccode(G,'File','ccodeFiles/modelBasedAtt/G.c');
% ccode(Phi,'File','ccodeFiles/modelBasedAtt/Phi.c');
% ccode(f,'File','ccodeFiles/modelBasedAtt/ff.c');
% ccode(h,'File','ccodeFiles/modelBasedAtt/hh.c');


%% Initial Conditions

clear xhat1u xhat1p P1u P1p

[q0_est] = Euler2Quat([0;0;0]*d2r);
xs0 = [q0_est;...
       [0;0;0];...
       [0;0;0];...
       ];

  
xp0 = [];
   
x0 = [xs0;xp0];

Ps0 = diag([0.01*[1;1;1;1];...
            [0;0;0];...
            [0;0;0];...
            ].^2);
Pp0 = diag([]);
P0 = diag([diag(Ps0);diag(Pp0)]);

nInput = length(cntrl);
nNoise = length(noise);
nM = size(h,1);
%% Initial Conditions
if ~simOn
    flightData = loadFlightData(fullfile('DataFiles','20211027_stationary.txt'));
    n_measurements = length(flightData.Time);

    Z(1:3,:) = flightData.Mag';
    Z(4:6,:) = flightData.Acc';
    Z(7:9,:) = zeros(3,n_measurements);
    uInput = flightData.Gyr';
else
    n_measurements = 100;
    delt = 1;
    xhat_true = nan(n,n_measurements);
    uInput = nan(nInput,n_measurements);
    Z = nan(nM,n_measurements); Z_true = nan(nM,n_measurements);
    [q0_true] = Euler2Quat([0;0;0]*d2r);
    xhat_true(:,1) = [q0_true;...
       [0;0;0];...
       [0;0;0];...
       ];
end


% Instantiate Vars
xhat1p = nan(n,n_measurements); P1p=nan(n,n,n_measurements);
xhat1u = nan(n,n_measurements); P1u=nan(n,n,n_measurements);



xhat1u(:,1)=x0;P1u(:,:,1)=P0;



%% Estimator

tic
for k=1:(n_measurements-1)

    % Display
    if mod(k,n_measurements)==0
        disp(num2str(100*k/n_measurements));
    end

    % Calculate Truth
    if simOn
        uInput(:,k) = [0;10;5]*d2r;
        noise_true = sqrt(Q)*randn(nNoise,1);
        xhat_true(:,k+1) = xhat_true(:,k) + delt*f_true_Fcn(xhat_true(:,k),uInput(:,k),noise_true);
        xhat_true(1:4,k+1)=xhat_true(1:4,k+1)/norm(xhat_true(1:4,k+1));
        Z_true(:,k+1) =  h_Fcn(xhat_true(:,k+1),magVec0);
        Z(:,k+1) = Z_true(:,k+1)  + sqrt(R)*randn(nM,1);
    else
        if k==1
            delt = flightData.Time(2)-flightData.Time(1);
        else
            delt = flightData.Time(k)-flightData.Time(k-1);
        end
    end

    
    % Predict State
    xhat1p(:,k+1) = xhat1u(:,k) + delt*f_Fcn(xhat1u(:,k),uInput(:,k));
    
    % Normalize
    xhat1p(1:4,k+1)=xhat1p(1:4,k+1)/norm(xhat1p(1:4,k+1));

    % Predict Covariance
    Phi = Phi_Fcn(delt,xhat1u(:,k),uInput(:,k));
    G = G_jac_Fcn(xhat1u(:,k));
    P1p(1:n,1:n,k+1) = Phi*P1u(1:n,1:n,k)*Phi' + G*Q*G'*delt^2;
    
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),magVec0,gravVec0);
    
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
    
    % Predicted Measurement
    h_current = h_Fcn(xhat1p(:,k+1),magVec0,gravVec0);
    hSave(:,k) = h_current;
    
    % Current Measurement
    z_current = Z(:,k+1);
    
    res_current = z_current-h_current;
    
    % Update
    xhat1u(:,k+1) = xhat1p(:,k+1) + K *res_current;
    P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    
    % Normalize
    xhat1u(1:4,k+1)=xhat1u(1:4,k+1)/norm(xhat1u(1:4,k+1));
    
%     [ex,ey,ez] = Quat2base(xhat1u(1:4,k+1));
    [Euler_est(:,k)] = Quat2Euler(xhat1u(1:4,k+1));
    if simOn
        [Euler_true(:,k)] = Quat2Euler(xhat_true(1:4,k+1));
    end

end
toc

%% Plots

if ~simOn
    time = flightData.Time;
    figure
    plotMult(time,Euler_est,[],'Euler')
    xlabel('Time');

    figure
    plotMult(time,hSave(1:3,:),Z(1:3,2:end),'Mag')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(5:7,:),[],'NED')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(8:10,:),[],'Vel')
    xlabel('Time');




else
    time = delt*(0:(n_measurements-1));

    figure
    plotMult(time,Euler_est,Euler_true,'Euler')
    xlabel('Time');

    figure
    plotMult(time,hSave(1:3,:),Z(1:3,2:end),'Mag')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(5:7,:),xhat_true(5:7,:),'NED')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(8:10,:),xhat_true(8:10,:),'Vel')
    xlabel('Time');
end

function plotMult(x,y1,y2,TITLE)
if length(x) > size(y1,2)
    x = x(2:end);
end
nr = size(y1,1);
for i = 1:size(y1,1)
    subplot(nr,1,i)
    plot(x,y1(i,:),'-')
    if ~isempty(y2)
        hold on
        plot(x,y2(i,:),'--')
    end
    if (i==1); title(TITLE); end
end
if ~isempty(y2)
    legend('Est','True')
end

end
