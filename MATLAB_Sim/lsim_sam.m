function [tOut,xOut,uOut] = lsim_sam(A,B,K,u,t,x0)

u_prev = [0;0];
t_prev = 0;

xOut = NaN(length(x0),length(t));
uOut = NaN(2,length(t));
tOut = t;
xOut(:,1) = x0;
for i=2:length(t)

    u_curr = -K*xOut(:,i-1);
    
    delU = (u_curr-u_prev)/(t(i)-t(i-1));
    log = abs(delU)>60/.14;
    if any(log)
        u_curr(log) = u_prev(log) + sign(u_curr(log)).*60/.14*(t(i)-t(i-1));
    end
    u_prev = u_curr;
    
    u_system = interp1(t,u',t(i),'previous')';
    
    
    deriv = A*xOut(:,i-1)+B*u_curr + u_system;
    
    xOut(:,i) = xOut(:,i-1) + deriv*(t(i)-t(i-1));
    
    
    uOut(:,i) = u_curr;
    
    
    
    
end

xOut=xOut';


end

