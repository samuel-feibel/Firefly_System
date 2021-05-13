function Xkp1=predict_stateparam(Xk,cntrl_k,delt,n)

Xkp1 = Xk + delt*f_Fcn(0,[Xk;cntrl_k]);

% [~,Xout] = ode45(@f_cntrl_Fcn,[0 delt],[Xk;cntrl_k]);
% Xkp1 = Xout(end,1:n)';

end