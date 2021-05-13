function [NED_C_ECEF] = TECEF2NED(r_ECEF)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

phi = asin(r_ECEF(3)/norm(r_ECEF));
lambda = atan2(r_ECEF(2),r_ECEF(1));

NED_C_ECEF = [-sin(phi)*cos(lambda) -sin(lambda) -cos(phi)*cos(lambda);...
              -sin(phi)*sin(lambda)  cos(lambda) -cos(phi)*sin(lambda);...
              cos(phi)               0           -sin(phi)]';
          

end

