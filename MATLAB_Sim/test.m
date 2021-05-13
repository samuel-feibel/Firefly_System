Xk = xhat1u(:,k);

[~,Xout] = ode45(@f_cntrl_Fcn,[0 delt],[Xk;cntrl_k]');
Xkp1 = Xout(end,1:n)';