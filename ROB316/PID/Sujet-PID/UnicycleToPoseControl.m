function [ u ] = UnicycleToPoseControl( xTrue,xGoal )
%Computes a control to reach a pose for unicycle
%   xTrue is the robot current pose : [ x y theta ]'
%   xGoal is the goal point
%   u is the control : [v omega]'

    Krho = 15;
    Kalpha = 10;
    Kbeta = 20;
    alphaMax = 1.2;

    error = xGoal - xTrue;
    rho = norm( error(1:2) );
    alpha = AngleWrap( atan2( error(2), error(1) ) - xTrue(3) );

    if abs( alpha ) > alphaMax
        u(1) = 0;
    else
        u(1) = Krho * rho;
    endif

    if rho > 0.05
        u(2) = Kalpha * alpha;
    else
        u(2) = Kbeta * error(3);
    endif
end
