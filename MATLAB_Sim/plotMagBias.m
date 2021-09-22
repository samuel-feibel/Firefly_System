close all;
addpath('DataFiles');
mid = @(data) (max(data)+min(data))/2;

[flightData] = loadFlightData('magTuning_NorthLevel_11H.TXT');

hold on
plot(flightData.Time,flightData.Mag.x);
plot(flightData.Time,flightData.Mag.y);
plot(flightData.Time,flightData.Mag.z);

magVec0_uncorrected = [mean(flightData.Mag.x);mean(flightData.Mag.y);mean(flightData.Mag.z)];

[flightData] = loadFlightData('magTuning_11H.txt');

figure
hold on
plot(flightData.Time,flightData.Mag.x);
plot(flightData.Time,flightData.Mag.y);
plot(flightData.Time,flightData.Mag.z);
legend('x','y','z')

bias = [mid(flightData.Mag.x);mid(flightData.Mag.y);mid(flightData.Mag.z)];


magVec0 = magVec0_uncorrected - bias;
    


