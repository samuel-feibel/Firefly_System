  t2 = q1*q1;
  t3 = q2*q2;
  t4 = q3*q3;
  t5 = q4*q4;
  t6 = q1*q2*2.0;
  t7 = q1*q3*2.0;
  t8 = q1*q4*2.0;
  t9 = q2*q3*2.0;
  t10 = q2*q4*2.0;
  t11 = q3*q4*2.0;
  t12 = -t3;
  t13 = -t4;
  t14 = -t5;
  A0[0][0] = magVec02*(t6+t11)+magVec03*(t7-t10)+magVec01*(t2+t5+t12+t13);
  A0[1][0] = magVec03*(t8+t9)+magVec01*(t6-t11)-magVec02*(t2+t4+t12+t14);
  A0[2][0] = magVec01*(t7+t10)-magVec02*(t8-t9)-magVec03*(t2+t3+t13+t14);
