# 
#  Copyright 
# 


MatrixAbstractLayerdir = $(datadir)/doc/MatrixAbstractLayer

EXTRA_DIST = \
	header.html \
	footer.html \
	package.css \
	pictures/footer.jpg \
	additionalDoc/package.h 

install-data-hook: html
	mkdir -p $(MatrixAbstractLayerdir)
	$(INSTALL_DATA) html/* $(MatrixAbstractLayerdir)
	mkdir -p $(MatrixAbstractLayerdir)/pictures
	$(INSTALL_DATA) $(srcdir)/pictures/* $(MatrixAbstractLayerdir)/pictures

html: package.dox
	doxygen $<
