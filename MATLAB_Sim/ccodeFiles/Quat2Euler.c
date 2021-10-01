

float t2 = q2*q2;
float  t3 = t2*2.0;
float  t4 = -t3;
A0(0,0) = atan2(q1*q4*2.0+q2*q3*2.0,t4-(q1*q1)*2.0+1.0);
float temp = asin(q1*q3*2.0+q2*q4*2.0);
if (temp > 1.0){ temp = 1.0; }
if (temp < -1.0){ temp = -1.0; }
A0(1,0) = temp;
A0(2,0) = atan2(q1*q2*2.0+q3*q4*2.0,t4-(q3*q3)*2.0+1.0);
