% GET_SINCOS_BASIS             Make a set of basis images for
%                              smooth images
%
% b=get_sincos_basis(res,freqs)
%
% This function generates a set of sine and cosine functions in
% two-dimensions. 
%
% res    - The resolution of the basis images.
% perrow - This value says how many frequencies to include in the
%          set of basis functions. More frequencies result in more
%          images according to the following pattern:
%     
%          Number of frequencies             Number of basis images
%                 1                                     1
%                 2                                     9
%                 3                                    25
%                 N                                  (2N-1)^2

function b=get_sincos_basis(res,freqs)

k=1;
b(:,:,1)=ones(res,res);
k=k+1;

for i=2:freqs
  rowfreq=i-1;
  for y=1:res
    for x=1:res
      b(y,x,k)=cos(2*pi*y/res*rowfreq);
    end
  end
  k=k+1;
  for y=1:res
    for x=1:res
      b(y,x,k)=sin(2*pi*y/res*rowfreq);
    end
  end
  k=k+1;
  for y=1:res
    for x=1:res
      b(y,x,k)=cos(2*pi*x/res*rowfreq);
    end
  end
  k=k+1;
  for y=1:res
    for x=1:res
      b(y,x,k)=sin(2*pi*x/res*rowfreq);
    end
  end
  k=k+1;
end

  
for i=2:freqs
  rowfreq=i-1;
  for j=2:freqs
    colfreq=j-1;
    for y=1:res
      for x=1:res
	b(y,x,k)=cos(2*pi*y/res*rowfreq)*cos(2*pi*x/res*colfreq);
      end
    end
    k=k+1;
    for y=1:res
      for x=1:res
	if colfreq==0
  	  b(y,x,k)=cos(2*pi*y/res*rowfreq);
	else
   	  b(y,x,k)=cos(2*pi*y/res*rowfreq)*sin(2*pi*x/res*colfreq);
	end
	
      end
    end
    k=k+1;
    for y=1:res
      for x=1:res
	if rowfreq==0
  	  b(y,x,k)=                        cos(2*pi*x/res*colfreq);
	else
  	  b(y,x,k)=sin(2*pi*y/res*rowfreq)*cos(2*pi*x/res*colfreq);
	end
	
      end
    end
    k=k+1;
    for y=1:res
      for x=1:res
	if rowfreq==0 & colfreq==0
	  b(y,x,k)=1;
	else 
	  if rowfreq==0 
 	    b(y,x,k)=                       sin(2*pi*x/res*colfreq);
	  else 
	    if colfreq==0
	      b(y,x,k)=sin(2*pi*y/res*rowfreq);
	    else
     	      b(y,x,k)=sin(2*pi*y/res*rowfreq)*sin(2*pi*x/res*colfreq);
	    end
	  end
	end	
      end
    end
    k=k+1;
    
  end
end


