function simulateMPC(xinit,K,mu)
  
  dt=.01;
  x=xinit;
  xstore = NaN*zeros(2,10000);
  k=1;
  u=1;
  
  n=4;
  while (norm(x) > 0.001) && (k<2000)
    xstore(:,k) = x;
    
    
    %TODO linearisation en x et t
    Ar=[(1-mu)*u, 1; 1, -4*(1-mu)*u];
    Br=[mu+(1-mu)*x(1); mu-4*(1-mu)*x(2)];
    A=eye(2, 2)+dt*Ar;
    B=dt*Br;
    
    %vecteur d'entrées
    U=[u,u,u,u]';
    H=eye(n,n)*2;
    
    %TODO écrire les matrices de la commande prédictive linéaire
    Z=0*B;
    Aqp=[A; A^2; A^3; A^4];
    Bqp=[B,     Z,     Z,   Z;
         A*B,   B,     Z,   Z;
         A^2*B, A*B,   B,   Z;
         A^3*B, A^2*B, A*B, B ];
      
    %TODO avec une pseudo inverse, calculer le vecteur d'entrées
    pseudoinv=inv(Bqp'*Bqp)*Bqp';
    U=-pseudoinv*Aqp*x;
    
    
    if size(K)==0
      u=U(1);
    else
      u=-K*x;
    end
    
    if (u > 2)
      u=2;
    elseif (u<-2)
      u=-2;
    end
    
    %simu avec euler
    x1=x(1);
    x2=x(2);
    x(1) = x1 + dt*(x2 + u*(mu + (1-mu)*x1));
    x(2) = x2 + dt*(x1+u*(mu-4*(1-mu)*x2));
    
    k++;
  end
  
  if norm(x) < 0.01
    plot(xstore(1,:),xstore(2,:),'+');
  else
    disp("fail!")
    plot(xstore(1,:),xstore(2,:),'+');
  end
endfunction
