function [bias,magVec0] = makeMagBias(bias)
% Finds Magnetometer Bias


%% Sensor Noise and Throttle Relations
addpath('DataFiles');

[flightData] = loadFlightData('CompassTuning_XY.TXT');

idcs = find((flightData.Time > 24).*(flightData.Time < 31.6));

bias.Mag.x = mean(flightData.Mag.x(idcs));
bias.Mag.y = mean(flightData.Mag.y(idcs));

idcs = find(flightData.Time < 24);

magVec0 = mean([flightData.Mag.x(idcs)';...
    flightData.Mag.y(idcs)';...
    flightData.Mag.z(idcs)'],2);

% figure
% subplot(3,2,2)
% plot(flightData.Time,flightData.Mag.x);
% hold on
% plot(flightData.Time,bias.Mag.x*ones(1,length(flightData.Time)));
% ylabel('Mag X')
% subplot(3,2,4)
% plot(flightData.Time,flightData.Mag.y);
% hold on
% plot(flightData.Time,bias.Mag.y*ones(1,length(flightData.Time)));
% ylabel('Mag Y ')


[flightData] = loadFlightData('CompassTuning_Z.TXT');

idcs = find((flightData.Time > 45.7).*(flightData.Time < 51.8));

bias.Mag.z = mean(flightData.Mag.z(idcs));


% Mag

% subplot(3,2,6)
% plot(flightData.Time,flightData.Mag.z);
% hold on
% plot(flightData.Time,bias.Mag.z*ones(1,length(flightData.Time)));
% ylabel('Mag Z ')

end

