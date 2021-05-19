function [skewx] = skew(x)
%SKEW creates matrix form of cross product

skewx = [0, -x(3), x(2); x(3), 0, -x(1); -x(2), x(1), 0];

end

