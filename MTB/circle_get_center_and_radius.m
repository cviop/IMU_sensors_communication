

% syms Hx;
% syms Sx;
% syms Hy;
% syms Sy;
% syms Hz;
% syms Sz;

% syms Mx Hx Sx My Hy Sy Mz Hz Sz const

syms x1 y1 x2 y2 x3 y3 R xc yc
eqn1 = (x1-xc)^2+(y1-yc)^2==R^2;
eqn2 = (x2-xc)^2+(y2-yc)^2==R^2;
eqn3 = (x3-xc)^2+(y3-yc)^2==R^2;

eqn = [eqn1, eqn2, eqn3];



[x y rr] = solve(eqn, [xc yc R]);
vars = [x1, x2, x3, y1, y2, y3];



subs(x,vars , [-1 0 1 0 2 0])
subs(y,vars , [-1 0 1 0 2 0])


% solve((Mx*Hx+Sx)^2+(My*Hy+Sy)^2+(Mz*Hz+Sz)^2-const^2 == 0, Hx)

%%[x y] = solve('(x1-xc)^2+(y1-yc)^2=R^2 ,(x2-xc)^2+(y2-yc)^2=R^2')

x1 = -1;
x2 = 0;
x3 = 1;

y1 = 0;
y2 = 2;
y3 = 0;

xovy = (x1^2*y2 - x1^2*y3 - x2^2*y1 + x2^2*y3 + x3^2*y1 - x3^2*y2 + y1^2*y2 - y1^2*y3 - y1*y2^2 + y1*y3^2 + y2^2*y3 - y2*y3^2)/(2*(x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2));
xovy2 = (x1^2*y2 - x1^2*y3 - x2^2*y1 + x2^2*y3 + x3^2*y1 - x3^2*y2 + y1^2*y2 - y1^2*y3 - y1*y2^2 + y1*y3^2 + y2^2*y3 - y2*y3^2)/(2*(x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2));


yovy = (- x1^2*x2 + x1^2*x3 + x1*x2^2 - x1*x3^2 + x1*y2^2 - x1*y3^2 - x2^2*x3 + x2*x3^2 - x2*y1^2 + x2*y3^2 + x3*y1^2 - x3*y2^2)/(2*(x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2));
yovy2 =  (- x1^2*x2 + x1^2*x3 + x1*x2^2 - x1*x3^2 + x1*y2^2 - x1*y3^2 - x2^2*x3 + x2*x3^2 - x2*y1^2 + x2*y3^2 + x3*y1^2 - x3*y2^2)/(2*(x1*y2 - x2*y1 - x1*y3 + x3*y1 + x2*y3 - x3*y2));


