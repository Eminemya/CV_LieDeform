% load_MR_raw    Load an image series in RAW 16-bit big-endian format from disk.
%    load_MR_raw(fname)
%
function im=load_MR_raw(fname)

fid=fopen(fname,'r');
raw=fread(fid,256*256*2,'unsigned char');
fclose(fid);

resh=reshape(raw,[2 256 256]);
im=(squeeze(256*resh(1,:,:)+resh(2,:,:)))';

