function h = h_Fcn(in1,in2)
%H_FCN
%    H = H_FCN(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 8.5.
%    18-May-2021 22:41:31

D = in1(3,:);
E = in1(2,:);
N = in1(1,:);
q1 = in1(7,:);
q2 = in1(8,:);
q3 = in1(9,:);
q4 = in1(10,:);
u = in1(4,:);
v = in1(5,:);
w = in1(6,:);
t2 = q1.^2;
t3 = q2.^2;
t4 = q3.^2;
t5 = q4.^2;
t6 = q1.*q2.*2.0;
t7 = q3.*q4.*2.0;
t8 = -t3;
h = [N;E;D;sqrt(abs(u).^2+abs(v).^2+abs(w).^2);t2.*1.181760952660976e+1-t3.*1.181760952660976e+1-t4.*1.181760952660976e+1+t5.*1.181760952660976e+1-q1.*q2.*6.117036165833703+q1.*q3.*1.06871028374007e+2-q2.*q4.*1.06871028374007e+2-q3.*q4.*6.117036165833703;t2.*3.058518082916851-t3.*3.058518082916851+t4.*3.058518082916851-t5.*3.058518082916851+q1.*q2.*2.363521905321952e+1+q1.*q4.*1.06871028374007e+2+q2.*q3.*1.06871028374007e+2-q3.*q4.*2.363521905321952e+1;t2.*(-5.343551418700349e+1)-t3.*5.343551418700349e+1+t4.*5.343551418700349e+1+t5.*5.343551418700349e+1+q1.*q3.*2.363521905321952e+1+q1.*q4.*6.117036165833703-q2.*q3.*6.117036165833703+q2.*q4.*2.363521905321952e+1;atan2(u.*(t6+t7)-v.*(t2+t4-t5+t8)-w.*(q1.*q4.*2.0-q2.*q3.*2.0),u.*(t2-t4+t5+t8)+v.*(t6-t7)+w.*(q1.*q3.*2.0+q2.*q4.*2.0))];
