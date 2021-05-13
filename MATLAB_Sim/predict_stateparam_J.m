function Xkp1=predict_stateparam_J(Xk,cntrl_k,U,delt)

acc_B = U(1:3)-I_C_B_Fcn(Xk(7),Xk(8),Xk(9))'*[0;0;-9.8];

fdot = f_Fcn(0,[Xk;cntrl_k]);

fdot(4:6) = fdot(4:6)+acc_B;
fdot(10:12) = fdot(10:12)+U(4:6);

Xkp1 = Xk + delt*fdot;

end