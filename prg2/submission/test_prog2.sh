#!/bin/sh

WORKDIR=${TMPDIR:-/tmp}/test_prog2.$$
mkdir -p $WORKDIR

if [ -x ./test_prog2 ]; then
  ./test_prog2
else
  echo test_prog2 does not exist.
fi

if [ -x ./topwords ]; then

cat << EOF > $WORKDIR/correct.$$
and	5
cheer	5
dame	5
for	2
her	8
loyal	2
name	2
notre	5
of	2
old	2
rah	2
sons	2
the	4
to	3
true	2
we	2
while	1
will	4
win	1
with	1
EOF

./topwords victory.txt | LC_ALL=C sort > $WORKDIR/output.$$
if diff -q $WORKDIR/output.$$ $WORKDIR/correct.$$; then
  echo topwords passed.
else
  echo topwords failed.
  diff -y $WORKDIR/output.$$ $WORKDIR/correct.$$
fi

cat << EOF > $WORKDIR/correct.$$
"	1023
,	3932
.	1265
:	426
;	323
a	366
and	984
as	315
he	421
his	398
i	723
in	513
me	315
my	347
of	703
that	650
the	1792
thou	348
to	739
with	389
EOF

./topwords inferno.txt | LC_ALL=C sort > $WORKDIR/output.$$
if diff -q $WORKDIR/output.$$ $WORKDIR/correct.$$; then
  echo topwords passed.
else
  echo topwords failed.
  diff -y $WORKDIR/output.$$ $WORKDIR/correct.$$
fi

cat << EOF > $WORKDIR/correct.$$
0.397927
EOF

./cosine victory.txt almamater.txt > $WORKDIR/output.$$
if diff -q $WORKDIR/output.$$ $WORKDIR/correct.$$; then
  echo cosine passed.
else
  echo cosine failed.
  diff -y $WORKDIR/output.$$ $WORKDIR/correct.$$
fi

fi
