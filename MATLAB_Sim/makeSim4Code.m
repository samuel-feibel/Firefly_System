% 
% syms Lat Lon Alt real
% 
% r0_ECEF = sym('r0_ECEF',[3,1],{'real'} );
% NED_C_ECEF = sym('NED_C_ECEF',[3,3],{'real'} );
% 
% r_NED = LatLonAlt2NED(Lat,Lon,Alt,r0_ECEF,NED_C_ECEF);
% 
% matlabFunction(r_NED,'Vars',{Lat,Lon,Alt,r0_ECEF,NED_C_ECEF},'File','LatLonAlt2NED_Fcn');
% 
% clear all;
% 
% syms Lat Lon Alt  real
% 
% r0_ECEF = LatLonAlt2ECEF(Lat,Lon,Alt);
% 
% matlabFunction(r0_ECEF,'Vars',{Lat,Lon,Alt},'File','LatLonAlt2ECEF_Fcn');

clear all;

r0_ECEF = sym('r0_ECEF',[3,1],{'real'} );

NED_C_ECEF = TECEF2NED(r0_ECEF);

matlabFunction(NED_C_ECEF,'Vars',{r0_ECEF},'File','TECEF2NED_Fcn');


disp(1)