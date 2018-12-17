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

	#OBJ= comparaison-vt.o
	test_vt\
	make-se\

.PHONY: all
all: $(BIN)

#$(BIN): comparaison-vt.o


.PHONY: test
test:
	#./seuil_V0 ../data/log1/001-rgb.png
<<<<<<< HEAD
	./mahalanobis_model_init ../data/log1/001-rgb.png
	./mahalanobis ../data/log1/001-rgb.png
	./ero_dil ./mahalanobis.png erosion.png ./croix.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt ../data/log1/001-rgb.png ./hull.png
=======
	#./mahalanobis_model_init ../data/log1/001-rgb.png
	#./mahalanobis ../data/log1/001-rgb.png
	#./ero_dil ./mahalanobis.png erosion.png ./croix.png
	#./ero_dil ./mahalanobis.png erosion_carre.png ./carre.png
	#./ero_dil ./mahalanobis.png erosion_grand_carre.png ./square.png
	#./enveloppe_convex ./erosion.png
	#./enveloppe_convex ./erosion_carre.png
	#./enveloppe_convex ./erosion_grand_carre.png
	./comparaisons-vt-multiples teste

>>>>>>> e2c9fc4098194a7f30a5b9ce7143e46c4912807e

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
