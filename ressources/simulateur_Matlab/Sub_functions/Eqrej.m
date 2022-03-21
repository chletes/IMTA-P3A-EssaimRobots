function [Ta, Ga]=eqrej(A,B,C,n1,tol);

% EQREJ.M  
%
% function [Ta, Ga]=eqrej(A,B,C,n1,tol);
%
% programme permettant la résolution des équations
% du rejet asymptotique :
%
%	A11*Ta - Ta*A22 + B1*Ga = A12
%	C1*Ta 			= C2
%
% paramètres d'entrée :
%	# A=[A11 A12 ; 0 A22]
%	# B=[B1 ; 0]
%	# C=[C1 , C2]
%	# n1 : nombre d'états commandables (taille de A11)
%
% bibliogr. : P.d.L. (1993) p274

if nargin == 4
    tol=1e-10;
end
[n,m]=size(B);
[p,n]=size(C);

A11=A(1:n1,1:n1);	A12=A(1:n1,n1+1:n);
A21=A(n1+1:n,1:n1);	A22=A(n1+1:n,n1+1:n);
B1=B(1:n1,:);
B2=B(n1+1:n,:);
C1=C(:,1:n1);		C2=C(:,n1+1:n);

if (max(max(abs(A21))) > tol)|(max(max(abs(B2))) > tol)
  error('le système doit être donné sous forme canonique de commandabilité')
end

vecA12=reshape(A12,n1*(n-n1), 1);
vecC2=reshape(C2,p*(n-n1),1);

I1=eye(n1,n1); I2=eye(n-n1,n-n1);
mat11=kron(I2,B1);			[lmat11,cmat11]=size(mat11);
mat12=kron(I2,A11)-kron(A22',I1); 	[lmat12,cmat12]=size(mat12);
mat22=kron(I2,C1);			[lmat22,cmat22]=size(mat22);
mat21=zeros(lmat22,cmat11);
mat = [ mat11	mat12
	    mat21	mat22 ];
    %rank(mat)
    %size(mat)
    %eig(mat'*mat)
x=mat\[vecA12 ; vecC2]; condmat=cond(mat);

if condmat>1/tol
  disp('Warning : mauvais conditionnement de mat')
end
vecGa=x(1:m*(n-n1));
vecTa=x(m*(n-n1)+1:(m+n1)*(n-n1));
Ga=reshape(vecGa,m,n-n1);
Ta=reshape(vecTa,n1,n-n1);
			
% validation des résultats
diff1=max(max(abs(A11*Ta-Ta*A22+B1*Ga-A12)));
diff2=max(max(abs(C1*Ta-C2)));

if (diff1 > tol) | (diff2 > tol)
  Ga=[]; Ta=[];
  error('Résultats faux')
end
