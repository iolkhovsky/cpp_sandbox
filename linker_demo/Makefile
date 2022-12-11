app: libcustomops.so
	g++ -std=c++17 \
		main.cpp \
		-I/home/user/cpp_sandbox/linker_demo \
		-L/home/user/cpp_sandbox/linker_demo \
		-lcustomops \
		-o app

libcustomops.so: custom_ops.o
	g++ -std=c++17 -shared custom_ops.o -o libcustomops.so

custom_ops.o:
	g++ -std=c++17 -c custom_ops.cpp -o custom_ops.o

clean:
	rm custom_ops.o
	rm libcustomops.so
	rm app
