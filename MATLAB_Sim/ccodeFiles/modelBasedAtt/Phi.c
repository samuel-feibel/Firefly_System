  t2 = fx*q1*2.0;
  t3 = fx*q2*2.0;
  t4 = fx*q3*2.0;
  t5 = fx*q4*2.0;
  t6 = fy*q1*2.0;
  t7 = fy*q2*2.0;
  t8 = fy*q3*2.0;
  t9 = fy*q4*2.0;
  t10 = fz*q1*2.0;
  t11 = fz*q2*2.0;
  t12 = fz*q3*2.0;
  t13 = fz*q4*2.0;
  t17 = (delt*p)/2.0;
  t18 = (delt*q)/2.0;
  t19 = (delt*r)/2.0;
  t14 = -t3;
  t15 = -t8;
  t16 = -t10;
  t20 = -t17;
  t21 = -t18;
  t22 = -t19;
  t23 = t2+t7+t12;
  t24 = t6+t13+t14;
  t25 = t4+t9+t16;
  t26 = t5+t11+t15;
  t27 = delt*t23;
  t28 = delt*t24;
  t29 = delt*t25;
  t30 = delt*t26;
  A0[0][0] = 1.0;
  A0[0][1] = t19;
  A0[0][2] = t21;
  A0[0][3] = t17;
  A0[1][0] = t22;
  A0[1][1] = 1.0;
  A0[1][2] = t17;
  A0[1][3] = t18;
  A0[2][0] = t18;
  A0[2][1] = t20;
  A0[2][2] = 1.0;
  A0[2][3] = t19;
  A0[3][0] = t20;
  A0[3][1] = t21;
  A0[3][2] = t22;
  A0[3][3] = 1.0;
  A0[4][4] = 1.0;
  A0[4][7] = delt;
  A0[5][5] = 1.0;
  A0[5][8] = delt;
  A0[6][6] = 1.0;
  A0[6][9] = delt;
  A0[7][0] = t27;
  A0[7][1] = t28;
  A0[7][2] = -t29;
  A0[7][3] = t30;
  A0[7][7] = 1.0;
  A0[8][0] = -t28;
  A0[8][1] = t27;
  A0[8][2] = t30;
  A0[8][3] = t29;
  A0[8][8] = 1.0;
  A0[9][0] = t29;
  A0[9][1] = -t30;
  A0[9][2] = t27;
  A0[9][3] = t28;
  A0[9][9] = 1.0;
  A0[10][10] = 1.0;
  A0[11][11] = 1.0;
  A0[12][12] = 1.0;
