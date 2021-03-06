function out1 = heading_Fcn(in1,in2)
%heading_Fcn
%    OUT1 = heading_Fcn(IN1,IN2)

%    This function was generated by the Symbolic Math Toolbox version 9.0.
%    24-Sep-2021 14:29:11

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
out1 = atan2(u.*(t6+t7)-v.*(t2+t4-t5+t8)-w.*(q1.*q4.*2.0-q2.*q3.*2.0),u.*(t2-t4+t5+t8)+v.*(t6-t7)+w.*(q1.*q3.*2.0+q2.*q4.*2.0));
