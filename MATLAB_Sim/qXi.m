function [out] = qXi(q)
%qXi Summary of this function goes here
out = [q(4)*eye(3) + skew(q(1:3)); -q(1:3).'];
end

