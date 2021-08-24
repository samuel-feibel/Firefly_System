% Generate Code Commands

% codegen -lang:c++ mcadd -args {0,0}
% codegen -lang:c++ LatLonAlt2NED_Fcn -args {0,0,0,zeros(3,1),zeros(3,3)}
% codegen -lang:c++ LatLonAlt2ECEF_Fcn -args {0,0,0}
% codegen -lang:c++ TECEF2NED_Fcn -args {zeros(3,1)}
codegen -lang:c++ f_Fcn -args {0,zeros(10,1),zeros(6,1)}

% codegen -lang:c++ F_jac_Fcn -args {zeros(10,1),zeros(6,1)}
