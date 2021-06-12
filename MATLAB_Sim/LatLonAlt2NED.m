function r_NED = LatLonAlt2NED(Lat,Lon,Alt,r0_ECEF,NED_C_ECEF)
Lat = Lat*pi/180; Lon = Lon*pi/180;
a = 6378137.0;  % m
b = 6356752.314245; % m
N = a^2./sqrt(a^2.*cos(Lat).^2+b^2.*sind(Lat).^2);

r_ECEF = [(N+Alt).*cos(Lat).*cosd(Lon);...
          (N+Alt).*cos(Lat).*sind(Lon);...
          (b^2/a^2.*N+Alt).*sind(Lat)];
      
r_NED = NED_C_ECEF*(r_ECEF-r0_ECEF);
end

