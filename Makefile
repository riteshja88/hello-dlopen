run: service
	./obj/dlopen_demo

service: dll
	gcc dlopen_demo.c -ldl -o obj/dlopen_demo

make_obj:
	mkdir -p obj

dll: make_obj obj/predict.so

obj/predict.o: predict.c
	gcc -c -fPIC predict.c -o obj/predict.o
obj/predict.so: obj/predict.o
	gcc obj/predict.o -shared -o obj/predict.so

clean:
	rm -f obj/*

clobber:
	rm -rf obj
