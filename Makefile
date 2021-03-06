CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

DATA = ../data/log1/262-rgb.png

DESTINATION = filled_region.png

MULTIPLE = 1

TAILLEMASQUE = 0

VT = ./images_vt/log4-vt/60-rgb-vt.png

SEUIL = 750

BIN=\
	mahalanobis_model_init\
	mahalanobis\
	ero_dil\
	enveloppe_convex\
	comparaisons_vt_multiples_algo2\
	comparaisons_vt_multiples_algo1\
	comparaison_vt\
	test_vt\
	remplissage_enveloppe_convex\
	terrain_mask\
	mask_original\

.PHONY: all
all: $(BIN)

.PHONY: algo1
algo1:
	./mahalanobis_model_init ./log1/001-rgb.png
	./mahalanobis $(DATA) $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt $(DATA) ./hull.png
	./remplissage_enveloppe_convex ./hull.png $(DESTINATION)
	./mask_original $(DESTINATION) $(DATA) ./mask_image_originale.png

.PHONY: algo2
algo2:
	./terrain_mask $(DATA) $(DESTINATION) $(TAILLEMASQUE)

.PHONY: test_image
test_image:
	./terrain_mask $(DATA) image_test2.png $(TAILLEMASQUE)
	./mahalanobis_model_init ./log1/001-rgb.png
	./mahalanobis $(DATA) $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt $(DATA) ./hull.png
	./remplissage_enveloppe_convex ./hull.png image_test1.png
	./comparaison_vt image_test1.png $(VT) Algo1
	./comparaison_vt image_test2.png $(VT) Algo2

.PHONY: test_algo2
test_algo2:
	./terrain_mask ../data/log1/001-rgb.png ./images_test_algo2/algo2_filled_region_1_001.png $(TAILLEMASQUE)
	./terrain_mask ../data/log1/081-rgb.png ./images_test_algo2/algo2_filled_region_1_081.png $(TAILLEMASQUE)
	./terrain_mask ../data/log1/212-rgb.png ./images_test_algo2/algo2_filled_region_1_212.png $(TAILLEMASQUE)
	./terrain_mask ../data/log1/231-rgb.png ./images_test_algo2/algo2_filled_region_1_231.png $(TAILLEMASQUE)
	./terrain_mask ../data/log1/271-rgb.png ./images_test_algo2/algo2_filled_region_1_271.png $(TAILLEMASQUE)
	./terrain_mask ../data/log1/358-rgb.png ./images_test_algo2/algo2_filled_region_1_358.png $(TAILLEMASQUE)

	./terrain_mask ../data/log2/011-rgb.png ./images_test_algo2/algo2_filled_region_2_011.png $(TAILLEMASQUE)
	./terrain_mask ../data/log2/089-rgb.png ./images_test_algo2/algo2_filled_region_2_089.png $(TAILLEMASQUE)
	./terrain_mask ../data/log2/157-rgb.png ./images_test_algo2/algo2_filled_region_2_157.png $(TAILLEMASQUE)
	./terrain_mask ../data/log2/185-rgb.png ./images_test_algo2/algo2_filled_region_2_185.png $(TAILLEMASQUE)
	./terrain_mask ../data/log2/200-rgb.png ./images_test_algo2/algo2_filled_region_2_200.png $(TAILLEMASQUE)
	./terrain_mask ../data/log2/231-rgb.png ./images_test_algo2/algo2_filled_region_2_231.png $(TAILLEMASQUE)

	./terrain_mask ../data/log3/001-rgb.png ./images_test_algo2/algo2_filled_region_3_001.png $(TAILLEMASQUE)
	./terrain_mask ../data/log3/043-rgb.png ./images_test_algo2/algo2_filled_region_3_043.png $(TAILLEMASQUE)
	./terrain_mask ../data/log3/078-rgb.png ./images_test_algo2/algo2_filled_region_3_078.png $(TAILLEMASQUE)
	./terrain_mask ../data/log3/125-rgb.png ./images_test_algo2/algo2_filled_region_3_125.png $(TAILLEMASQUE)
	./terrain_mask ../data/log3/216-rgb.png ./images_test_algo2/algo2_filled_region_3_216.png $(TAILLEMASQUE)
	./terrain_mask ../data/log3/249-rgb.png ./images_test_algo2/algo2_filled_region_3_249.png $(TAILLEMASQUE)

	./terrain_mask ../data/log4/10-rgb.png ./images_test_algo2/algo2_filled_region_4_10.png $(TAILLEMASQUE)
	./terrain_mask ../data/log4/20-rgb.png ./images_test_algo2/algo2_filled_region_4_20.png $(TAILLEMASQUE)
	./terrain_mask ../data/log4/30-rgb.png ./images_test_algo2/algo2_filled_region_4_30.png $(TAILLEMASQUE)
	./terrain_mask ../data/log4/40-rgb.png ./images_test_algo2/algo2_filled_region_4_40.png $(TAILLEMASQUE)
	./terrain_mask ../data/log4/50-rgb.png ./images_test_algo2/algo2_filled_region_4_50.png $(TAILLEMASQUE)
	./terrain_mask ../data/log4/60-rgb.png ./images_test_algo2/algo2_filled_region_4_60.png $(TAILLEMASQUE)

	./comparaisons_vt_multiples_algo2 $(MULTIPLE)

.PHONY: test_algo1
test_algo1:
	./mahalanobis_model_init ./log1/001-rgb.png
	## Log 1
	./mahalanobis ../data/log1/001-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_001.png

	./mahalanobis ../data/log1/081-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_081.png

	./mahalanobis ../data/log1/212-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_212.png

	./mahalanobis ../data/log1/231-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_231.png

	./mahalanobis ../data/log1/271-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_271.png

	./mahalanobis ../data/log1/358-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_1_358.png

	## Log 2
	./mahalanobis ../data/log2/011-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_011.png

	./mahalanobis ../data/log2/089-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_089.png

	./mahalanobis ../data/log2/157-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_157.png

	./mahalanobis ../data/log2/185-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_185.png

	./mahalanobis ../data/log2/200-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_200.png

	./mahalanobis ../data/log2/231-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_2_231.png

	## Log 3
	./mahalanobis ../data/log3/001-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_001.png

	./mahalanobis ../data/log3/043-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_043.png

	./mahalanobis ../data/log3/078-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_078.png

	./mahalanobis ../data/log3/125-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_125.png

	./mahalanobis ../data/log3/216-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_216.png

	./mahalanobis ../data/log3/249-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_3_249.png

	## Log 4
	./mahalanobis ../data/log4/10-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_10.png

	./mahalanobis ../data/log4/20-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_20.png

	./mahalanobis ../data/log4/30-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_30.png

	./mahalanobis ../data/log4/40-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_40.png

	./mahalanobis ../data/log4/50-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_50.png

	./mahalanobis ../data/log4/60-rgb.png $(SEUIL)
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./remplissage_enveloppe_convex ./hull.png ./images_test_algo1/algo1_filled_region_4_60.png

	./comparaisons_vt_multiples_algo1 $(MULTIPLE)

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
