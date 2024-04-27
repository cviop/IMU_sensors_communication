function [Winv,V,B] = magcal_diag(x,y,z)




    d = [...
        x.*x, ...
        y.*y, ...
        z.*z, ...
        x, ...
        y, ...
        z, ...
        ones(size(x))];

    beta = smallestEigenVector(d);

    A = diag(beta(1:3));
    % Compute the determinant of A, a diagonal matrix.
    dA = beta(1)*beta(2)*beta(3);

    if dA < 0
        A = -A;
        beta = -beta;
        dA = -dA; %Compensate for -A.
    end
    V = -0.5*(beta(4:6)./beta(1:3)); %hard iron offset

    B = sqrt(abs(sum([...
        A(1,1)*V(1)*V(1), ...
        A(2,2)*V(2)*V(2), ...
        A(3,3)*V(3)*V(3), ...
        -beta(end)] ...
    )));
  

    % We correct Winv and B by det(A) because we don't know which has the
    % gain. By convention, normalize A.

    det3root = nthroot(dA,3);
    det6root = sqrt(det3root);
    Winv = sqrtm(A./det3root);
    B = B./det6root;
    V = V.'
    
function beta = smallestEigenVector(d)

% Use SVD to compute the eigenvalues and eigenvectors.
[~,~,V] = svd(d,'econ');
beta = V(:,end); % Solution has smallest eigenvalue.


end

end
