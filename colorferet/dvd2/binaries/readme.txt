Image files of the form *.ppm.bz2 can be decompressed into their
original *.ppm files using the program "bunzip2", which is part
of the "bzip2" package.

When run on a file, e.g. 00005_930831_pr.ppm.bz2, the program
creates a 00005_930831_pr.ppm and removes the compressed
version:
	% ls
	00005_930831_pr.ppm.bz2
	% bunzip2 00005_930831_pr.ppm.bz2
	% ls
	00005_930831_pr.ppm

The program accepts multiple files on its command line:
	% bunzip2 *.ppm.bz2
The number of files that such a wildcard expression can be 
expanded into is often limited by the command shells. Even 
recent Linux kernels limit the total size of a process'
command line arguments and environment variables to 131072 
bytes:
	% getconf ARG_MAX
	131072
If the command will fails to execute for that reason:
	% cd data/images/
	% bunzip2 */*.ppm.bz2
	/usr/bin/bunzip2: Argument list too long.
then break it up into multiple invocations:
	% bunzip2 *0/*.ppm.bz2
	% bunzip2 *1/*.ppm.bz2
	...
	% bunzip2 *9/*.ppm.bz2

The "bunzip2" binaries in this directory are from the official
"bzip2" website:
	http://sources.redhat.com/bzip2/
The programs on the webpage all had names beginning with "bzip2",
although the same program does both compression and decompression.
They were downloaded and renamed to begin with "bunzip2." Copy
the one for your architecture to a directory that gets searched 
automatically for commands, and rename it as just "bunzip2" (or
"bunzip2.exe" for Windows systems), e.g.:
	% cp bunzip2-102-x86-linux24 $HOME/bin/bunzip2

The following two binaries are the latest version of "bunzip2,"
1.0.2:
	bunzip2-102-x86-linux24
		PC, Linux 2.4.9 (Red Hat 7.2, x86), statically linked
	bunzip2-102-x86-win32.exe
		PC, Windows 95/98/ME/NT/2000/XP
		This program is for Windows systems that do not have
		Cygwin installed; it was compiled on a computer running
		Windows 2000 Service Pack 2 and may or may not work on
		Windows 95/98/ME/NT/XP

The following three binaries are a previous version of "bunzip2,"
1.0.0, and they are likely to work on the compressed files:
	bunzip2-100-sparc-solaris7
		Sun Sparc, Solaris 7, statically linked
	bunzip2-100-x86-cygwinb20.exe
		PC, Cygwin b20.1 on Windows 2000
	bunzip2-100-x86-win32.exe
		PC, Windows 95/98/NT/2000

The source code, if it is needed, is in a "tar" archive on each DVD:
	source/bzip2-1.0.2.tar
