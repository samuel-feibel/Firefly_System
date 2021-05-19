function [q] = Euler2Quat(EulerAngles)
roll = EulerAngles(1,:);
pitch = EulerAngles(2,:);
yaw = EulerAngles(3,:);

cy = cos(yaw * 0.5);
sy = sin(yaw * 0.5);
cp = cos(pitch * 0.5);
sp = sin(pitch * 0.5);
cr = cos(roll * 0.5);
sr = sin(roll * 0.5);

q(1,:) = sr .* cp .* cy - cr .* sp .* sy;
q(2,:) = cr .* sp .* cy + sr .* cp .* sy;
q(3,:) = cr .* cp .* sy - sr .* sp .* cy;
q(4,:) = cr .* cp .* cy + sr .* sp .* sy;
end
