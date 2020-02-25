
 
kompilator=g++
standard=-std=c++14
optymalizacja=-O3
# optymalizacja=
debug=-g
#debug=
profilowanie=-pg

exec=exec
zrodla=Mapav1
mem=memory_leaks
dane=data

# uruchomienie

__ : $(exec)/main
	cat $(dane)/data.txt  | $(exec)/main -d $(dane)/data2.txt > $(dane)/wyjscie
	$(exec)/main -d $(dane)/data2.txt -o $(dane)/wyjscie -t $(dane)/data.txt 
	$(exec)/main -d $(dane)/data2.txt -t $(dane)/data.txt -o 
 	$(exec)/main -d $(dane)/data2.txt 
	$(exec)/main -d $(dane)/data2.txt -o $(dane)/wyjscie -t 
# kompilacja programu

$(exec)/main : 	$(exec)/Mapa.o        \
                  $(exec)/cleanse.o     \
                  $(exec)/loading.o     \
                  $(exec)/pathfinding.o \
                  $(exec)/service.o     \
                  $(exec)/valid.o       \
                  $(exec)/debug_new.o             \
                  $(exec)/static_mem_pool.o       \
                  $(exec)/mem_pool_base.o         \
                  $(exec)/bool_array.o            \
                  $(exec)/static_mem_pool.o                  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^  
	
$(exec)/Mapa.o : $(zrodla)/Mapa.cpp 
	if [ ! -e $(exec) ] ; then mkdir $(exec) ; fi
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^  -c

$(exec)/cleanse.o : $(zrodla)/Cleanse.cpp  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ -c

$(exec)/loading.o : $(zrodla)/Loading.cpp  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ -c

$(exec)/pathfinding.o : $(zrodla)/pathfinding.cpp  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ -c

$(exec)/service.o : $(zrodla)/Service.cpp  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ -c

$(exec)/valid.o : $(zrodla)/Valid.cpp  
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ -c
	
# kompilacja biblioteki do sprawdzania wyciekow pamieci 
		
main : main.o 
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors -o $@ $^ 
	            
$(exec)/debug_new.o : $(mem)/debug_new.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 
	
$(exec)/static_mem_pool.o : $(mem)/static_mem_pool.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

$(exec)/mem_pool_base.o : $(mem)/mem_pool_base.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

$(exec)/bool_array.o : $(mem)/bool_array.cpp
	$(kompilator) $(standard) $(debug) $(optymalizacja) -pedantic-errors  -c -o $@ $^ 		

		
		
# czyszczenie:
		
clear:
	rm -r $(exec)

# dokumentacja 
	
doxygen : 
	doxygen doxygen.config


