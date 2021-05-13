%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%--------------------------------------------------------------------------
function [rotmat] = R_x(angle)
C = cos(angle);
S = sin(angle);

rotmat = [1.0 0.0 0.0;...
          0.0 C -S;...
          0.0 S C];

