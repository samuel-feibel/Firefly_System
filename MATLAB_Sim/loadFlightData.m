function [flightData] = loadFlightData(textFile,startIdx,endIdx)

A = readmatrix(textFile,'NumHeaderLines',3);

if nargin < 3
    endIdx = size(A,1);
    
    if nargin < 2
        startIdx = 1;
    end
    
end

fid = fopen(textFile);
stringA = fscanf(fid,'%s');
if contains(stringA,'Pressure')
    flightData.Time=A(startIdx:endIdx,1)*1E-3;            % s
    flightData.Acc.x=A(startIdx:endIdx,2)*1E-3*9.81;      % m/s^2
    flightData.Acc.y=A(startIdx:endIdx,3)*1E-3*9.81*-1;   % m/s^2
    flightData.Acc.z=A(startIdx:endIdx,4)*1E-3*9.81*-1;   % m/s^2
    flightData.Gyr.x=A(startIdx:endIdx,5)*pi/180;         % rad/s
    flightData.Gyr.y=A(startIdx:endIdx,6)*pi/180*-1;      % rad/s
    flightData.Gyr.z=A(startIdx:endIdx,7)*pi/180*-1;      % rad/s
    flightData.Mag.x=A(startIdx:endIdx,8);                % uT
    flightData.Mag.y=A(startIdx:endIdx,9)*-1;             % uT
    flightData.Mag.z=A(startIdx:endIdx,10)*-1;            % uT
    flightData.Tmp=A(startIdx:endIdx,11);                 % C
    flightData.Lat=A(startIdx:endIdx,12)*1E-7;            % deg
    flightData.Lon=A(startIdx:endIdx,13)*1E-7;            % deg
    flightData.Alt=A(startIdx:endIdx,14)*1E-3;            % m
    flightData.Speed=A(startIdx:endIdx,15)*1E-3;          % m/s
    flightData.Heading=A(startIdx:endIdx,16)*1E-5*pi/180; % deg
    flightData.pDOP=A(startIdx:endIdx,17);
    flightData.SIV=A(startIdx:endIdx,18);
    flightData.Pressure = A(startIdx:endIdx,19);           % hPa
    flightData.Pressure(flightData.Pressure==-1) = NaN;
    flightData.Throttle=A(startIdx:endIdx,20);            
    flightData.Aileron=A(startIdx:endIdx,21);
    flightData.Elevator=A(startIdx:endIdx,22);
    flightData.Rudder=A(startIdx:endIdx,23);
    flightData.autoMode=A(startIdx:endIdx,24);
    flightData.auxMode=A(startIdx:endIdx,25);
else
    
    flightData.Time=A(startIdx:endIdx,1)*1E-3;            % s
    flightData.Acc.x=A(startIdx:endIdx,2)*1E-3*9.81;      % m/s^2
    flightData.Acc.y=A(startIdx:endIdx,3)*1E-3*9.81*-1;   % m/s^2
    flightData.Acc.z=A(startIdx:endIdx,4)*1E-3*9.81*-1;   % m/s^2
    flightData.Gyr.x=A(startIdx:endIdx,5)*pi/180;         % rad/s
    flightData.Gyr.y=A(startIdx:endIdx,6)*pi/180*-1;      % rad/s
    flightData.Gyr.z=A(startIdx:endIdx,7)*pi/180*-1;      % rad/s
    flightData.Mag.x=A(startIdx:endIdx,8);                % uT
    flightData.Mag.y=A(startIdx:endIdx,9)*-1;             % uT
    flightData.Mag.z=A(startIdx:endIdx,10)*-1;            % uT
    flightData.Tmp=A(startIdx:endIdx,11);                 % C
    flightData.Lat=A(startIdx:endIdx,12)*1E-7;            % deg
    flightData.Lon=A(startIdx:endIdx,13)*1E-7;            % deg
    flightData.Alt=A(startIdx:endIdx,14)*1E-3;            % m
    flightData.Speed=A(startIdx:endIdx,15)*1E-3;          % m/s
    flightData.Heading=A(startIdx:endIdx,16)*1E-5*pi/180; % deg
    flightData.pDOP=A(startIdx:endIdx,17);
    flightData.SIV=A(startIdx:endIdx,18);
    flightData.Throttle=A(startIdx:endIdx,19);
    flightData.Aileron=A(startIdx:endIdx,20);
    flightData.Elevator=A(startIdx:endIdx,21);
    flightData.Rudder=A(startIdx:endIdx,22);
    flightData.autoMode=A(startIdx:endIdx,23);
    flightData.auxMode=A(startIdx:endIdx,24);
end


end