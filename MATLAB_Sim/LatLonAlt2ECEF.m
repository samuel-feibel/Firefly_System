function [r_ECEF] = LatLonAlt2ECEF(lat,lon,alt)
a = 6378137.0;  % m
b = 6356752.314245; % m
N = a^2./sqrt(a^2.*cosd(lat).^2+b^2.*sind(lat).^2);

r_ECEF = [(N+alt).*cosd(lat).*cosd(lon);...
          (N+alt).*cosd(lat).*sind(lon);...
          (b^2/a^2.*N+alt).*sind(lat)];
        
end

