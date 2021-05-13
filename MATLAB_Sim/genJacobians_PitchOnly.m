%% RC Aircraft Dynamics - Pitch Only

% Constants
syms rho g0 S m u0 Theta0

% States
ns = 4;
syms u w ud wd q theta
xs = [u w ud wd q theta];

% Parameters
np = 15;
syms Xu Xw Zu Zw Mu Mwd Mw Mq ... % Pitch A
    Xde Xdt Zde Zdt Mde Mdt Zdt  % Pitch B
xp = [Xu Xw Zu Zw Mu Mwd Mw Mq...
      Xde Xdt Zde Zdt Mde Mdt Zdt];

% Dynamics
fs = [Xu*u + Xw*w - g0*theta;...
      Zu*u + Zw*w + u0*q;...
      0;...
      0;...
       (Mu+Mwd*Zu)*u + (Mw+Mwd*Zw)*w + (Mq+Mwd*u0)*q;...
       q];
  
fp = zeros(np,1);

fout = [fs;fp];

x = [xs xp];

F = jacobian(fout,x);

% Measurement

h = [ud+g0*sin(theta);...
     wd-g0*cos(theta);...
     q];
 
 H = jacobian(h,x);
 
 
     


