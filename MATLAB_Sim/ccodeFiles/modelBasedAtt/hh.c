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
  A0[0][0] = magVec0Sym2*(t6+t11)+magVec0Sym3*(t7-t10)+magVec0Sym1*(t2+t5+t12+t13);
  A0[1][0] = magVec0Sym3*(t8+t9)+magVec0Sym1*(t6-t11)-magVec0Sym2*(t2+t4+t12+t14);
  A0[2][0] = magVec0Sym1*(t7+t10)-magVec0Sym2*(t8-t9)-magVec0Sym3*(t2+t3+t13+t14);
  A0[3][0] = ax-q1*q3*(9.8E+1/5.0)+q2*q4*(9.8E+1/5.0);
  A0[4][0] = ay-q1*q4*(9.8E+1/5.0)-q2*q3*(9.8E+1/5.0);
  A0[5][0] = az+t2*(4.9E+1/5.0)+t3*(4.9E+1/5.0)-t4*(4.9E+1/5.0)-t5*(4.9E+1/5.0);