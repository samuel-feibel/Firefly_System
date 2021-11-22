%% Attitude + Acceleration
% Finds atti/tude and position from sensors only, no model
% This is the most recent working model

close all; clearvars -except flightData
rng(2);
d2r = pi/180;

simOn = 1;

%% Constants

% non-sim version for MATLAB
rho = 1.225; % kg/m^3
g0 = 9.8; % m/s^2
u0 = 0;

%% States

syms t

% States
syms q1 q2 q3 q4 N E D vN vE vD real
xs = transpose([q1 q2 q3 q4 N E D vN vE vD]);
ns = length(xs);

syms mag_bias_x mag_bias_y mag_bias_z
xp = transpose([mag_bias_x mag_bias_y mag_bias_z]);
np = length(xp);

x = [xs;xp];
n = ns+np;

% Control Inputs
syms p q r fx fy fz real
cntrl = transpose([p q r fx fy fz]);

% Noise Inputs
syms pn qn rn axn ayn azn 
noise = transpose([pn qn rn axn ayn azn]);

% Dynamics

I_C_B = [q1^2-q2^2-q3^2+q4^2, 2*(q1*q2 + q3*q4), 2*(q1*q3 - q2*q4);...
         2*(q2*q1-q3*q4), -q1^2 + q2^2 - q3^2 + q4^2,2*(q1*q4 + q2*q3);...
         2*(q3*q1+q2*q4),2*(q2*q3 -q1*q4),-q1^2 - q2^2 + q3^2 + q4^2]';
     
qVec = [q1 q2 q3 q4]';

matlabFunction(I_C_B,'Vars',{qVec},'File','I_C_B_Fcn');

syms('gravVec0Sym',[3,1]);
gravVec = I_C_B'*(gravVec0Sym);

% Dynamics
fs = [
    % Angles
    0;0;0;0; ...
    % NED
    [vN;vE;vD];...
    % Velocity
    [0;0;0];...
    ];

