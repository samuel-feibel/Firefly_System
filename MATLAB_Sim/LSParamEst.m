%% Batch Least Squares Parameter Estimation
% Estimate Parameters with batch least squares methods using the states
% pulled from the Inertial Navigation System

clearvars -except xhat1u flightData

u0 = 10;

%% Find xdot state values


xhat(1:6,:) = xhat1u(1:6,:);

% Change from Quat to Euler off the bat
Euler = Quat2Euler(xhat1u(7:10,:));
xhat = [xhat;Euler];

xdot = diff(xhat,1,2);
xdot(:,end+1) = xdot(:,end);
tdiff1 = diff(flightData.Time)';
tdiff1(end+1) = tdiff1(end);
tdiff = repmat(tdiff1,size(xdot,1),1);
xdot = xdot./tdiff;

%% Subtract Equilibrium Values to form derivatives

% Derivs
delUdot = xdot(4,:);
delVdot = xdot(5,:);
delWdot = xdot(6,:);
delPhidot = xdot(7,:);
delThetadot = xdot(8,:);
delPsidot = xdot(9,:);

% States
delU = xhat(4,:);
delV = xhat(5,:);
delW = xhat(6,:);
delPhi = xhat(7,:);
delTheta = xhat(8,:);

delP = nan(1,size(xdot,2));
delQ = nan(1,size(xdot,2));
delR = nan(1,size(xdot,2));

for i=1:size(xdot,2)
    C = [1,sin(delPhi(i))*tan(delTheta(i)),cos(delPhi(i))*tan(delTheta(i));...   % phidot
         0,cos(delPhi(i)),-sin(delPhi(i));...                            % thetadot
         0,sin(delPhi(i))*sec(delTheta(i)),cos(delPhi(i))*sec(delTheta(i))];          % psidot
    
     temp = C'*[delPhidot(i);delThetadot(i);delPsidot(i)];
     delP(i)=temp(1);
     delQ(i)=temp(2);
     delR(i)=temp(3);
end

delPdot = diff(delP,1,2); delPdot(:,end+1) = delPdot(:,end); delPdot=delPdot./tdiff1;
delQdot = diff(delQ,1,2); delQdot(:,end+1) = delQdot(:,end); delQdot=delQdot./tdiff1;
delRdot = diff(delR,1,2); delRdot(:,end+1) = delRdot(:,end); delRdot=delRdot./tdiff1;


% Controls
delElevator = -(flightData.Elevator' - 90); 
delThrottle = -(flightData.Throttle' - 80); 
delAileron = -(flightData.Aileron' - 94);
delRudder = -(flightData.Rudder' - 90); 


%% Find Parameter Estimates for each Row

% delUdot Stuff
y = delUdot + 9.8*delTheta;
X = [delU;delW;delElevator;delThrottle];

ParamVec = y*X'/(X*X');

Xu = ParamVec(1); Xw = ParamVec(2); Xde = ParamVec(3); XdT = ParamVec(4);

% delWdot Stuff
y = delWdot - u0*delQ;
X = [delU;delW;delElevator;delThrottle];

ParamVec = y*X'/(X*X');

Zu = ParamVec(1); Zw = ParamVec(2); Zde = ParamVec(3); ZdT = ParamVec(4);

% delQdot Stuff
y = delQdot;
X = [delU;delW;delQ;delElevator;delThrottle];

ParamVec = y*X'/(X*X');

MuComb = ParamVec(1); MwComb = ParamVec(2); MqComb = ParamVec(3); MdeComb = ParamVec(4); MdTComb = ParamVec(5);

% delVdot Stuff
y = delVdot - 9.8*delPhi;
X = [delV;delP;delR;delRudder];

ParamVec = y*X'/(X*X');

Yv = ParamVec(1); Yp = ParamVec(2); Yr = u0 + ParamVec(3); Ydr = ParamVec(4);

% delPdot Stuff
y = delPdot;
X = [delV;delP;delR;delAileron;delRudder];

ParamVec = y*X'/(X*X');

Lv = ParamVec(1); Lp = ParamVec(2); Lr = ParamVec(3); Lda = ParamVec(4); Ldr = ParamVec(5);

% delRdot Stuff
y = delRdot;
X = [delV;delP;delR;delAileron;delRudder];

ParamVec = y*X'/(X*X');

Nv = ParamVec(1); Np = ParamVec(2); Nr = ParamVec(3); Nda = ParamVec(4); Ndr = ParamVec(5);

%% Combine for output

ParamVec0 = [Xu Xw Zu Zw MuComb MwComb MqComb ...
             Xde XdT Zde ZdT MdeComb MdTComb ZdT ...
             Yv Yp Yr Lv Lp Lr Nv Np Nr...
             Ydr Lda Ldr Nda Ndr];


% save('ParamVec0','ParamVec0');
save('ParamVec0_individual','Xu', 'Xw', 'Zu', 'Zw', 'MuComb', 'MwComb', 'MqComb', ...
             'Xde', 'XdT', 'Zde', 'ZdT', 'MdeComb', 'MdTComb', 'ZdT', ...
             'Yv', 'Yp', 'Yr', 'Lv', 'Lp', 'Lr', 'Nv', 'Np', 'Nr',...
             'Ydr', 'Lda', 'Ldr', 'Nda', 'Ndr','u0');


