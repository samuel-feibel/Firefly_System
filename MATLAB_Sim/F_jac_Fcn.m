function F = F_jac_Fcn(in1,in2)
%F_jac_Fcn
%    F = F_jac_Fcn(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 9.0.
%    21-Oct-2021 11:00:17

p = in2(1,:);
q = in2(2,:);
r = in2(3,:);
t2 = p./2.0;
t3 = q./2.0;
t4 = r./2.0;
t5 = -t2;
t6 = -t3;
t7 = -t4;
F = reshape([0.0,t7,t3,t5,t4,0.0,t5,t6,t6,t2,0.0,t7,t2,t3,t4,0.0],[4,4]);
