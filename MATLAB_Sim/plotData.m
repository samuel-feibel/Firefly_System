startIdx = 1;
[flightData] = loadFlightData("DataFiles/ParamEstFlight2.txt",startIdx);

%% Position

r2d = 180/pi;

r0_ECEF = LatLonAlt2ECEF(flightData.Lat(1),flightData.Lon(1),flightData.Alt(1));
[NED_C_ECEF] = TECEF2NED(r0_ECEF);
r_ECEF = LatLonAlt2ECEF(flightData.Lat',flightData.Lon',flightData.Alt');

r_NED = zeros(3,size(r_ECEF,2));
for i=1:size(r_ECEF,2)
    r_NED(:,i) = NED_C_ECEF*(r_ECEF(:,i)-r_ECEF(:,1));
end

figure
plot3(r_NED(2,:),r_NED(1,:),-r_NED(3,:));
axis equal
xlabel('E'); ylabel('N'); zlabel('D');

% Pressure
figure
alt_all = pressure2alt(flightData.Pressure);
alt = alt_all((~isnan(alt_all)));
alt0 = alt(1);
alt = alt-alt0;
plot(flightData.Time(~isnan(alt_all)),-alt);
hold on
plot(flightData.Time,r_NED(3,:));

%% Inputs
figure
subplot(2,2,1)
plot(flightData.Time,flightData.Throttle);
ylabel('Throttle')
subplot(2,2,2)
plot(flightData.Time,flightData.Aileron);
ylabel('Aileron')
subplot(2,2,3)
plot(flightData.Time,flightData.Elevator);
ylabel('Elevator')
subplot(2,2,4)
plot(flightData.Time,flightData.Rudder);
ylabel('Rudder')

%% Sensors

figure

% Acceleration
subplot(3,2,1)
plot(flightData.Time,flightData.Acc.x);
ylabel('Acc X [m/s^2]')
subplot(3,2,3)
plot(flightData.Time,flightData.Acc.y);
ylabel('Acc Y [m/s^2]')
subplot(3,2,5)
plot(flightData.Time,flightData.Acc.z);
ylabel('Acc Z [m/s^2]')

% Gyro
subplot(3,2,2)
plot(flightData.Time,flightData.Gyr.x*r2d);
ylabel('Gyr X [deg/s]')
subplot(3,2,4)
plot(flightData.Time,flightData.Gyr.y*r2d);
ylabel('Gyr Y [deg/s]')
subplot(3,2,6)
plot(flightData.Time,flightData.Gyr.z*r2d);
ylabel('Gyr Z [deg/s]')

% Mag
figure
subplot(3,2,2)
plot(flightData.Time,flightData.Mag.x);
ylabel('Mag X')
subplot(3,2,4)
plot(flightData.Time,flightData.Mag.y);
ylabel('Mag Y ')
subplot(3,2,6)
plot(flightData.Time,flightData.Mag.z);
ylabel('Mag Z ')

figure
% Speed
subplot(2,1,1)
plot(flightData.Time,flightData.Speed);
ylabel('Speed [m/s]')

subplot(2,1,2)
plot(flightData.Time,flightData.Heading*r2d);
ylabel('Heading [deg]')

%% Auxiliary

figure

subplot(3,2,1)
plot(flightData.Time,flightData.pDOP);
ylabel('pDOP');
subplot(3,2,2)
plot(flightData.Time,flightData.SIV);
ylabel('SIV');
subplot(3,2,3)
plot(flightData.Time,flightData.autoMode);
ylabel('Auto Mode');
subplot(3,2,4)
plot(flightData.Time,flightData.auxMode);
ylabel('Aux Mode');
subplot(3,2,5)
plot(flightData.Time,flightData.Tmp);
ylabel('Temperature [C]');





