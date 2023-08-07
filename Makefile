CC= gcc -Wall -ggdb

obj1= exo1.o exo2.o
obj2= partie2.o $(obj1)
obj3= partie3.o $(obj2)
obj4= partie4.o $(obj3)  
obj5= partie5.o $(obj4)

%.o: %.c
	@$(CC) -o $@ -c $<

partie1:$(obj1) main1.o
	$(CC) -o $@ $^

partie2:$(obj2) main2.o
	$(CC) -o $@ $^

partie3:$(obj3) main3.o
	$(CC) -o $@ $^

partie4:$(obj4) main4.o
	$(CC) -o $@ $^ -lssl -lcrypto

partie5:$(obj5) main5.o
	$(CC) -o $@ $^ -lssl -lcrypto

clean:
	rm -f *.o partie1 partie2 partie3 partie4 partie5 Blockchain/*
	
