function [sigma] = makeSigma(fileName,Nbins)

%% Sensor Noise and Throttle Relations
addpath('DataFiles');

order  = 1;
syms dT;

if nargin < 2
    Nbins = 8;
end

binEdges = linspace(0,180,Nbins+1);

[flightData] = loadFlightData(fileName);

for i=1:length(binEdges)-1
    idcs = logical((flightData.Throttle < binEdges(i+1)).*(flightData.Throttle > binEdges(i)));
    sigmaData.Gyr.x(i) = std(flightData.Gyr.x(idcs));
    sigmaData.Gyr.y(i) = std(flightData.Gyr.y(idcs));
    sigmaData.Gyr.z(i) = std(flightData.Gyr.z(idcs));
    sigmaData.Mag.x(i) = std(flightData.Mag.x(idcs));
    sigmaData.Mag.y(i) = std(flightData.Mag.y(idcs));
    sigmaData.Mag.z(i) = std(flightData.Mag.z(idcs));
    sigmaData.Acc.x(i) = std(flightData.Acc.x(idcs));
    sigmaData.Acc.y(i) = std(flightData.Acc.y(idcs));
    sigmaData.Acc.z(i) = std(flightData.Acc.z(idcs));
    sigmaData.Lat(i) = std(flightData.Lat(idcs));
    sigmaData.Lon(i) = std(flightData.Lon(idcs));
    sigmaData.Alt(i) = std(flightData.Alt(idcs));
    sigmaData.Heading(i) = std(flightData.Heading(idcs));
    sigmaData.ThrottleVal(i) = mean(binEdges(i:i+1));
end

p = polyfit(sigmaData.ThrottleVal,sigmaData.Gyr.x,order);
sigma.Gyr.x = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Gyr.y,order);
sigma.Gyr.y = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Gyr.z,order);
sigma.Gyr.z = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Mag.x,order);
sigma.Mag.x = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Mag.y,order);
sigma.Mag.y = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Mag.z,order);
sigma.Mag.z = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Acc.x,order);
sigma.Acc.x = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Acc.y,order);
sigma.Acc.y = p(2) + p(1)*dT;
p = polyfit(sigmaData.ThrottleVal,sigmaData.Acc.z,order);
sigma.Acc.z = p(2) + p(1)*dT;

% Pulled from DataSheet: https://media.digikey.com/pdf/Data%20Sheets/Sparkfun%20PDFs/GPS-15210_Web.pdf
sigma.N = sqrt(2)*2.5;  % m
sigma.E = sqrt(2)*2.5;  % m
sigma.D = 10;            % m     (THIS IS A GUESS)
sigma.Speed = 0.05;     % m/s
sigma.Heading = 0.3*pi/180;     % rad

% Pulled from Site: https://www.adafruit.com/product/4494
sigma.alt = 0.02;

end

