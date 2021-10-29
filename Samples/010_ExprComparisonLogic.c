
void ComparisonLogic(void) {
    char c, c2;
    short s;
    long  l;
    
    c && s && l;
    c && c;                     // c && c
    0 && c;                     // 0
    1 && c;                     // c
    c && 1;                     // c
    c && 0;                     // c && 0
    c && 1 && c2;               // c && c2
    c && 0 && c2;               // c            // we get c && 0 && c2
    0 && c;                     // 0
    (0&&c) && (0 &&c);          // 0
    (0&&c) && (1 &&c);          // 0
    (1&&c) && (0 &&c);          // c & 0
    (1&&(c|-1)) && (1&&(c|-1)); // 1            // is this right ? (c avoided due to | -1 arithmetic)
 
    c || 1;                     // c || 1
    c || 0;                     // c
    1 || c;                     // 1
    0 || c;                     // c
    c || 0 || c2;               //  c || c2
    c || 1 || c2;               // c           // we get c || 1 || c2;
    (0&&c) || (0 &&c);          // 0
    (0&&c) || (1&&(c|-1));      // 1
    (1&&(c|-1)) || (0 &&c);     // 1
    (1&&(c|-1)) || (1&&(c|-1)); // 1
    
}
