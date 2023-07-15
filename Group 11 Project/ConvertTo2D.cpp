#include <iostream>

int main(int argc, char* argv[]) {
    FILE *fr = fopen("CollisionArrayNew.txt", "r");
    FILE *fw = fopen("Collision2DArrayNew.txt", "w");

    int Collision2D[114][94];
    char input;
    char openBr = '{';
    char closeBr = '}';
    char comma = ',';
    char nextLine = '\n';

    fwrite(&openBr, sizeof(char), 1, fw);
    for(int i = 0; i < 94; i++) {
        fwrite(&openBr, sizeof(char), 1, fw);
        for(int j = 0; j < 114; j++) {
            for(int k = 0; k < 3;k++) {
                fread(&input, sizeof(char), 1, fr);
                fwrite(&input, sizeof(char), 1, fw);
            }
        }
        fwrite(&closeBr, sizeof(char), 1, fw);
        fwrite(&comma, sizeof(char), 1, fw);
        fwrite(&nextLine, sizeof(char), 1, fw);
    }
    fwrite(&closeBr, sizeof(char), 1, fw);

    fclose(fr);
    fclose(fw);
}