all: cp_splice cp_normal tee sendfile

cp_slice:cp_splice.c
	gcc cp_splice.c -o cp_splice -O2 -g
cp_normal:cp_normal.c
	gcc cp_normal.c -o cp_normal -O2 -g
tee:tee.c
	gcc tee.c -o tee -O2 -g
sendfile:sendfile.c
	gcc sendfile.c -o sendfile -O2 -g
clean:
	rm tee cp_splice cp_normal gocp/gocp