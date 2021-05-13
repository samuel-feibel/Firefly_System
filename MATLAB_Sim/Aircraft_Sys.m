%% Simulate and Estimate Parameters of Aircraft in Pitch
%  Capable of multiple Flights with Smoothing in between
% 10 Unknown Parameters

clearvars; close all; clc;
rng(100)
d2r = pi/180;

%% Aircraft True Parameters

V = 279.1; %ft/s
Theta0 = 0;
g0 = 32; % ft/s^2
u0 = V;
param.g0 = g0;

%%%%% Parameter Stuff %%%%%
np=10;

Gp = zeros(np,3);
Qp = [];

syms Xu Xw Zu Zw Zwd Zq Mu Mw Mwd Mq

% True Parameters
param.Xu = -0.0212; param.Xw = 0.0466;
param.Zu = -0.2306; param.Zw = -0.6038; param.Zwd = -0.0341; param.Zq = -7.674;
param.Mu = 0.0; param.Mw = -0.0019; param.Mwd = -0.0002; param.Mq = -0.4381;

% Initial Parameter Estimates 

% 1 Unknown
param_1sig = .5;
xp0 = [param.Xu;param.Xw;param.Zu;param.Zw;param.Zwd;param.Zq;...
    param.Mu+0.01;param.Mw;param.Mwd;param.Mq].*(1+param_1sig*randn(np,1));

Pp0 = diag(([param.Xu param.Xw param.Zu param.Zw param.Zwd param.Zq ...
    param.Mu+0.01 param.Mw param.Mwd param.Mq]*param_1sig).^2);


syms xi zi u w q theta

xs = [xi zi u w q theta];
xp = [Xu Xw Zu Zw Zwd Zq Mu Mw Mwd Mq];
x = [xs xp];

fs = [ (u+u0)*cos(theta+Theta0) + w*sin(theta*Theta0);...
    -(u+u0)*sin(theta+Theta0) + w*cos(theta*Theta0);...
    Xu*u + Xw*w + 0 + -g0*cos(Theta0)*theta;...
    Zu/(1-Zwd)*u + Zw/(1-Zwd)*w + (u0+Zq)/(1-Zwd)*q + -g0*sin(Theta0)/(1-Zwd)*theta;...
    (Mu+Mwd*Zu/(1-Zwd))*u + (Mw+Mwd*Zw/(1-Zwd))*w + (Mq+(u0+Zq)*Mwd/(1-Zwd))*q + -Mwd*g0*sin(Theta0)/(1-Zwd)*theta;...
    0 + 0 + q + 0];

fp = zeros(np,1);

fout(xi,zi,u,w,q,theta,Xu,Xw,Zu,Zw,Zwd,Zq,Mu,Mw,Mwd,Mq) = [fs;fp];

jac(xi,zi,u,w,q,theta,Xu,Xw,Zu,Zw,Zwd,Zq,Mu,Mw,Mwd,Mq) = jacobian(fout,x);

jac = matlabFunction(jac);
fout = matlabFunction(fout);

param.jac = jac;
param.fout = fout;
param.Theta0 = Theta0;
param.u0 = u0;
param.g0 = g0;

dt = 0.1;
t=0:dt:40;
ns=6;nt=length(t);
AoA0 = 1; %rad

num_flights = 1;
for fl=1:num_flights
    
    if fl==1 % First Flight
        xs0_true=[0; -1000; 0;0;0.1;.05];
        clr = [0 0.4470 0.7410];
    end
    if fl==2 % Second Flight
        xs0_true=[0; -1000; 0;1;-0.1;-.1];
        clr = [0.4940 0.1840 0.5560];
    end
    %%%%% Truth Dynamics %%%%%
    
    %Xclean=zeros(ns,nt);Xclean(:,1)=xs0_true;
    Xnoisy=zeros(ns,nt);Xnoisy(:,1)=xs0_true;
    
    Qs=diag([.01^2,.01^2,.001^2]*dt/1); Gs=zeros(ns,3); Gs(3,1)=1; Gs(4,2)=1; Gs(5,3)=1;
    w=randn(length(Qs),nt).*sqrt(diag(Qs));
    for k=1:(nt-1)
