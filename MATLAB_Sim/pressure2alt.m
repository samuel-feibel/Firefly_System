function [alt] = pressure2alt(pressure)
% Pressure: hPa
% alt: meters

alt = -1/(1.2E-4).*log(pressure./1013.25);
end

