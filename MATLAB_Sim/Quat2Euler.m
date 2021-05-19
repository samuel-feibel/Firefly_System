function [Euler] = Quat2Euler(q)

q1 = q(1,:);
q2 = q(2,:);
q3 = q(3,:);
q4 = q(4,:);

phi = atan2(2*(q2.*q3+q1.*q4),1-2*(q1.^2+q2.^2));
temp = 2*(q1.*q3+q4.*q2);
gr1 = temp>1;
le1 = temp<-1;
temp(gr1)=1;
temp(le1)=-1;
theta = asin(temp);

% theta = atan2(-sin(phi).*(q4.*q2+q3.*q1),(q2.*q3-q1.*q4));

psi = atan2(2*(q1.*q2+q3.*q4),1-2*(q2.^2+q3.^2));

Euler = [phi;theta;psi];
end