%         Xtmp=predict_statetrue(Xclean(:,k),param,dt);
%         Xclean(:,k+1)=Xtmp(1:ns);
        
        Xtmp=predict_statetrue(Xnoisy(:,k),param,dt);
        Xnoisy(:,k+1)=Xtmp(1:ns) + Gs*w(:,k);
    end
    
    figure
    subplot(2,1,1)
    plot(t,Xnoisy(3,:)/u0);
    hold on
    plot(t,Xnoisy(4,:)/u0);
    plot(t,Xnoisy(5,:));
    plot(t,Xnoisy(6,:));
    legend('u/u_0','w/u_0','q rad/s','\theta rad')
    xlabel('Time [s]')
    ylabel('State');
    grid minor
    subplot(2,1,2)
    plot(-Xnoisy(1,:),-Xnoisy(2,:))
    set(gcf,'color','w');
    xlabel('-x_i [ft]');
    ylabel('-z_i [ft]');
    grid minor
     
%     figure
%     plot(-Xnoisy(1,:),-Xnoisy(2,:))
%     axis equal

    % Initial State Estimates
    state_1sig = 0.05;
    xs0 = xs0_true.*(1+state_1sig*randn(ns,1));
    Ps0 = 4*diag((state_1sig*[10 1000 1 1 .1 .1]).^2);

    %%%%% Sensor Measurment %%%%%%
    R=diag([3^2 3^2 .1^2 .1^2]);
    v=randn(length(diag(R)),nt).*sqrt(diag(R));
    Z=[Xnoisy(1,:);Xnoisy(2,:);Xnoisy(5,:);Xnoisy(6,:)]+v;
    
    %Extended Kalman Filter (EKF)
    
    % Combine
    G = [Gs;Gp];
    if isempty(Qp)
        Q=Qs;
    else
        Q = diag(Qs,Qp);
    end
    
    x0 = [xs0; xp0];
    P0 = diag([diag(Ps0);diag(Pp0)]);
    n=ns+np;
    
    % Measurement
    H = zeros(4,n);
    H(1,1) = 1; H(2,2)=1; H(3,5)=1; H(4,6)=1;
    xhat1p=x0;P1p(1:n,1:n,1)=P0;
    xhat1u=x0;P1u(1:n,1:n,1)=P0;
    
    for k=1:(nt-1)
        %predict state
        xhat1p(:,k+1)=predict_stateparam2(xhat1u(:,k),param,dt);
        
        %predict covariance
        [F]=getF_stateparam2(xhat1u(:,k),param,dt);
        P1p(1:n,1:n,k+1) = F*P1u(1:n,1:n,k)*F' + G*Q*G';
        
        % Kalman Gain
        K = P1p(1:n,1:n,k+1)*H'/(H*P1p(1:n,1:n,k+1)*H' + R);
        
        % Update
        xhat1u(:,k+1) = xhat1p(:,k+1) + K *(Z(:,k+1) - H*xhat1p(:,k+1));
        P1u(1:n,1:n,k+1) = (eye(n)-K*H)*P1p(1:n,1:n,k+1)*(eye(n)-K*H)' + K*R*K';
    end
    
    figure(2)
    subplot(3,2,1)
    statePlot(1,1,Xnoisy,xhat1u,t,clr,P1u,Z);
    ylabel('X_i')
    subplot(3,2,2)
    statePlot(2,2,Xnoisy,xhat1u,t,clr,P1u,Z);
    ylabel('Y_i')
    subplot(3,2,3)
    statePlot(3,2,Xnoisy,xhat1u,t,clr,P1u);
    ylabel('u')
    subplot(3,2,4)
    statePlot(4,2,Xnoisy,xhat1u,t,clr,P1u);
    ylabel('w')
    subplot(3,2,5)
    statePlot(5,3,Xnoisy,xhat1u,t,clr,P1u,Z);
    ylabel('q')
    ylim([-0.1 0.1]);
    subplot(3,2,6)
    p_obj_frwd = lastStatePlot(6,4,Xnoisy,xhat1u,t,clr,P1u,Z);
    ylabel('\theta')
    ylim([-0.1 0.1]);
    
    figure(3)
    subplot(2,5,1)
    paramPlot(7,param.Xu,xhat1u,t,clr);
    ylabel('X_u');
    subplot(2,5,2)
    paramPlot(8,param.Xw,xhat1u,t,clr);
    ylabel('X_w'); 
    subplot(2,5,3)
    paramPlot(9,param.Zu,xhat1u,t,clr);
    ylabel('Z_u'); 
    subplot(2,5,4)
    paramPlot(10,param.Zw,xhat1u,t,clr);
    ylabel('Z_w'); 
    subplot(2,5,5)
    paramPlot(11,param.Zwd,xhat1u,t,clr);
    ylabel('Z_wd');
    subplot(2,5,6)
    paramPlot(12,param.Zq,xhat1u,t,clr);
    ylabel('Z_q');
    subplot(2,5,7)
    paramPlot(13,param.Mu,xhat1u,t,clr);
    ylabel('M_u'); 
    subplot(2,5,8)
    paramPlot(14,param.Mw,xhat1u,t,clr);
    ylabel('M_w'); 
    subplot(2,5,9)
    paramPlot(15,param.Mwd,xhat1u,t,clr);
    ylabel('M_{wd}'); 
    subplot(2,5,10)
    p_obj_p_frwd = lastParamPlot(16,param.Mq,xhat1u,t,clr);
    ylabel('M_q'); xlabel('Time [s]');
    
    
    %% Smoothing
    
    % Kalman Smoother
    xhat1s(:,nt)=xhat1u(:,k+1);P1s(1:n,1:n,nt)=P1u(1:n,1:n,k+1);
    for k=(nt-1):-1:1
        [F]=getF_stateparam2(xhat1s(:,k+1),param,dt);
        Ks = P1u(1:n,1:n,k)*F'/(P1p(1:n,1:n,k+1));
        xhat1s(:,k)=xhat1u(:,k)+Ks*(xhat1s(:,k+1)-xhat1p(:,k+1));
        P1s(1:n,1:n,k)=P1u(1:n,1:n,k)-Ks*(P1p(1:n,1:n,k+1)-P1s(1:n,1:n,k+1));   
    end
    
    % Parameter Estimate Stays Constant
    xp0 = xhat1s(7:n,1);
    Pp0 = P1s(7:n,7:n,1);
    
    if fl==1 % First Flight
        clr = [0.8500 0.3250 0.0980];
    end
    if fl==2 % Second Flight
        clr = [0.9290 0.6940 0.1250];
    end
    
    figure(2)
    subplot(3,2,1)
    statePlot(1,1,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('x_i [ft]'); ylim(2.5*[-1 1]);
    subplot(3,2,2)
    statePlot(2,2,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('z_i [ft]'); ylim(5*[-1 1]);
    subplot(3,2,3)
    statePlot(3,2,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('u [ft/s]'); ylim(1.5*[-1 1]);
    subplot(3,2,4)
    statePlot(4,2,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('w [ft/s]'); ylim(12*[-1 1]);
    subplot(3,2,5)
    statePlot(5,3,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('q [rad/s]'); ylim(0.06*[-1 1]);
    xlabel('Time [s]');
    subplot(3,2,6)
    p_obj_smth = lastStatePlot(6,4,Xnoisy,xhat1s,t,clr,P1s);
    ylabel('\theta [rad]'); ylim(0.055*[-1 1]);
    xlabel('Time [s]');
   
    legend([p_obj_frwd.err p_obj_frwd.cov p_obj_smth.err p_obj_smth.cov p_obj_frwd.meas],'EKF Error','EKF Cov','KS Error','KS Cov','Measurements');
    
    figure(3)
    subplot(2,5,1)
    paramPlot(7,param.Xu,xhat1s,t,clr);
    ylabel('X_u');
    subplot(2,5,2)
    paramPlot(8,param.Xw,xhat1s,t,clr);
    ylabel('X_w'); 
    subplot(2,5,3)
    paramPlot(9,param.Zu,xhat1s,t,clr);
    ylabel('Z_u'); 
    subplot(2,5,4)
    paramPlot(10,param.Zw,xhat1s,t,clr);
    ylabel('Z_w'); 
    subplot(2,5,5)
    paramPlot(11,param.Zwd,xhat1s,t,clr);
    ylabel('Z_wd'); 
    subplot(2,5,6)
    paramPlot(12,param.Zq,xhat1s,t,clr);
    ylabel('Z_q'); xlabel('Time [s]');
    subplot(2,5,7)
    paramPlot(13,param.Mu,xhat1s,t,clr);
    ylabel('M_u'); xlabel('Time [s]');
    subplot(2,5,8)
    paramPlot(14,param.Mw,xhat1s,t,clr);
    ylabel('M_w'); xlabel('Time [s]');
    subplot(2,5,9)
    paramPlot(15,param.Mwd,xhat1s,t,clr);
    ylabel('M_{wd}'); xlabel('Time [s]');
    subplot(2,5,10)
    p_obj_p_smth = lastParamPlot(16,param.Mq,xhat1s,t,clr);
    ylabel('M_q'); xlabel('Time [s]');

    legend([p_obj_p_frwd.est p_obj_p_smth.est p_obj_p_smth.truth],'EKF Error','KS Error','Truth');

    
    tableOutEKF = produceTableState(t,xhat1u,Xnoisy);
    tableOutKS = produceTableState(t,xhat1s,Xnoisy);
    
%     close all
    [tableOutEKF, tableOutKS] = produceTableParam(t,xhat1u,xhat1s,param);
    
end

function [tableOutKF, tableOutS] = produceTableParam(t,xhatu,xhats,param)
    pn = {'Xu', 'Xw', 'Zu', 'Zw', 'Zwd', 'Zq', 'Mu', 'Mw', 'Mwd', 'Mq'};
    
     for i=1:10
         if i==7
             addThis = 0.01;
         else
             addThis =0;
         end
        tableEntryKF = num2str(abs((xhatu(i+6,end)-param.(pn{i})-addThis)/(param.(pn{i})+addThis))*100,'%2.1f');
        if i==1
            tableOutKF = tableEntryKF;
        else
           tableOutKF = [tableOutKF ' & ' tableEntryKF];
        end
        
        tableEntryS = num2str(abs((xhats(i+6,1)-param.(pn{i})-addThis)/(param.(pn{i})+addThis))*100,'%2.1f');
        
        if i==1
            tableOutS = tableEntryS;
        else
            tableOutS = [tableOutS ' & ' tableEntryS];
        end
     end
end

function tableOut = produceTableState(t,xhat,Xtrue)

for i=1:6
    tableEntry = num2str(std(xhat(i,:)-Xtrue(i,:)),'%5.2E');
    if i==1
        tableOut = tableEntry;
    else
        tableOut = [tableOut ' & ' tableEntry];
    end
end
end

function statePlot(iix,iim,Xtrue,xhat,t,clr,P,Z)
hold on
plot(t,(xhat(iix,:)-Xtrue(iix,:)),'Color',clr);
if nargin>6
    plot(t, - 2*sqrt(real(squeeze(abs(P(iix,iix,:)))))','Color',clr,'LineStyle','--');
    plot(t, 2*sqrt(real(squeeze(abs(P(iix,iix,:)))))','Color',clr,'LineStyle','--');
end
if nargin > 7
    plot(t,(Z(iim,:)-Xtrue(iix,:)),'.','MarkerSize',1)
end
grid minor
set(gcf,'color','w');
end

function p_obj = lastStatePlot(iix,iim,Xtrue,xhat,t,clr,P,Z)
hold on
p_obj.err = plot(t,(xhat(iix,:)-Xtrue(iix,:)),'Color',clr);
if nargin>6
    p_obj.cov = plot(t, - 2*sqrt(real(squeeze(abs(P(iix,iix,:)))))','Color',clr,'LineStyle','--');
    plot(t, 2*sqrt(real(squeeze(abs(P(iix,iix,:)))))','Color',clr,'LineStyle','--');
end
if nargin > 7
    p_obj.meas = plot(t,(Z(iim,:)-Xtrue(iix,:)),'.','MarkerSize',1);
end
grid minor
set(gcf,'color','w');
end

function paramPlot(iix,paramTrue,xhat,t,clr,P)
hold on
plot(t,xhat(iix,:),'Color',clr);
plot(t,paramTrue*ones(length(t),1),'k');
if nargin>5
    plot(t, xhat(iix,:) - 2*sqrt(squeeze(abs(P(iix,iix,:))))','Color',clr,'LineStyle','--');
    plot(t, xhat(iix,:) + 2*sqrt(squeeze(P(iix,iix,:)))','Color',clr,'LineStyle','--');
end

grid minor
set(gcf,'color','w');
end

function p_obj = lastParamPlot(iix,paramTrue,xhat,t,clr,P)
hold on
p_obj.est = plot(t,xhat(iix,:),'Color',clr);
p_obj.truth = plot(t,paramTrue*ones(length(t),1),'k');

if nargin>5
    p_obj.cov = plot(t, xhat(iix,:) - 2*sqrt(squeeze(abs(P(iix,iix,:))))','Color',clr,'LineStyle','--');
    plot(t, xhat(iix,:) + 2*sqrt(squeeze(P(iix,iix,:)))','Color',clr,'LineStyle','--');
end


grid minor
set(gcf,'color','w');
end


