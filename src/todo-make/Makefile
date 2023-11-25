#
# invoke as "make PREFIX=/usr/local install" to override PREFIX
# 

PREFIX   	= $(HOME)
BINDIR 	 	= $(PREFIX)/bin
MAN1DIR 	= $(PREFIX)/man/man1
P2M_OPTS 	= -s 1 -r "Alpha" -c "github.com/hit9"

all:	compile
	
compile:
		$(MAKE) -C src/

clean:
		$(MAKE) -C src/ clean
		rm -f todo.1


install: compile todo.1
		install -d $(BINDIR)
		install src/todo $(BINDIR)
		install -d $(MAN1DIR)
		install todo.1 $(MAN1DIR)

uninstall:
		rm -f $(BINDIR)/todo
		rm -f $(MAN1DIR)/todo.1

todo.1: todo.pod
		pod2man $(P2M_OPTS) $< > $@

test:
		$(MAKE) -C src/ test
