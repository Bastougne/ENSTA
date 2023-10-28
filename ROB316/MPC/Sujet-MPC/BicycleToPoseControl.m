function [ u ] = BicycleToPoseControl( xTrue,xGoal )
%Computes a control to reach a pose for bicycle
%   xTrue is the robot current pose : [ x y theta ]'
%   xGoal is the goal point
%   u is the control : [v phi]'

   Krho = 20;
   Kalpha = 15;
   Kbeta = -10;

   error = xGoal - xTrue;
   rho = norm( error(1:2) );
   atanVal = atan2( error(2), error(1) );
   alpha = AngleWrap( atanVal - xTrue(3) );
   beta = AngleWrap( xGoal(3) - atanVal );

   u(1) = Krho * rho;
   u(2) = Kalpha * alpha + Kbeta * beta;
end
