function [F]=getF_stateparam(Xk,cntrl,delt)

F_continuous = F_jac_Fcn(Xk,cntrl);

F = expm(F_continuous*delt);

end