% Inputs
fs = fs + [
            % Angles
            1/2*qXi([q1,q2,q3,q4]')*[p,q,r]';...
            % NED
            0;0;0;...
            % Velocity
            (I_C_B*[fx;fy;fz]-gravVec0Sym);...
            ];

% Noise
fs_true = fs + [
            % Angles
            1/2*qXi([q1,q2,q3,q4]')*[pn,qn,rn]';...
            % NED
            0;0;0;...
            % Velocity
            I_C_B*[axn; ayn; azn];...
            ];

fp = zeros(np,1);

f = [fs;fp];
f_true = [fs_true;fp];


% Continuous time diff eq of motion
matlabFunction(f,'Vars',{x,cntrl,gravVec0Sym},'File','f_Fcn');
matlabFunction(f_true,'Vars',{x,cntrl,noise,gravVec0Sym},'File','f_true_Fcn');

F = jacobian(f,x);
syms delt;
Phi = eye(n) + F*delt;

matlabFunction(Phi,'Vars',{delt,x,cntrl,gravVec0Sym},'File','Phi_Fcn');

%% Noise

% ---- Process Noise ---- %

% States
Qs = diag([...
            1*[0.0189845388442364, 0.020660226476864607, 0.02769334420437668],...   % gyro
            1*[0.06622349896195277, 0.08050395576102345, 0.053307049839142584],...  % accel
            ].^2);
Gs = jacobian(fs_true,noise);


% Parameters
Qp = diag([...
           0*[1,1,1]...   % mag bias
            ]);
Gp = eye(np);

% Combine
Q = blkdiag(Qs,Qp);
G = blkdiag(Gs,Gp);
matlabFunction(G,'Vars',{x},'File','G_jac_Fcn');

syms dT
matlabFunction(Q,'Vars',dT,'File','Q_Fcn');


% ---- Measurement Noise ---- %

R = diag([...
            (1*[0.7356117692017315, 0.6273443875505387, 0.7582585400442549]),...   % mag
            1,1,5,...   % GPS NED
            .1,...      % baro alt
            .05,.05,.5,...
            ].^2);

%% Sensor Measurement

syms('magVec0Sym',[3,1]);
magVec = I_C_B'*(magVec0Sym);


h = [(magVec-[mag_bias_x;mag_bias_y;mag_bias_z]);...
     N;E;D;...
     D;...
     [vN;vE;vD];...
     ];
 % Full measurement
matlabFunction(h,'Vars',{x,magVec0Sym},'File','h_Fcn');

% Jacobian
H = jacobian(h,x);
matlabFunction(H,'Vars',{x,magVec0Sym},'File','H_jac_Fcn');


%% Convert to C
ccode(H,'File','ccodeFiles/INS/H.c');
ccode(G,'File','ccodeFiles/INS/G.c');
ccode(Phi,'File','ccodeFiles/INS/Phi.c');
ccode(f,'File','ccodeFiles/INS/ff.c');
ccode(h,'File','ccodeFiles/INS/hh.c');


%% Initial Conditions

clear xhat1u xhat1p P1u P1p

[q0_est] = Euler2Quat([0;0;0]*d2r);
xs0 = [q0_est;...
       [0;0;0];...
       [0;0;0];...
       ];

  
xp0 =  [-18.37500286102295; -15.15000057220459; 2.9250011444091797];
   
x0 = [xs0;xp0];

Ps0 = diag([0.5*[1;1;1;1];...
            [0;0;0];...
            [0;0;0];...
            ].^2);
Pp0 = diag([10*[1,1,1]].^2);
P0 = diag([diag(Ps0);diag(Pp0)]);

nInput = length(cntrl);
nNoise = length(noise);
nM = size(h,1);
%% Initial Conditions

gravVec0 = [0;0;-9.8067];
magVec0 = [19814.6,-5046.4,47408.0]'*1E-3;

if ~simOn
    if ~exist('flightData','var')
        flightData = loadFlightData(fullfile('DataFiles','20211115_runningWest.txt'),100);
    end
    n_measurements = length(flightData.Time);
    
%     stationaryTime = 5; %s
%     [~,indST] = min(abs(flightData.Time-stationaryTime));
    indST = 1000;
%     gravVec0 = mean(flightData.IMU.Acc(1:indST,:))';
%     magVec0 = mean(flightData.IMU.Mag(1:indST,:))';


    Z(1:3,:) = flightData.IMU.Mag';
    Z(4:6,:) = flightData.GPS.NED'-flightData.GPS.NED(1,:)';
    Z(7,:) = flightData.baro.Alt';
    Z(8:10,:) = flightData.GPS.vNED';
    uInput(1:3,:) = flightData.IMU.Gyr';
    uInput(4:6,:) = flightData.IMU.Acc';
else
    n_measurements = 100;
    delt = 1;
    xhat_true = nan(n,n_measurements);
    uInput = nan(nInput,n_measurements);
    uInput_true = nan(nInput,n_measurements);
    Z = nan(nM,n_measurements); Z_true = nan(nM,n_measurements);
    [q0_true] = Euler2Quat([15;15;15]*d2r);
    xhat_true(:,1) = [q0_true;...
       [0;0;0];...
       [0;0;0];...
       [-18.37500286102295; -15.15000057220459; 2.9250011444091797];...
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
        I_C_B_true = I_C_B_Fcn(xhat_true(1:4,k));
        uInput_true(:,k) = [[0;0;5]*d2r;(I_C_B_true'*[0;1;0]+I_C_B_true'*gravVec0)];
        uInput(:,k) = uInput_true(:,k) + sqrt(Q(1:nNoise,1:nNoise))*randn(nNoise,1);
        xhat_true(:,k+1) = xhat_true(:,k) + delt*f_Fcn(xhat_true(:,k),uInput_true(:,k),gravVec0);
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
    xhat1p(:,k+1) = xhat1u(:,k) + delt*f_Fcn(xhat1u(:,k),uInput(:,k),gravVec0);
    
    % Normalize
    xhat1p(1:4,k+1)=xhat1p(1:4,k+1)/norm(xhat1p(1:4,k+1));

    % Predict Covariance
    Phi = Phi_Fcn(delt,xhat1u(:,k),uInput(:,k),gravVec0);
    G = G_jac_Fcn(xhat1u(:,k));
    P1p(1:n,1:n,k+1) = Phi*P1u(1:n,1:n,k)*Phi' + G*Q*G'*delt^2;
    
    
    % Kalman Gain
    H = H_jac_Fcn(xhat1p(:,k+1),magVec0);
    
    K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
    
    % Predicted Measurement
    h_current = h_Fcn(xhat1p(:,k+1),magVec0);
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
    plotMult(time,Euler_est/d2r,[],[],'Euler')
    xlabel('Time');

    figure
    plotMult(time,hSave(1:3,:),Z(1:3,2:end),[],'Mag')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(5:7,:),[],P1u(5:7,5:7,:),'NED')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(8:10,:),[],P1u(8:10,8:10,:),'Vel')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(11:13,:),[],P1u(11:13,11:13,:),'Mag Bias')
    xlabel('Time');

    figure
    plotMult(time,Z(4:6,:),[],[],'GPS NED')
    xlabel('Time');

    figure
    plot(time,Z(7,:)); title('Baro')
    xlabel('Time');

    for i=1:size(xhat1u,2)
        I_C_B_curr = I_C_B_Fcn(xhat1u(1:4,i));
        acc(:,i) = I_C_B_curr*flightData.IMU.Acc(i,:)';
    end

    figure
    plotMult(time,acc,[],[],'Acc')
    xlabel('Time');

    figure
    plotMult(time,Z(8:10,:),[],[],'VM')

    autoArrangeFigures(3,3,1);


else
    time = delt*(0:(n_measurements-1));

    figure
    plotMult(time,Euler_est/d2r,Euler_true/d2r,[],'Euler')
    xlabel('Time');

    figure
    plotMult(time,hSave(1:3,:),Z(1:3,2:end),[],'Mag')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(5:7,:),xhat_true(5:7,:),P1u(5:7,5:7,:),'NED')
    xlabel('Time');

    figure
    plotMult(time,xhat1u(8:10,:),xhat_true(8:10,:),P1u(8:10,8:10,:),'Vel')
    xlabel('Time');


end

function plotMult(x,y1,y2,P1,TITLE)
if length(x) > size(y1,2)
    x = x(2:end);
end
nr = size(y1,1);
for i = 1:size(y1,1)
    subplot(nr,1,i); hold on;
    % State
    plot(x,y1(i,:),'-')
    if ~isempty(y2)
        hold on
        plot(x,y2(i,:),'--')
    end
    % Cov
    if ~isempty(P1)
    plot(x,y1(i,:)'+2*sqrt(squeeze(P1(i,i,:))),'-','Color',[0.8500 0.3250 0.0980])
    plot(x,y1(i,:)'-2*sqrt(squeeze(P1(i,i,:))),'-','Color',[0.8500 0.3250 0.0980])
    end
    if (i==1); title(TITLE); end
    grid on;
end
if ~isempty(y2)
    legend('Est','True')
end
set(gcf,'color','w');
end
