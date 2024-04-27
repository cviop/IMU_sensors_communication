function [Winv,V,B] = magcal_symetric(d)

    
x=d(:,1);
y=d(:,2);
z=d(:,3);



    d = [...
        x.*x, ...
        2*x.*y, ...
        2*x.*z, ...
        y.*y, ...
        2*y.*z, ...
        z.*z, ...
        x, ...
        y, ...
        z, ...
        ones(size(x))];

    beta = smallestEigenVector(d);

    A = beta([1 2 3; 2 4 5; 3 5 6]); %make symmetric
    dA = det(A);

    if dA < 0
        A = -A;
        beta = -beta;
        dA = -dA; %Compensate for -A.
    end

    V = -0.5*(A\beta(7:9)); %hard iron offset

    B = sqrt(abs(sum([...
        A(1,1)*V(1)*V(1), ...
        2*A(2,1)*V(2)*V(1), ...
        2*A(3,1)*V(3)*V(1), ...
        A(2,2)*V(2)*V(2), ...
        2*A(3,2)*V(2)*V(3), ...
        A(3,3)*V(3)*V(3), ...
        -beta(end)] ...
    )));

    V = V.';
    % We correct Winv and B by det(A) because we don't know which has the
    % gain. By convention, normalize A.

    det3root = nthroot(dA,3);
    det6root = sqrt(det3root);
    Winv = sqrtm(A./det3root);
    B = B./det6root;
    

end





function beta = smallestEigenVector(d)

% Use SVD to compute the eigenvalues and eigenvectors.
[~,~,V] = svd(d,'econ');
beta = V(:,end); % Solution has smallest eigenvalue.


end
