all: randomchat csv-to-txt fix_file
	rm randomchat.o csv-to-txt.o fix_file.o

randomchat: randomchat.o
	g++ -o randomchat randomchat.o

randomchat.o: randomchat.cpp
	g++ -c randomchat.cpp

csv-to-txt: csv-to-txt.o
	g++ -o csv-to-txt csv-to-txt.o

csv-to-txt.o: csv-to-txt.cpp
	g++ -c csv-to-txt.cpp

fix_file: fix_file.o
	g++ -o fix_file fix_file.o

fix_file.o: fix_file.cpp
	g++ -c fix_file.cpp

clean:
	rm csv-to-txt randomchat *.o