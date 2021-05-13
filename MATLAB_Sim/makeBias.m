function [bias,magVec0] = makeBias(fileName)
% finds bias values of gyro and the magnetometer vector for leveled facing
% north position. In future, magnetometer vector could be found as function
% of position

%% Sensor Noise and Throttle Relations
addpath('DataFiles');

[flightData] = loadFlightData(fileName);

bias.Gyr.x = mean(flightData.Gyr.x);
bias.Gyr.y = mean(flightData.Gyr.y);
bias.Gyr.z = mean(flightData.Gyr.z);

magVec0 = mean([flightData.Mag.x';...
                flightData.Mag.y';...
                flightData.Mag.z'],2);
            
end
