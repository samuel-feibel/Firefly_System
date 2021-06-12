function f_cntrl = f_cntrl_Fcn(t,in2)
%F_CNTRL_FCN
%    F_CNTRL = F_CNTRL_FCN(T,IN2)

%    This function was generated by the Symbolic Math Toolbox version 8.5.
%    10-Jun-2021 22:10:32

X = in2(11,:);
Y = in2(12,:);
Z = in2(13,:);
p = in2(14,:);
q = in2(15,:);
q1 = in2(7,:);
q2 = in2(8,:);
q3 = in2(9,:);
q4 = in2(10,:);
r = in2(16,:);
u = in2(4,:);
v = in2(5,:);
w = in2(6,:);
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
f_cntrl = [u.*(t2+t5+t12+t13)+w.*(t7+t10)+v.*(t6-t11);-v.*(t2+t4+t12+t14)+u.*(t6+t11)-w.*(t8-t9);-w.*(t2+t3+t13+t14)+v.*(t8+t9)+u.*(t7-t10);X+q1.*q3.*(9.8e+1./5.0)-q2.*q4.*(9.8e+1./5.0);Y+q1.*q4.*(9.8e+1./5.0)+q2.*q3.*(9.8e+1./5.0);Z-t2.*(4.9e+1./5.0)-t3.*(4.9e+1./5.0)+t4.*(4.9e+1./5.0)+t5.*(4.9e+1./5.0);(p.*q4)./2.0-(q.*q3)./2.0+(q2.*r)./2.0;(p.*q3)./2.0+(q.*q4)./2.0-(q1.*r)./2.0;p.*q2.*(-1.0./2.0)+(q.*q1)./2.0+(q4.*r)./2.0;p.*q1.*(-1.0./2.0)-(q.*q2)./2.0-(q3.*r)./2.0;0.0;0.0;0.0;0.0;0.0;0.0];
