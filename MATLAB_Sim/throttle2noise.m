%% Sensor Noise and Throttle Relations
addpath('DataFiles');

fileNames = "Combined_DATALOG.TXT";
bins = linspace(0,180,8);

for j = 1:length(fileNames)
    [flightData] = loadFlightData(fileNames{j});
    
    bins = linspace(0,180,8);
    
    for i=1:length(bins)-1
        idcs = logical((flightData.Throttle < bins(i+1)).*(flightData.Throttle > bins(i)));
        sigma(j).Gyr.x(i) = std(flightData.Gyr.x(idcs));
        sigma(j).Gyr.y(i) = std(flightData.Gyr.y(idcs));
        sigma(j).Gyr.z(i) = std(flightData.Gyr.z(idcs));
        sigma(j).Mag.x(i) = std(flightData.Mag.x(idcs));
        sigma(j).Mag.y(i) = std(flightData.Mag.y(idcs));
        sigma(j).Mag.z(i) = std(flightData.Mag.z(idcs));
        sigma(j).Acc.x(i) = std(flightData.Acc.x(idcs));
        sigma(j).Acc.y(i) = std(flightData.Acc.y(idcs));
        sigma(j).Acc.z(i) = std(flightData.Acc.z(idcs));
        sigma(j).Lat(i) = std(flightData.Lat(idcs));
        sigma(j).Lon(i) = std(flightData.Lon(idcs));
        sigma(j).Alt(i) = std(flightData.Alt(idcs));
        sigma(j).Heading(i) = std(flightData.Heading(idcs));
        sigma(j).ThrottleVal(i) = mean(bins(i:i+1));
        
    end
    
    % Gyro
    figure(1)
    subplot(3,3,1); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Gyr.x);
    ylabel('Gyr X 1\sigma [dps]'); xlabel('Throttle')
    subplot(3,3,4); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Gyr.y);
    ylabel('Gyr Y 1\sigma [dps]'); xlabel('Throttle')
    subplot(3,3,7); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Gyr.z);
    ylabel('Gyr Z 1\sigma [dps]'); xlabel('Throttle')
    
    % Mag
    subplot(3,3,2); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Mag.x);
    ylabel('Mag X 1\sigma [uT]'); xlabel('Throttle')
    subplot(3,3,5); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Mag.y);
    ylabel('Mag Y 1\sigma [uT]'); xlabel('Throttle')
    subplot(3,3,8); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Mag.z);
    ylabel('Mag Z 1\sigma [uT]'); xlabel('Throttle')
    
    % Accel
    subplot(3,3,3); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Acc.x);
    ylabel('Acc X 1\sigma [m/s^2]'); xlabel('Throttle')
    subplot(3,3,6); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Acc.y);
    ylabel('Acc Y 1\sigma [m/s^2]'); xlabel('Throttle')
    subplot(3,3,9); hold on;
    plot(sigma(j).ThrottleVal,sigma(j).Acc.z);
    ylabel('Acc Z 1\sigma [m/s^2]'); xlabel('Throttle')
   
    
end





