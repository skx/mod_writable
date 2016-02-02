all:
	apxs -i -a -c  mod_writable.c

clean:
	rm mod_writable.la  || true
	rm mod_writable.lo  || true
	rm mod_writable.slo || true
