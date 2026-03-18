# TODO
# Sad se sve prevodi od ovuda.
# Maknuti to neka se sve prevodi zasebnim Makefileovima po direktorijima.

debug ?= 1 #isključiti dodavanjem debug=0 pri make-u, npr. $ make debug=0 run

CFLAGS = -MMD -D DEBUG=$(debug)
LDFLAGS = -O3
LDLIBS =

OBJEKTI = main.o ulaz/ulaz.o ulaz/datoteka/datoteka.o \
ulaz/generator/generator.o ulaz/tipkovnica/tipkovnica.o \
obrada/obrada.o obrada/pobroji/pobroji.o obrada/smisao/smisao.o \
obrada/smisao/na-brzinu/na-brzinu.o obrada/smisao/dublje/dublje.o\
izlaz/izlaz.o izlaz/datoteka/datoteka.o izlaz/ispis/ispis.o

ZAGLAVLJA=$(OBJEKTI:.o=.d)

PROG=prog

$(PROG): $(OBJEKTI)
	gcc $(LDFLAGS) $(OBJEKTI) $(LDLIBS) -o $(PROG)

run: $(PROG)
	./$(PROG)

brisi obrisi:
	rm -rf $(ZAGLAVLJA) $(OBJEKTI) $(PROG)

-include $(ZAGLAVLJA)
