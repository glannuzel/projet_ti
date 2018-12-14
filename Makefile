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
	test_vt\

.PHONY: all
all: $(BIN)

.PHONY: test
test:
	#./seuil_V0 ../data/log1/001-rgb.png
	#./mahalanobis_model_init ../data/log1/001-rgb.png
	./mahalanobis ../data/log1/231-rgb.png
	./ero_dil ./mahalanobis.png erosion.png ./croix.png
	#./ero_dil ./mahalanobis.png erosion_carre.png ./carre.png
	./enveloppe_convex ./erosion.png
	#./enveloppe_convex ./erosion_carre.png
	./test_vt ../data/log1/231-rgb.png ./convex-hull.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
