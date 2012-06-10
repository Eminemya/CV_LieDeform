function y=logsum(arr)
%in [log(a),log(b),...]
%out log(a+b+c)

mm=max(arr);

y=log(sum(exp(arr-mm)))+mm;

end
