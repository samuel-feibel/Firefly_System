function Xkp1=predict_stateparam_IN(Xk,U,delt)

fdot = double(f_Fcn(0,[Xk;U]));
    
Xkp1 = Xk + delt*fdot;

end
