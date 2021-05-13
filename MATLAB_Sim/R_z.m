%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%--------------------------------------------------------------------------
function [rotmat] = R_z(angle)
C = cos(angle);
S = sin(angle);

rotmat = [C -S 0;...
          S C 0;...
          0 0 1];

