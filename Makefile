CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	seuil_V0\
	mahalanobis_model_init\
	mahalanobis\
	ero_dil\
	enveloppe_convex\
	comparaisons-vt-multiples\
	test_vt\
	remplissage_enveloppe_convex\
	make-se\


.PHONY: all
all: $(BIN)


.PHONY: algo1
algo1:
	./mahalanobis_model_init ../data/log1/001-rgb.png
	./mahalanobis ../data/log1/001-rgb.png
	./ero_dil ./mahalanobis.png erosion.png ./croix.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt ../data/log1/001-rgb.png ./hull.png
	./enveloppe_convex ./erosion.png convex-hull.png
	./remplissage_enveloppe_convex ./convex-hull.png filled_region.png
	./comparaisons-vt-multiples teste

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
