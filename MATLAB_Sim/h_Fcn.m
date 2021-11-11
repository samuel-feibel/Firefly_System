function h = h_Fcn(in1,in2)
%h_Fcn
%    H = h_Fcn(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 9.0.
%    10-Nov-2021 20:11:25

D = in1(7,:);
E = in1(6,:);
N = in1(5,:);
magVec0Sym1 = in2(1,:);
magVec0Sym2 = in2(2,:);
magVec0Sym3 = in2(3,:);
q1 = in1(1,:);
q2 = in1(2,:);
q3 = in1(3,:);
q4 = in1(4,:);
t2 = q1.^2;
t3 = q2.^2;
t4 = q3.^2;
t5 = q4.^2;
t6 = q1.*q2.*2.0;
t7 = q1.*q3.*2.0;
t8 = q1.*q4.*2.0;
t9 = q2.*q3.*2.0;
t10 = q2.*q4.*2.0;
t11 = q3.*q4.*2.0;
t12 = -t3;
t13 = -t4;
t14 = -t5;
h = [magVec0Sym2.*(t6+t11)+magVec0Sym3.*(t7-t10)+magVec0Sym1.*(t2+t5+t12+t13);magVec0Sym3.*(t8+t9)+magVec0Sym1.*(t6-t11)-magVec0Sym2.*(t2+t4+t12+t14);magVec0Sym1.*(t7+t10)-magVec0Sym2.*(t8-t9)-magVec0Sym3.*(t2+t3+t13+t14);N;E;D;D];
