function f_true = f_true_Fcn(in1,in2,in3,in4)
%f_true_Fcn
%    F_TRUE = f_true_Fcn(IN1,IN2,IN3,IN4)

%    This function was generated by the Symbolic Math Toolbox version 9.0.
%    16-Nov-2021 11:04:07

axn = in3(4,:);
ayn = in3(5,:);
azn = in3(6,:);
fx = in2(4,:);
fy = in2(5,:);
fz = in2(6,:);
gravVec0Sym1 = in4(1,:);
gravVec0Sym2 = in4(2,:);
gravVec0Sym3 = in4(3,:);
p = in2(1,:);
pn = in3(1,:);
q = in2(2,:);
q1 = in1(1,:);
q2 = in1(2,:);
q3 = in1(3,:);
q4 = in1(4,:);
qn = in3(2,:);
r = in2(3,:);
rn = in3(3,:);
vD = in1(10,:);
vE = in1(9,:);
vN = in1(8,:);
t2 = conj(pn);
t3 = conj(qn);
t4 = conj(rn);
t5 = q1.^2;
t6 = q2.^2;
t7 = q3.^2;
t8 = q4.^2;
t9 = q1.*q2.*2.0;
t10 = q1.*q3.*2.0;
t11 = q1.*q4.*2.0;
t12 = q2.*q3.*2.0;
t13 = q2.*q4.*2.0;
t14 = q3.*q4.*2.0;
t15 = -t12;
t16 = -t13;
t17 = -t14;
t18 = -t6;
t19 = -t7;
t20 = -t8;
t21 = t9+t14;
t22 = t10+t13;
t23 = t11+t12;
t24 = t9+t17;
t25 = t10+t16;
t26 = t11+t15;
t27 = t5+t8+t18+t19;
t28 = t5+t7+t18+t20;
t29 = t5+t6+t19+t20;
mt1 = [(p.*q4)./2.0-(q.*q3)./2.0+(q2.*r)./2.0+(q2.*t4)./2.0-(q3.*t3)./2.0+(q4.*t2)./2.0,(p.*q3)./2.0+(q.*q4)./2.0-(q1.*r)./2.0-(q1.*t4)./2.0+(q3.*t2)./2.0+(q4.*t3)./2.0,p.*q2.*(-1.0./2.0)+(q.*q1)./2.0+(q4.*r)./2.0+(q1.*t3)./2.0-(q2.*t2)./2.0+(q4.*t4)./2.0,p.*q1.*(-1.0./2.0)-(q.*q2)./2.0-(q3.*r)./2.0-(q1.*t2)./2.0-(q2.*t3)./2.0-(q3.*t4)./2.0,vN,vE,vD,-gravVec0Sym1+axn.*t27+ayn.*t24+azn.*t22+fx.*t27+fy.*t24+fz.*t22];
mt2 = [-gravVec0Sym2+axn.*t21-ayn.*t28-azn.*t26+fx.*t21-fy.*t28-fz.*t26,-gravVec0Sym3+axn.*t25+ayn.*t23-azn.*t29+fx.*t25+fy.*t23-fz.*t29,0.0,0.0,0.0];
f_true = reshape([mt1,mt2],13,1);
