function r_NED = LatLonAlt2NED_Fcn(Lat,Lon,Alt,in4,in5)
%LATLONALT2NED_FCN
%    R_NED = LATLONALT2NED_FCN(LAT,LON,ALT,IN4,IN5)

%    This function was generated by the Symbolic Math Toolbox version 8.5.
%    10-Jun-2021 23:09:47

NED_C_ECEF1_1 = in5(1);
NED_C_ECEF1_2 = in5(4);
NED_C_ECEF1_3 = in5(7);
NED_C_ECEF2_1 = in5(2);
NED_C_ECEF2_2 = in5(5);
NED_C_ECEF2_3 = in5(8);
NED_C_ECEF3_1 = in5(3);
NED_C_ECEF3_2 = in5(6);
NED_C_ECEF3_3 = in5(9);
r0_ECEF1 = in4(1,:);
r0_ECEF2 = in4(2,:);
r0_ECEF3 = in4(3,:);
t2 = pi.^2;
t3 = (Lat.*pi)./1.8e+2;
t4 = cos(t3);
t6 = (Lat.*t2)./3.24e+4;
t7 = (Lon.*t2)./3.24e+4;
t5 = t4.^2;
t8 = cos(t7);
t9 = sin(t6);
t10 = sin(t7);
t11 = t9.^2;
t12 = t5.*4.0680631590769e+13;
t13 = t11.*4.040829998465916e+13;
t14 = t12+t13;
t15 = 1.0./sqrt(t14);
t16 = t15.*4.0680631590769e+13;
t24 = t15.*4.040829998465915e+13;
t17 = Alt+t16;
t25 = Alt+t24;
t18 = t4.*t8.*t17;
t19 = t4.*t10.*t17;
t26 = t9.*t25;
t20 = -t18;
t21 = -t19;
t27 = -t26;
t22 = r0_ECEF1+t20;
t23 = r0_ECEF2+t21;
t28 = r0_ECEF3+t27;
r_NED = [-NED_C_ECEF1_1.*t22-NED_C_ECEF1_2.*t23-NED_C_ECEF1_3.*t28;-NED_C_ECEF2_1.*t22-NED_C_ECEF2_2.*t23-NED_C_ECEF2_3.*t28;-NED_C_ECEF3_1.*t22-NED_C_ECEF3_2.*t23-NED_C_ECEF3_3.*t28];