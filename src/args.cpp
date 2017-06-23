/*
 * Implementation of args.h
 */

#include "args.h"

class Args {

    public:

        string toString() {
            return "";
        }

        string getColorsFilePath() {
            return colorsFilePath;
        }

        void setColorsFilePath(string path) {
            this.colorsFilePath = path;
        }

    private:

        string colorsFilePath;

        size_t kmerLen;

}
