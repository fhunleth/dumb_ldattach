# dumb_ldattach

This is an answer to my inability to only configure util-linux and Buildroot to
generate `ldattach`. One syscall wasn't worth it.

## Building from source

If cloning, run `./autgen.sh`. Building from an official release does not
require this step.

Then:

```
$ ./configure
$ make
$ make install
```

## License

I looked at the `util-linux` source and copy/pasted a few lines to create this.
It's GPL like the original.

