printf "deleting old *.o files\n"
find . -maxdepth 1 -type f -iname \*.o -delete
echo make
make -f Makefile
./tp tests/00_parametros
./tp tests/01_always/always.cfg tests/01_always/one.cap > myOuts/test1out
./tp tests/02_all_of/all_of.cfg tests/02_all_of/multiple_packets.cap > myOuts/test2out
./tp tests/03_any_of/any_of.cfg tests/03_any_of/multiple_packets.cap > myOuts/test3out
./tp tests/04_by_endpoint/3to4.cfg tests/04_by_endpoint/multiple_packets.cap > myOuts/test4out
./tp tests/05_threshold/elite_4_or_more.cfg tests/05_threshold/elite.cap > myOuts/test5out
./tp tests/06_fragmented_ordered/spoon.cfg tests/06_fragmented_ordered/packet_fragmented.cap > myOuts/test6out
./tp tests/07_fragmented_unordered/spoon.cfg tests/07_fragmented_unordered/packet_fragmented.cap > myOuts/test7out
./tp tests/08_multiples_matches/rules.cfg tests/08_multiples_matches/packets.cap > myOuts/test8out
./tp tests/09_multiple_captures/spoon.cfg tests/09_multiple_captures/cap0.cap tests/09_multiple_captures/cap1.cap tests/09_multiple_captures/cap2.cap tests/09_multiple_captures/cap3.cap tests/09_multiple_captures/cap4.cap > myOuts/test9out

printf "\nDiffs:\n"
printf "\ntest 1:\n"
diff tests/01_always/output/__stdout__ myOuts/test1out
printf "\ntest 2:\n"
diff tests/02_all_of/output/__stdout__ myOuts/test2out
printf "\ntest 3:\n"
diff tests/03_any_of/output/__stdout__ myOuts/test3out
printf "\ntest 4:\n"
diff tests/04_by_endpoint/output/__stdout__ myOuts/test4out
printf "\ntest 5:\n"
diff tests/05_threshold/output/__stdout__ myOuts/test5out
printf "\ntest 6:\n"
diff tests/06_fragmented_ordered/output/__stdout__ myOuts/test6out
printf "\ntest 7:\n"
diff tests/07_fragmented_unordered/output/__stdout__ myOuts/test7out
printf "\ntest 8:\n"
diff tests/08_multiples_matches/output/__stdout__ myOuts/test8out
printf "\ntest 9:\n"
diff tests/09_multiple_captures/output/__stdout__ myOuts/test9out
