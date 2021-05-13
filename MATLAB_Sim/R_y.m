%--------------------------------------------------------------------------
%  Input:
%    angle       angle of rotation [rad]
%
%  Output:
%    rotmat      rotation matrix
%--------------------------------------------------------------------------
function rotmat = R_y(angle)
C = cos(angle);
S = sin(angle);

rotmat = [ C 0 S;...
           0 1 0 ;...
          -S 0 C];

