#include "Eigen/Dense"

#define HI(num) (((num) & 0x0000FF00) >> 8)
#define LO(num) ((num) & 0x000000FF)

using namespace Eigen;
using namespace std;

void SkipComments(FILE *fp);
MatrixXd readPGM(string file_name);