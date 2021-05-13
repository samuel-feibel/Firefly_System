function plotStates(time,x1,els,ylabels,x2,legends)
for i=1:length(els)
    subplot(length(els),1,i);
    plot(time,x1(els(i),:));
    if nargin > 4
        hold on
        plot(time,x2(els(i),:));
        if nargin > 4
            legend(legends)
        end
    end
    ylabel(ylabels{i});
    
end

xlabel('Time')