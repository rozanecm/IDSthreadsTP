echo make
make -f Makefile
echo test 0:
./tp tests/00_parametros 
echo test 1:
./tp tests/01_always/always.cfg tests/01_always/one.cap
echo test 2:
./tp tests/02_all_of/all_of.cfg tests/02_all_of/multiple_packets.cap
echo test 3:
./tp tests/03_any_of/any_of.cfg tests/03_any_of/multiple_packets.cap 
echo test 4:
./tp tests/04_by_endpoint/3to4.cfg tests/04_by_endpoint/multiple_packets.cap 
echo test 5:
./tp tests/05_threshold/elite_4_or_more.cfg tests/05_threshold/elite.cap
echo test 6:
./tp tests/06_fragmented_ordered/spoon.cfg tests/06_fragmented_ordered/packet_fragmented.cap
echo test 7:
./tp tests/07_fragmented_unordered/spoon.cfg tests/07_fragmented_unordered/packet_fragmented.cap 
echo test 8:
./tp tests/08_multiples_matches/rules.cfg tests/08_multiples_matches/packets.cap
echo test 9:
./tp tests/09_multiple_captures/spoon.cfg tests/09_multiple_captures/cap0.cap tests/09_multiple_captures/cap1.cap tests/09_multiple_captures/cap2.cap tests/09_multiple_captures/cap3.cap tests/09_multiple_captures/cap4.cap
