CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	seuil_V0\
	ero_dil\
	terrain_mask \
	application_mask\
	make-se\

.PHONY: all
all: $(BIN)

.PHONY: test
test:
	./make-se 7 2 croix.png
	./terrain_mask ../data/log1/001-rgb.png mask.png
	./ero_dil mask.png maskImage.png croix.png
	./application_mask ../data/log1/001-rgb.png maskImage.png terrain.png autour.png



.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
