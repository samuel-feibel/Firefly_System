function [x,P]=SPF(fstate,x,uk,ukp1,P,hmeas,z,Q,R,delt)
% SPF   Sigma Point Filter for nonlinear dynamic systems
% [x, P] = SPF(f,x,P,h,z,Q,R) returns state estimate, x and state covariance, P
% for nonlinear dynamic system (for simplicity, noises are assumed as additive):
%           x_k+1 = f(x_k) + w_k
%           z_k   = h(x_k) + v_k
% where w ~ N(0,Q) meaning w is gaussian noise with covariance Q
%       v ~ N(0,R) meaning v is gaussian noise with covariance R
% Inputs:   f: function handle for f(x)
%           x: "a priori" state estimate
%           P: "a priori" estimated state covariance
%           h: fanction handle for h(x)
%           z: current measurement
%           Q: process noise covariance
%           R: measurement noise covariance
% Output:   x: "a posteriori" state estimate
%           P: "a posteriori" state covariance
%

% Based off of:
% Reference: Julier, SJ. and Uhlmann, J.K., Unscented Filtering and
% Nonlinear Estimation, Proceedings of the IEEE, Vol. 92, No. 3,
% pp.401-422, 2004.
% By Yi Cao at Cranfield University, 04/01/2008


L=numel(x);                                 %numer of states
m=numel(z);                                 %numer of measurements
alpha=1e-3;                                 %default, tunable
ki=0;                                       %default, tunable
beta=2;                                     %default, tunable
lambda=alpha^2*(L+ki)-L;                    %scaling factor
c=L+lambda;                                 %scaling factor
Wm=[lambda/c 0.5/c+zeros(1,2*L)];           %weights for means
Wc=Wm;
Wc(1)=Wc(1)+(1-alpha^2+beta);               %weights for covariance
c=sqrt(c);
X=sigmas(x,P,c);                            %sigma points around x
% Predict State Distribution
[x1,X1,P1,X2]=ut_f(fstate,X,uk,Wm,Wc,L,Q,delt);          %unscented transformation of process

% Predicted Measurement Distribution
[z1,Z1,P2,Z2]=ut_h(hmeas,X1,ukp1,Wm,Wc,m,R);       %unscented transformation of measurments


P12=X2*diag(Wc)*Z2';                        %transformed cross-covariance
K=P12*inv(P2);
x=x1+K*(z-z1);                              %state update
P=P1-K*P12';                                %covariance update

    function [y,Y,P,Y1]=ut_f(f,X,u,Wm,Wc,n,R,delt)
        %Unscented Transformation
        %Input:
        %        f: nonlinear map
        %        X: sigma points
        %        u: inputs
        %       Wm: weights for mean
        %       Wc: weights for covraiance
        %        n: numer of outputs of f
        %        R: additive covariance
        %       dt: time span
        %Output:
        %        y: transformed mean
        %        Y: transformed sampling points
        %        P: transformed covariance
        %       Y1: transformed deviations
        
        LL=size(X,2);
        y=zeros(n,1);
        Y=zeros(n,LL);
        for k=1:LL
            Y(:,k)=f(X(:,k),u,delt);
            y=y+Wm(k)*Y(:,k);
        end
        Y1=Y-y(:,ones(1,LL));
        P=Y1*diag(Wc)*Y1'+R;
    end

    function [y,Y,P,Y1]=ut_h(f,X,u,Wm,Wc,n,R)
        %Unscented Transformation
        %Input:
        %        f: nonlinear map
        %        X: sigma points
        %        u: inputs
        %       Wm: weights for mean
        %       Wc: weights for covraiance
        %        n: numer of outputs of f
        %        R: additive covariance
        %Output:
        %        y: transformed mean
        %        Y: transformed sampling points
        %        P: transformed covariance
        %       Y1: transformed deviations
        
        LL=size(X,2);
        y=zeros(n,1);
        Y=zeros(n,LL);
        for k=1:LL
            Y(:,k)=f(X(:,k),u);
            y=y+Wm(k)*Y(:,k);
        end
        Y1=Y-y(:,ones(1,LL));
        P=Y1*diag(Wc)*Y1'+R;
    end

    function X=sigmas(x,P,c)
        %Sigma points around reference point
        %Inputs:
        %       x: reference point
        %       P: covariance
        %       c: coefficient
        %Output:
        %       X: Sigma points
        
        A = c*chol(P)';
        Y = x(:,ones(1,numel(x)));
        X = [x Y+A Y-A];
    end
end




