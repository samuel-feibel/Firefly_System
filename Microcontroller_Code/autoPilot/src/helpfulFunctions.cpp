// Helpful Functions for the whole project

void copy(double *a, double *b, int b_size) {
     if(b_size == 0) return;    
     *a = *b;
     copy(++a, ++b, b_size-1);
}