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

if contains(stringA,'Version2')
    flightData.Time=A(startIdx:endIdx,1);            % s
    flightData.IMU.Acc=A(startIdx:endIdx,2:4);      % m/s^2
    flightData.IMU.Gyr=A(startIdx:endIdx,5:7);         % rad/s
    flightData.IMU.rawGyr=A(startIdx:endIdx,8:10);         % deg/s
    flightData.IMU.rawMag=A(startIdx:endIdx,11:13);                % uT
    flightData.baro.Tmp=A(startIdx:endIdx,14);                 % C
    flightData.GPS.Lat=A(startIdx:endIdx,15);            % deg
    flightData.GPS.Lon=A(startIdx:endIdx,16);            % deg
    flightData.GPS.Alt=A(startIdx:endIdx,17);            % m
    flightData.GPS.Speed=A(startIdx:endIdx,18);          % m/s
    flightData.GPS.Heading=A(startIdx:endIdx,19); % deg
    flightData.GPS.pDOP=A(startIdx:endIdx,20);
    flightData.GPS.SIV=A(startIdx:endIdx,21);
    flightData.GPS.NED=A(startIdx:endIdx,22:24);
    flightData.GPS.vNED=A(startIdx:endIdx,25:27);
    flightData.baro.Pressure = A(startIdx:endIdx,28);           % hPa
    flightData.baro.Alt = A(startIdx:endIdx,29);           % hPa
    flightData.Reciever.Throttle=A(startIdx:endIdx,30);            
    flightData.Reciever.Elevator=A(startIdx:endIdx,31);
    flightData.Reciever.Aileron=A(startIdx:endIdx,32);
    flightData.Reciever.Rudder=A(startIdx:endIdx,33);
    flightData.mode.auto=A(startIdx:endIdx,34);
    flightData.mode.aux=A(startIdx:endIdx,35);
    flightData.stateEst.q=A(startIdx:endIdx,36:39);            
    flightData.stateEst.NED=A(startIdx:endIdx,40:42);
    flightData.stateEst.vNED=A(startIdx:endIdx,43:45);
    flightData.stateEst.mag_bias=A(startIdx:endIdx,46:48);
    flightData.servo.Throttle=A(startIdx:endIdx,49);            
    flightData.servo.Elevator=A(startIdx:endIdx,50);
    flightData.servo.Aileron=A(startIdx:endIdx,51);
    flightData.servo.Rudder=A(startIdx:endIdx,52);
elseif contains(stringA,'Version1')
    flightData.Time=A(startIdx:endIdx,1);            % s
    flightData.IMU.Acc=A(startIdx:endIdx,2:4);      % m/s^2
    flightData.IMU.Gyr=A(startIdx:endIdx,5:7);         % rad/s
    flightData.IMU.Mag=A(startIdx:endIdx,8:10);                % uT
    flightData.IMU.rawGyr=A(startIdx:endIdx,11:13);         % deg/s
    flightData.IMU.rawMag=A(startIdx:endIdx,14:16);                % uT
    flightData.baro.Tmp=A(startIdx:endIdx,17);                 % C
    flightData.GPS.Lat=A(startIdx:endIdx,18);            % deg
    flightData.GPS.Lon=A(startIdx:endIdx,19);            % deg
    flightData.GPS.Alt=A(startIdx:endIdx,20);            % m
    flightData.GPS.Speed=A(startIdx:endIdx,21);          % m/s
    flightData.GPS.Heading=A(startIdx:endIdx,22); % deg
    flightData.GPS.pDOP=A(startIdx:endIdx,23);
    flightData.GPS.SIV=A(startIdx:endIdx,24);
    flightData.GPS.NED=A(startIdx:endIdx,25:27);
    flightData.GPS.vNED=A(startIdx:endIdx,28:30);
    flightData.baro.Pressure = A(startIdx:endIdx,31);           % hPa
    flightData.baro.Alt = A(startIdx:endIdx,32);           % hPa
    flightData.Reciever.Throttle=A(startIdx:endIdx,33);            
    flightData.Reciever.Elevator=A(startIdx:endIdx,34);
    flightData.Reciever.Aileron=A(startIdx:endIdx,35);
    flightData.Reciever.Rudder=A(startIdx:endIdx,36);
    flightData.mode.auto=A(startIdx:endIdx,37);
    flightData.mode.aux=A(startIdx:endIdx,38);
    flightData.stateEst.NED=A(startIdx:endIdx,39:41);            
    flightData.stateEst.uvw=A(startIdx:endIdx,42:44);
    flightData.stateEst.q=A(startIdx:endIdx,45);
    flightData.servo.Throttle=A(startIdx:endIdx,46);            
    flightData.servo.Elevator=A(startIdx:endIdx,47);
    flightData.servo.Aileron=A(startIdx:endIdx,48);
    flightData.servo.Rudder=A(startIdx:endIdx,49);
