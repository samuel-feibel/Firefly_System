float t2 = fabs(u);
float t3 = fabs(v);
float t4 = fabs(w);
float t5 = q1*q1;
float t6 = q2*q2;
float t7 = q3*q3;
float t8 = q4*q4;
float t12 = magVec0(0)*q1*2.0;
float t13 = magVec0(0)*q2*2.0;
float t14 = magVec0(1)*q1*2.0;
float t15 = magVec0(0)*q3*2.0;
float t16 = magVec0(1)*q2*2.0;
float t17 = magVec0(2)*q1*2.0;
float t18 = magVec0(0)*q4*2.0;
float t19 = magVec0(1)*q3*2.0;
float t20 = magVec0(2)*q2*2.0;
float t21 = magVec0(1)*q4*2.0;
float t22 = magVec0(2)*q3*2.0;
float t23 = magVec0(2)*q4*2.0;
float t24 = q1*q2*2.0;
float t25 = q1*q3*2.0;
float t26 = q1*q4*2.0;
float t27 = q2*q3*2.0;
float t28 = q2*q4*2.0;
float t29 = q3*q4*2.0;
float t30 = q1*u*2.0;
float t31 = q2*u*2.0;
float t32 = q3*u*2.0;
float t33 = q4*u*2.0;
float t34 = q1*v*2.0;
float t35 = q2*v*2.0;
float t36 = q3*v*2.0;
float t37 = q4*v*2.0;
float t38 = q1*w*2.0;
float t39 = q2*w*2.0;
float t40 = q3*w*2.0;
float t41 = q4*w*2.0;
float t9 = t2*t2;
float t10 = t3*t3;
float t11 = t4*t4;
float t42 = -t14;
float t43 = -t15;
float t44 = -t20;
float t45 = -t27;
float t46 = -t29;
float  t47 = -t31;
float  t48 = -t36;
float   t49 = -t38;
float   t50 = -t6;
float   t51 = -t7;
float   t52 = -t8;
float   t53 = t24+t29;
float   t54 = t25+t28;
float   t62 = t12+t16+t22;
float   t63 = t30+t35+t40;
float  t55 = t24+t46;
float   t56 = t26+t45;
float   t57 = t53*u;
float   t58 = t54*w;
float   t61 = t9+t10+t11;
float   t65 = t13+t23+t42;
float   t66 = t17+t21+t43;
float   t67 = t18+t19+t44;
float   t68 = t34+t41+t47;
float   t69 = t32+t37+t49;
float   t70 = t33+t39+t48;
float   t72 = t5+t8+t50+t51;
float   t73 = t5+t7+t50+t52;
float   t59 = t55*v;
float   t60 = t56*w;
float   t64 = -t57;
float   t71 = 1.0/sqrt(t61);
float   t74 = t72*u;
float   t75 = t73*v;
float   t76 = t58+t59+t74;
float   t77 = t60+t64+t75;
float   t78 = t76*t76;
float   t79 = 1.0/t76;
float   t81 = t77*t77;
float   t80 = 1.0/t78;
float   t82 = t78+t81;
float   t83 = 1.0/t82;
H_jac(0,0) = 1.0;
H_jac(1,1) = 1.0;
H_jac(2,2) = 1.0;
H_jac(3,3) = t2*t71*((u/fabs(u)));
H_jac(3,4) = t3*t71*((v/fabs(v)));
H_jac(3,5) = t4*t71*((w/fabs(w)));
H_jac(4,6) = t62;
H_jac(4,7) = -t13+t14-t23;
H_jac(4,8) = t66;
H_jac(4,9) = t67;
H_jac(5,6) = t65;
H_jac(5,7) = t62;
H_jac(5,8) = -t18-t19+t20;
H_jac(5,9) = t66;
H_jac(6,6) = t15-t17-t21;
H_jac(6,7) = t67;
H_jac(6,8) = t62;
H_jac(6,9) = t65;
H_jac(7,3) = t78*t83*(t53*t79+t72*t77*t80);
H_jac(7,4) = -t78*t83*(t73*t79-t55*t77*t80);
H_jac(7,5) = -t78*t83*(t56*t79-t54*t77*t80);
H_jac(7,6) = -t78*t83*(t68*t79-t63*t77*t80);
H_jac(7,7) = t78*t83*(t63*t79+t68*t77*t80);
H_jac(7,8) = t78*t83*(t70*t79-t69*t77*t80);
H_jac(7,9) = t78*t83*(t69*t79+t70*t77*t80);
H_jac(8,2) = 1.0;
