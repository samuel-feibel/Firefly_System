% Generate Code Commands

% codegen -lang:c++ mcadd -args {0,0}
% codegen -lang:c++ LatLonAlt2NED_Fcn -args {0,0,0,zeros(3,1),zeros(3,3)}
% codegen -lang:c++ LatLonAlt2ECEF_Fcn -args {0,0,0}
codegen -lang:c++ TECEF2NED_Fcn -args {zeros(3,1)}