elseif contains(stringA,'Protobuf')
    flightData.Time=A(startIdx:endIdx,1);            % s
    flightData.IMU.Acc=A(startIdx:endIdx,2:4);      % m/s^2
    flightData.IMU.Gyr=A(startIdx:endIdx,5:7);         % rad/s
    flightData.IMU.Mag=A(startIdx:endIdx,8:10);                % uT
    flightData.IMU.rawGyr=A(startIdx:endIdx,11:13);         % deg/s
    flightData.IMU.rawMag=A(startIdx:endIdx,14:16);                % uT
    flightData.baro.Tmp=A(startIdx:endIdx,17);                 % C
    flightData.GPS.Lat=A(startIdx:endIdx,18);            % deg
    flightData.GPS.Lon=A(startIdx:endIdx,19);            % deg
    flightData.GPS.Alt=A(startIdx:endIdx,20);            % m
    flightData.GPS.Speed=A(startIdx:endIdx,21);          % m/s
    flightData.GPS.Heading=A(startIdx:endIdx,22); % deg
    flightData.GPS.pDOP=A(startIdx:endIdx,23);
    flightData.GPS.SIV=A(startIdx:endIdx,24);
    flightData.GPS.NED=A(startIdx:endIdx,25:27);
    flightData.baro.Pressure = A(startIdx:endIdx,28);           % hPa
    flightData.baro.Alt = A(startIdx:endIdx,29);           % hPa
    flightData.Reciever.Throttle=A(startIdx:endIdx,30);            
    flightData.Reciever.Elevator=A(startIdx:endIdx,31);
    flightData.Reciever.Aileron=A(startIdx:endIdx,32);
    flightData.Reciever.Rudder=A(startIdx:endIdx,33);
    flightData.mode.auto=A(startIdx:endIdx,34);
    flightData.mode.aux=A(startIdx:endIdx,35);
    flightData.stateEst.NED=A(startIdx:endIdx,36:38);            
    flightData.stateEst.uvw=A(startIdx:endIdx,39:41);
    flightData.stateEst.q=A(startIdx:endIdx,42);
    flightData.servo.Throttle=A(startIdx:endIdx,43);            
    flightData.servo.Elevator=A(startIdx:endIdx,44);
    flightData.servo.Aileron=A(startIdx:endIdx,45);
    flightData.servo.Rudder=A(startIdx:endIdx,46);

elseif contains(stringA,'Reciever')
    
    
    flightData.Time=A(startIdx:endIdx,1)*1E-3;            % s
    flightData.Acc.x=A(startIdx:endIdx,2)*1E-3*9.81;      % m/s^2
    flightData.Acc.y=A(startIdx:endIdx,3)*1E-3*9.81*-1;   % m/s^2
    flightData.Acc.z=A(startIdx:endIdx,4)*1E-3*9.81*-1;   % m/s^2
    flightData.Gyr.x=A(startIdx:endIdx,5)*pi/180;         % rad/s
    flightData.Gyr.y=A(startIdx:endIdx,6)*pi/180*-1;      % rad/s
    flightData.Gyr.z=A(startIdx:endIdx,7)*pi/180*-1;      % rad/s
    flightData.Mag.x=A(startIdx:endIdx,8);                % uT
    flightData.Mag.y=A(startIdx:endIdx,9);             % uT
    flightData.Mag.z=A(startIdx:endIdx,10);            % uT
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
    flightData.RecieverThrottle=A(startIdx:endIdx,20);            
    flightData.RecieverElevator=A(startIdx:endIdx,21);
    flightData.RecieverAileron=A(startIdx:endIdx,22);
    flightData.RecieverRudder=A(startIdx:endIdx,23);
    flightData.autoMode=A(startIdx:endIdx,24);
    flightData.auxMode=A(startIdx:endIdx,25);
    flightData.N=A(startIdx:endIdx,26);            
    flightData.E=A(startIdx:endIdx,27);
    flightData.D=A(startIdx:endIdx,28);
    flightData.u=A(startIdx:endIdx,29);
    flightData.v=A(startIdx:endIdx,30);            
    flightData.w=A(startIdx:endIdx,31);
    flightData.q1=A(startIdx:endIdx,32);
    flightData.q2=A(startIdx:endIdx,33);
    flightData.q3=A(startIdx:endIdx,34);            
    flightData.q4=A(startIdx:endIdx,35);
    flightData.Throttle=A(startIdx:endIdx,36);            
    flightData.Elevator=A(startIdx:endIdx,37);
    flightData.Aileron=A(startIdx:endIdx,38);
    flightData.Rudder=A(startIdx:endIdx,39);
elseif contains(stringA,'Pressure')
    flightData.Time=A(startIdx:endIdx,1)*1E-3;            % s
    flightData.Acc.x=A(startIdx:endIdx,2)*1E-3*9.81;      % m/s^2
    flightData.Acc.y=A(startIdx:endIdx,3)*1E-3*9.81*-1;   % m/s^2
    flightData.Acc.z=A(startIdx:endIdx,4)*1E-3*9.81*-1;   % m/s^2
    flightData.Gyr.x=A(startIdx:endIdx,5)*pi/180;         % rad/s
    flightData.Gyr.y=A(startIdx:endIdx,6)*pi/180*-1;      % rad/s
    flightData.Gyr.z=A(startIdx:endIdx,7)*pi/180*-1;      % rad/s
    flightData.Mag.x=A(startIdx:endIdx,8);                % uT
    flightData.Mag.y=A(startIdx:endIdx,9);             % uT
    flightData.Mag.z=A(startIdx:endIdx,10);            % uT
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
    flightData.Mag.y=A(startIdx:endIdx,9);             % uT
    flightData.Mag.z=A(startIdx:endIdx,10);            % uT
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