CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

DATA= ../data/log4/60-rgb.png

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
	terrain_mask\


.PHONY: all
all: $(BIN)

.PHONY: test
test:
	./comparaisons-vt-multiples

.PHONY: algo1
algo1:
	./mahalanobis_model_init ../data/log1/001-rgb.png
	./mahalanobis $(DATA)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt $(DATA) ./hull.png
	./remplissage_enveloppe_convex ./hull.png filled_region_4_60.png

.PHONY: algo2
algo2:
	./terrain_mask ../data/log1/

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
