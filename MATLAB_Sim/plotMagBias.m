close all;
addpath('DataFiles');
mid = @(data) (max(data)+min(data))/2;

[flightData] = loadFlightData('magTuning_NED_Sunapee.TXT');

hold on
plot(flightData.Time,flightData.Mag.x);
plot(flightData.Time,flightData.Mag.y);
plot(flightData.Time,flightData.Mag.z);

magVec0_uncorrected = [median(flightData.Mag.x);median(flightData.Mag.y);median(flightData.Mag.z)];

figure 
hold on
plot(flightData.Time,flightData.Gyr.x);
plot(flightData.Time,flightData.Gyr.y);
plot(flightData.Time,flightData.Gyr.z);

gyrBias = [median(flightData.Gyr.x);median(flightData.Gyr.y);median(flightData.Gyr.z)];

close all;
[flightData] = loadFlightData('magTuning_10202021_3.txt');

figure
hold on
plot(flightData.Time,flightData.Mag.x);
plot(flightData.Time,flightData.Mag.y);
plot(flightData.Time,flightData.Mag.z);
legend('x','y','z')

bias = [mid(flightData.Mag.x);mid(flightData.Mag.y);mid(flightData.Mag.z)];


magVec0 = magVec0_uncorrected - bias;
    



