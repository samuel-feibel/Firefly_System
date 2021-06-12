function plotStateCov(time,x1,els,ylabels,P1)
for i=1:length(els)
    subplot(length(els),1,i);
    plot(time,x1(els(i),:),'Color',[0 0.4470 0.7410]);
    if nargin > 4
        hold on
        plot(time,x1(els(i),:)'+2*sqrt(squeeze(P1(els(i),els(i),:))),'Color',[0.8500 0.3250 0.0980]);
        plot(time,x1(els(i),:)'-2*sqrt(squeeze(P1(els(i),els(i),:))),'Color',[0.8500 0.3250 0.0980]);
        
    end
    ylabel(ylabels{i});
    grid on
end
legend('Estimate','Estimate+2\sigma')
xlabel('Time [s]')