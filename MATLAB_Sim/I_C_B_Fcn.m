function I_C_B = I_C_B_Fcn(in1)
%I_C_B_FCN
%    I_C_B = I_C_B_FCN(IN1)

%    This function was generated by the Symbolic Math Toolbox version 8.5.
%    22-May-2021 20:49:16

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
t12 = -t2;
t13 = -t3;
t14 = -t4;
I_C_B = reshape([t2+t5+t13+t14,t6+t11,t7-t10,t6-t11,t3+t5+t12+t14,t8+t9,t7+t10,-t8+t9,t4+t5+t12+t13],[3,3]);
