dt = 0.01;
T = 5;
t = 0:dt:T;
N = length(t)-1;

F1 = zeros(1, N+1);
F2 = zeros(1, N+1);
F3 = zeros(1, N+1);
u = ones(1, N+1);

K1 = 1;
K2 = 5;
K3 = 25;

for k = 1:N+1
	F1(k) = 1 - exp(-K1*t(k));
	F2(k) = 1 - exp(-K2*t(k));
    F3(k) = 1 - exp(-K3*t(k));
end

plot(t, u, 'g', t, F1, 'b--', t, F2, 'b-.', t, F3, 'b')
xlabel('Time (s)')
ylabel('Value')
axis([0 T 0 1.2])
legend('u', 'F (K = 1)', 'F (K = 5)', 'F (K = 25)')