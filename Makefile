CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui

DATA= ../data/log1/262-rgb.png

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
	./mahalanobis $(DATA) 750
	./ero_dil ./mahalanobis.png erosion.png ./croix.png ./plus.png
	./enveloppe_convex ./erosion.png hull.png
	./test_vt $(DATA) ./hull.png
	./remplissage_enveloppe_convex ./hull.png filled_region_4_60.png

.PHONY: algo2
algo2:
	./terrain_mask ../data/log1/001-rgb.png algo2_filled_region_1_001.png 0
	./terrain_mask ../data/log1/081-rgb.png algo2_filled_region_1_081.png 0
	./terrain_mask ../data/log1/212-rgb.png algo2_filled_region_1_212.png 0
	./terrain_mask ../data/log1/231-rgb.png algo2_filled_region_1_231.png 0
	./terrain_mask ../data/log1/271-rgb.png algo2_filled_region_1_271.png 0
	./terrain_mask ../data/log1/358-rgb.png algo2_filled_region_1_358.png 0

	./terrain_mask ../data/log2/011-rgb.png algo2_filled_region_2_011.png 0
	./terrain_mask ../data/log2/089-rgb.png algo2_filled_region_2_089.png 0
	./terrain_mask ../data/log2/157-rgb.png algo2_filled_region_2_157.png 0
	./terrain_mask ../data/log2/185-rgb.png algo2_filled_region_2_185.png 0
	./terrain_mask ../data/log2/200-rgb.png algo2_filled_region_2_200.png 0
	./terrain_mask ../data/log2/231-rgb.png algo2_filled_region_2_231.png 0

	./terrain_mask ../data/log3/001-rgb.png algo2_filled_region_3_001.png 0
	./terrain_mask ../data/log3/043-rgb.png algo2_filled_region_3_043.png 0
	./terrain_mask ../data/log3/078-rgb.png algo2_filled_region_3_078.png 0
	./terrain_mask ../data/log3/125-rgb.png algo2_filled_region_3_125.png 0
	./terrain_mask ../data/log3/216-rgb.png algo2_filled_region_3_216.png 0
	./terrain_mask ../data/log3/249-rgb.png algo2_filled_region_3_249.png 0

	./terrain_mask ../data/log4/10-rgb.png algo2_filled_region_4_10.png 0
	./terrain_mask ../data/log4/20-rgb.png algo2_filled_region_4_20.png 0
	./terrain_mask ../data/log4/30-rgb.png algo2_filled_region_4_30.png 0
	./terrain_mask ../data/log4/40-rgb.png algo2_filled_region_4_40.png 0
	./terrain_mask ../data/log4/50-rgb.png algo2_filled_region_4_50.png 0
	./terrain_mask ../data/log4/60-rgb.png algo2_filled_region_4_60.png 0


.PHONY: algo22
algo22:
		./terrain_mask ../data/log1/001-rgb.png algo2_filled_region_1_001.png 15
		./terrain_mask ../data/log1/081-rgb.png algo2_filled_region_1_081.png 15
		./terrain_mask ../data/log1/212-rgb.png algo2_filled_region_1_212.png 15
		./terrain_mask ../data/log1/231-rgb.png algo2_filled_region_1_231.png 15
		./terrain_mask ../data/log1/271-rgb.png algo2_filled_region_1_271.png 15
		./terrain_mask ../data/log1/358-rgb.png algo2_filled_region_1_358.png 15

		./terrain_mask ../data/log2/011-rgb.png algo2_filled_region_2_011.png 15
		./terrain_mask ../data/log2/089-rgb.png algo2_filled_region_2_089.png 15
		./terrain_mask ../data/log2/157-rgb.png algo2_filled_region_2_157.png 15
		./terrain_mask ../data/log2/185-rgb.png algo2_filled_region_2_185.png 15
		./terrain_mask ../data/log2/200-rgb.png algo2_filled_region_2_200.png 15
		./terrain_mask ../data/log2/231-rgb.png algo2_filled_region_2_231.png 15

		./terrain_mask ../data/log3/001-rgb.png algo2_filled_region_3_001.png 15
		./terrain_mask ../data/log3/043-rgb.png algo2_filled_region_3_043.png 15
		./terrain_mask ../data/log3/078-rgb.png algo2_filled_region_3_078.png 15
		./terrain_mask ../data/log3/125-rgb.png algo2_filled_region_3_125.png 15
		./terrain_mask ../data/log3/216-rgb.png algo2_filled_region_3_216.png 15
		./terrain_mask ../data/log3/249-rgb.png algo2_filled_region_3_249.png 15

		./terrain_mask ../data/log4/10-rgb.png algo2_filled_region_4_10.png 15
		./terrain_mask ../data/log4/20-rgb.png algo2_filled_region_4_20.png 15
		./terrain_mask ../data/log4/30-rgb.png algo2_filled_region_4_30.png 15
		./terrain_mask ../data/log4/40-rgb.png algo2_filled_region_4_40.png 15
		./terrain_mask ../data/log4/50-rgb.png algo2_filled_region_4_50.png 15
		./terrain_mask ../data/log4/60-rgb.png algo2_filled_region_4_60.png 15



	./comparaisons-vt-multiples



.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
