function [F]=getF_stateparam_IN(Xk,cntrl,delt)

F_continuous = F_jac_Fcn(Xk,cntrl);

F = expm(F_continuous*delt);

end