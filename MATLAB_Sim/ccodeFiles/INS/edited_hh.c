float   t2 = q1*q1;
 float t3 = q2*q2;
 float t4 = q3*q3;
 float t5 = q4*q4;
 float t6 = q1*q2*2.0;
 float t7 = q1*q3*2.0;
 float t8 = q1*q4*2.0;
 float t9 = q2*q3*2.0;
 float t10 = q2*q4*2.0;
 float t11 = q3*q4*2.0;
 float t12 = -t3;
 float t13 = -t4;
 float t14 = -t5;
  h(0,0) = -mag_bias_x+magVec0(1)*(t6+t11)+magVec0(2)*(t7-t10)+magVec0(0)*(t2+t5+t12+t13);
  h(1,0) = -mag_bias_y+magVec0(2)*(t8+t9)+magVec0(0)*(t6-t11)-magVec0(1)*(t2+t4+t12+t14);
  h(2,0) = -mag_bias_z+magVec0(0)*(t7+t10)-magVec0(1)*(t8-t9)-magVec0(2)*(t2+t3+t13+t14);
  h(3,0) = N;
  h(4,0) = E;
  h(5,0) = D;
  h(6,0) = D;
  h(7,0) = vN;
  h(8,0) = vE;
  h(9,0) = vD;