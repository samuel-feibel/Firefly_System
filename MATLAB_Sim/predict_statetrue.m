function Xkp1=predict_statetrue(Xk,param,dt)

% Ap=param.Ap;
Theta0 = param.Theta0;
u0 = param.u0;
g0 = param.g0;

Xu = param.Xu;
Xw = param.Xw;
Zu = param.Zu;
Zw = param.Zw;
Zwd = param.Zwd;
Zq = param.Zq;
Mu = param.Mu;
Mw = param.Mw;
Mwd = param.Mwd;
Mq = param.Mq;


[~,Xout] = ode45(@odefun,[0 dt],Xk);
Xkp1 = Xout(end,:)';

    function A = odefun(t,Xk)
        
        % States

        u = Xk(3);
        w = Xk(4);
        q = Xk(5);
        theta = Xk(6);
        % Parameters
        
        %         A = [ (u+u0)*cos(theta+Theta0) + w*sin(theta*Theta0);...
        %             -(u+u0)*sin(theta+Theta0) + w*cos(theta*Theta0);...
        %             Ap*Xk(3:6)];
        
        A = [ (u+u0)*cos(theta+Theta0) + w*sin(theta*Theta0);...
            -(u+u0)*sin(theta+Theta0) + w*cos(theta*Theta0);...
            Xu*u + Xw*w + 0 + -g0*cos(Theta0)*theta;...
            Zu/(1-Zwd)*u + Zw/(1-Zwd)*w + (u0+Zq)/(1-Zwd)*q + -g0*sin(Theta0)/(1-Zwd)*theta;...
            (Mu+Mwd*Zu)/(1-Zwd)*u + (Mw+Mwd*Zw)/(1-Zwd)*w + (Mq+u0*Mwd)/(1-Zwd)*q + -Mwd*g0*sin(Theta0)/(1-Zwd)*theta;...
            0 + 0 + q + 0];
          
    end

% Xkp1 = Xk + dt*A;

end