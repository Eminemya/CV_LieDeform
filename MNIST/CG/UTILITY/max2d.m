function [rc,val]=max2d(a)

[rc,tval]=min2d(-a);
val= -tval;
