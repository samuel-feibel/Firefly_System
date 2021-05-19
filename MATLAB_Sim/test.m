
load('noMag.mat')
for i=1:size(xhat1u,2)
    hh(:,i) = h_Fcn(xhat1u(1:10,i),zeros(6,1));
end

plot((hh(5:7,:)./repmat(vecnorm(hh(5:7,:),1),3,1))');
hold on
plot((Z(5:7,:)./repmat(vecnorm(Z(5:7,:),1),3,1))');

figure
plot(vecnorm(hh(5:7,:),1));
hold on
plot(vecnorm(Z(5:7,:),1));
legend('h','z');