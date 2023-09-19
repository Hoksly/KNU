data = load("f6.txt")

time_total = 5
T = 0.01
t = 0:T:time_total
N = length(data)

#plot(data), grid
#figure

# Custom implementation of FT
fourier_func = zeros(1, N)


for k = 1:N
  for j = 1:N
    fourier_func(k) = fourier_func(k) + 1/N * data(j) * exp(1)^ (-1i * 2 * pi * k * j / N);
  endfor
endfor



#plot(abs(fourier_func)), grid
#figure


# Cutting half
t_length = length(t)
f = 0:T:round(t_length/2)*T

#plot(f, abs(fourier_func(1:round(t_length/2)+1))), grid
#figure
% Assuming 'fourier_func' contains the values you want to analyze


n = length(fourier_func);

% Initialize variables to store extrema and their indices
extrema = [];
extrema_indices = [];

% Perform 5-point analysis on half of the plot
for i = 3: (n/2 + 1)
    if fourier_func(i) > fourier_func(i-2) && fourier_func(i) > fourier_func(i-1) && fourier_func(i) > fourier_func(i+1) && fourier_func(i) > fourier_func(i+2)
        % Found a peak
        extrema = [extrema, fourier_func(i)];
        extrema_indices = [extrema_indices, i];
    end
end

% Display the extrema and their indices
disp('Extrema values:');
disp(extrema);
disp('Indices of extrema:');
disp(extrema_indices);

extremum = extrema_indices(1)
disp(extremum)




fourier_func = abs(fourier_func);

extremums = zeros(2, 1);
df = 0.2;

for i = 1:length(extrema_indices)
    extremum = extrema_indices(i) * df;
    disp(['Found peak: ' num2str(i)]);
    extremums(i) = extremum;
end

sin_f = sin(2*pi*extremum(1)*df*t)


A = [sum(t.^6), sum(t.^5), sum(t.^4), sum(sin_f .* t.^3), sum(t.^3);
    sum(t.^5), sum(t.^4), sum(t.^3), sum(sin_f .* t.^2), sum(t.^2);
    sum(t.^4), sum(t.^3), sum(t.^2), sum(sin_f .* t), sum(t);
    sum(sin_f .* t.^3), sum(sin_f .* t.^2), sum(sin_f .* t), sum(sin_f .* sin_f), sum(N * sin_f);
    sum(t.^3), sum(t.^2), sum(t), sum(N * sin_f), N;]

c = [sum(data .* t.^3), sum(data .* t.^2), sum(data .* t), sum(data .* sin_f), sum(data)];

a = A \ c'; % This will solve for 'a' using matrix division.

app_func = a(1).*t.^3 + a(2).*t.^2 + a(3).*t + a(4).*sin_f + a(5)

plot(t, app_func), grid
figure

error_value = sum((app_func - data).^2)
