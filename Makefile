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

.PHONY: all
all: $(BIN)

.PHONY: test
test:
	#./seuil_V0 ../data/log1/001-rgb.png
	./mahalanobis_model_init ../data/log1/001-rgb.png
	./mahalanobis ../data/log1/001-rgb.png

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
