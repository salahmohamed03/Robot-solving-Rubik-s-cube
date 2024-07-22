#define w11 w[0][0]
#define w12 w[0][1]
#define w13 w[0][2]
#define w21 w[1][0]
#define w23 w[1][2]
#define w31 w[2][0]
#define w32 w[2][1]
#define w33 w[2][2]
#define y11 y[0][0]
#define y12 y[0][1]
#define y13 y[0][2]
#define y21 y[1][0]
#define y23 y[1][2]
#define y31 y[2][0]
#define y32 y[2][1]
#define y33 y[2][2]
#define b11 b[0][0]
#define b12 b[0][1]
#define b13 b[0][2]
#define b21 b[1][0]
#define b23 b[1][2]
#define b31 b[2][0]
#define b32 b[2][1]
#define b33 b[2][2]
#define g11 g[0][0]
#define g12 g[0][1]
#define g13 g[0][2]
#define g21 g[1][0]
#define g23 g[1][2]
#define g31 g[2][0]
#define g32 g[2][1]
#define g33 g[2][2]
#define r11 r[0][0]
#define r12 r[0][1]
#define r13 r[0][2]
#define r21 r[1][0]
#define r23 r[1][2]
#define r31 r[2][0]
#define r32 r[2][1]
#define r33 r[2][2]
#define o11 o[0][0]
#define o12 o[0][1]
#define o13 o[0][2]
#define o21 o[1][0]
#define o23 o[1][2]
#define o31 o[2][0]
#define o32 o[2][1]
#define o33 o[2][2]
void filter(String& s);// to remove unwanted moves in the final solution
int counter(String s);
class cube
{
public:
  char w[3][3]; char y[3][3]; char b[3][3];
  char g[3][3]; char r[3][3]; char o[3][3]; // six faces
  void U(bool); // up move
  void D(bool); // down move 
  void R(bool); // right move 
  void L(bool); // left move 
  void f(bool); // front move 
  void B(bool); // back move 
  void transp(char c[3][3]); // transpose; asistent function for moving functions
  void perform(String s);// to ease performing moves by writing it as a string
  void solve_white_cross(String&);// solving the edges of the white face
  void solve_white_corners(String&);// solving the corners of the white face
  void solve_middle_layer(String&);// solving the middle edges
  void OLL(String& s); // oriantation of the last layer ; 57 alg
  void PLL(String& s); // permutation of the last layer ; 21 alg
  bool operator!=(cube);// to compare two cubes
  cube(); // consractor
};





String s;
void setup()
{
  Serial.begin(9600);
  cube x;
  
  x.perform("U");
  x.solve_white_cross(s);
  
}

void loop()
{
  Serial.println(s);
}







void cube::transp(char c[3][3])
{
  char temp[3][3];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      temp[i][j] = c[i][j];
  c[0][2] = temp[0][0]; c[1][2] = temp[0][1]; c[2][2] = temp[0][2];
  c[0][1] = temp[1][0]; c[1][1] = temp[1][1]; c[2][1] = temp[1][2];
  c[0][0] = temp[2][0]; c[1][0] = temp[2][1]; c[2][0] = temp[2][2];
}
bool cube::operator!=(cube x)
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (w[i][j] != x.w[i][j]) return 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (y[i][j] != x.y[i][j]) return 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (b[i][j] != x.b[i][j]) return 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (g[i][j] != x.g[i][j]) return 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (r[i][j] != x.r[i][j]) return 1;
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      if (o[i][j] != x.o[i][j]) return 1;
  return 0;
}

cube::cube()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      w[i][j] = 'w';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      y[i][j] = 'y';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      b[i][j] = 'b';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      g[i][j] = 'g';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      r[i][j] = 'r';
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      o[i][j] = 'o';
}

void filter(String& s)
{
  for (int i = 0; i < s.length() - 3; i++) {
    if (tolower(s[i]) == tolower(s[i + 1]) && tolower(s[i]) == tolower(s[i + 2]) && tolower(s[i]) == tolower(s[i + 3]))
    {
      s[i] = '0'; s[i + 1] = '0'; s[i + 2] = '0'; s[i + 3] = '0';
    }
  }
  String s2 = "", s3 = "", s4 = "";
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] != '0')s2 += s[i];
  }
  s = s2;
  for (int i = 0; i < s.length() - 1; i++) {
    if ((s[i] == tolower(s[i + 1]) && s[i] != s[i + 1]) || (s[i + 1] == tolower(s[i]) && s[i] != s[i + 1]))
    {
      s[i] = '0'; s[i + 1] = '0';
    }
  }
  for (int i = 0; i < s.length(); i++) { if (s[i] != '0')s3 += s[i]; }s = s3;

  for (int i = 0; i < s.length() - 2; i++) {
    if (s[i] == s[i + 1] && s[i] == s[i + 2])
    {
      if (s[i] == tolower(s[i + 1])) { s[i] = s[i + 1] = '0'; s[i + 2] = toupper(s[i + 2]); }
      else { s[i] = s[i + 1] = '0'; s[i + 2] = tolower(s[i + 2]); }
    }
  }
  for (int i = 0; i < s.length(); i++) { if (s[i] != '0')s4 += s[i]; }s = s4;
}
void cube::U(bool x)
{
  int i = 2;
  do
  {
    transp(y);
    char t1 = r[0][0], t2 = r[0][1], t3 = r[0][2];
    r[0][0] = g[0][0]; r[0][1] = g[0][1]; r[0][2] = g[0][2];
    char e1 = b[0][0], e2 = b[0][1], e3 = b[0][2];
    b[0][0] = t1; b[0][1] = t2; b[0][2] = t3;
    t1 = o[0][0], t2 = o[0][1], t3 = o[0][2];
    o[0][0] = e1; o[0][1] = e2; o[0][2] = e3;
    g[0][0] = t1; g[0][1] = t2; g[0][2] = t3;
  } while (i-- && x);
}

void cube::D(bool x)
{
  if (x) { transp(w); transp(w); transp(w); }
  else transp(w);
  int i = 2;
  do
  {
    char t1 = r[2][0], t2 = r[2][1], t3 = r[2][2];
    r[2][0] = g[2][0]; r[2][1] = g[2][1]; r[2][2] = g[2][2];
    char e1 = b[2][0], e2 = b[2][1], e3 = b[2][2];
    b[2][0] = t1; b[2][1] = t2; b[2][2] = t3;
    t1 = o[2][0], t2 = o[2][1], t3 = o[2][2];
    o[2][0] = e1; o[2][1] = e2; o[2][2] = e3;
    g[2][0] = t1; g[2][1] = t2; g[2][2] = t3;
  } while (i-- && !x);
}

void cube::R(bool x) // g > y > b > w > g
{
  int i = 2;
  do
  {
    transp(o);
    char t1 = y[0][2], t2 = y[1][2], t3 = y[2][2];
    y[0][2] = g[0][2]; y[1][2] = g[1][2]; y[2][2] = g[2][2];
    char e1 = b[0][0], e2 = b[1][0], e3 = b[2][0];
    b[0][0] = t3; b[1][0] = t2; b[2][0] = t1;
    t1 = w[0][2], t2 = w[1][2], t3 = w[2][2];
    w[0][2] = e3; w[1][2] = e2; w[2][2] = e1;
    g[0][2] = t1; g[1][2] = t2; g[2][2] = t3;
  } while (i-- && x);
}
void cube::L(bool x) // g > y > b > w > g
{
  if (x) { transp(r); transp(r); transp(r); }
  else transp(r);
  int i = 2;
  do
  {
    char t1 = y[0][0], t2 = y[1][0], t3 = y[2][0];
    y[0][0] = g[0][0]; y[1][0] = g[1][0]; y[2][0] = g[2][0];
    char e1 = b[0][2], e2 = b[1][2], e3 = b[2][2];
    b[0][2] = t3; b[1][2] = t2; b[2][2] = t1;
    t1 = w[0][0], t2 = w[1][0], t3 = w[2][0];
    w[0][0] = e3; w[1][0] = e2; w[2][0] = e1;
    g[0][0] = t1; g[1][0] = t2; g[2][0] = t3;
  } while (i-- && !x);
}

void cube::f(bool x) // transp g , y > o > w > r > y
{
  int i = 2;
  do
  {
    transp(g);
    char t1 = o[0][0], t2 = o[1][0], t3 = o[2][0];
    o[0][0] = y[2][0]; o[1][0] = y[2][1]; o[2][0] = y[2][2];
    char e1 = w[0][0], e2 = w[0][1], e3 = w[0][2];
    w[0][0] = t3; w[0][1] = t2; w[0][2] = t1;
    t1 = r[0][2], t2 = r[1][2], t3 = r[2][2];
    r[0][2] = e1; r[1][2] = e2; r[2][2] = e3;
    y[2][0] = t3; y[2][1] = t2; y[2][2] = t1;
  } while (i-- && x);
}

void cube::B(bool x) // 3 transp b , y > o > w > r > y
{
  if (x) { transp(b); transp(b); transp(b); }
  else transp(b);
  int i = 2;
  do
  {
    char t1 = o[0][2], t2 = o[1][2], t3 = o[2][2];
    o[0][2] = y[0][0]; o[1][2] = y[0][1]; o[2][2] = y[0][2];
    char e1 = w[2][0], e2 = w[2][1], e3 = w[2][2];
    w[2][0] = t3; w[2][1] = t2; w[2][2] = t1;
    t1 = r[0][0], t2 = r[1][0], t3 = r[2][0];
    r[0][0] = e1; r[1][0] = e2; r[2][0] = e3;
    y[0][0] = t3; y[0][1] = t2; y[0][2] = t1;
  } while (i-- && !x);
}
void cube::perform(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    if (s[i] == 'U') { U(0); }
    if (s[i] == 'u') { U(1); }
    if (s[i] == 'D') { D(0); }
    if (s[i] == 'd') { D(1); }
    if (s[i] == 'R') { R(0); }
    if (s[i] == 'r') { R(1); }
    if (s[i] == 'L') { L(0); }
    if (s[i] == 'l') { L(1); }
    if (s[i] == 'F') { f(0); }
    if (s[i] == 'f') { f(1); }
    if (s[i] == 'B') { B(0); }
    if (s[i] == 'b') { B(1); }
  }
}

void cube::solve_white_cross(String& s)
{
  cube x;
  int n = 2;
  do {
    if (w12 == 'w')
    {
      if (g32 == 'r') { s += "ffUll"; perform("ffUll"); }
      else if (g32 == 'o') { s += "ffurr"; perform("ffurr"); }
      else if (g32 == 'b') { s += "ffuubb"; perform("ffuubb"); }
    }
    if (w21 == 'w')
    {
      if (r32 == 'g') { s += "lluff"; perform("lluff"); }
      else if (r32 == 'o') { s += "lluurr"; perform("lluurr"); }
      else if (r32 == 'b') { s += "llUbb"; perform("llUbb"); }
    }
    if (w32 == 'w')
    {
      if (b32 == 'g') { s += "bbuuff"; perform("bbuuff"); }
      else if (b32 == 'o') { s += "bbUrr"; perform("bbUrr"); }
      else if (b32 == 'r') { s += "bbull"; perform("bbull"); }
    }
    if (w23 == 'w')
    {
      if (o32 == 'g') { s += "rrUff"; perform("rrUff"); }
      else if (o32 == 'r') { s += "rrUUll"; perform("rrUUll"); }
      else if (o32 == 'b') { s += "rrubb"; perform("rrubb"); }
    }
    if (g12 == 'w')
    {
      if (y32 == 'g') { s += "urFR"; perform("urFR"); }
      else if (y32 == 'r') { s += "fLF"; perform("fLF"); }
      else if (y32 == 'o') { s += "Frf"; perform("Frf"); }
      else if (y32 == 'b') { s += "uRbr"; perform("uRbr"); }
    }
    if (g21 == 'w')
    {
      if (r23 == 'g') { s += "dLD"; perform("dLD"); }
      else if (r23 == 'r') { s += "L"; perform("L"); }
      else if (r23 == 'o') { s += "FFrFF"; perform("FFrFF"); }
      else if (r23 == 'b') { s += "DLd"; perform("DLd"); }
    }
    if (g32 == 'w')
    {
      if (w12 == 'g') { s += "dLD"; perform("dLD"); }
      else if (w12 == 'r') { s += "L"; perform("L"); }
      else if (w12 == 'o') { s += "FFrFF"; perform("FFrFF"); }
      else if (w12 == 'b') { s += "DLd"; perform("DLd"); }
    }
    if (g23 == 'w')
    {
      if (o21 == 'g') { s += "Drd"; perform("Drd"); }
      else if (o21 == 'r') { s += "FFLFF"; perform("FFLFF"); }
      else if (o21 == 'o') { s += "r"; perform("r"); }
      else if (o21 == 'b') { s += "drD"; perform("drD"); }
    }
    if (y12 == 'w')
    {
      if (b12 == 'g') { s += "UUFF"; perform("UUFF"); }
      else if (b12 == 'r') { s += "ull"; perform("ull"); }
      else if (b12 == 'o') { s += "URR"; perform("URR"); }
      else if (b12 == 'b') { s += "bb"; perform("bb"); }
    }
    if (y21 == 'w')
    {
      if (r12 == 'g') { s += "uFF"; perform("uFF"); }
      else if (r12 == 'r') { s += "ll"; perform("ll"); }
      else if (r12 == 'o') { s += "UURR"; perform("UURR"); }
      else if (r12 == 'b') { s += "DLd"; perform("DLd"); }
    }
    if (y32 == 'w')
    {
      if (g12 == 'g') { s += "FF"; perform("FF"); }
      else if (g12 == 'r') { s += "Ull"; perform("Ull"); }
      else if (g12 == 'o') { s += "uRR"; perform("uRR"); }
      else if (g12 == 'b') { s += "UUbb"; perform("UUbb"); }
    }
    if (y23 == 'w')
    {
      if (o12 == 'g') { s += "UFF"; perform("UFF"); }
      else if (o12 == 'r') { s += "UUll"; perform("UUll"); }
      else if (o12 == 'o') { s += "RR"; perform("RR"); }
      else if (o12 == 'b') { s += "ubb"; perform("ubb"); }
    }
    if (r12 == 'w')
    {
      if (y21 == 'g') { s += "Lfl"; perform("Lfl"); }
      else if (y21 == 'r') { s += "ufLF"; perform("ufLF"); }
      else if (y21 == 'o') { s += "uFrf"; perform("uFrf"); }
      else if (y21 == 'b') { s += "lBL"; perform("lBL"); }
    }
    if (r21 == 'w')
    {
      if (b23 == 'g') { s += "ddBdd"; perform("ddBdd"); }
      else if (b23 == 'r') { s += "dBD"; perform("dBD"); }
      else if (b23 == 'o') { s += "DBd"; perform("DBd"); }
      else if (b23 == 'b') { s += "B"; perform("B"); }
    }
    if (r32 == 'w')
    {
      if (w21 == 'g') { s += "lf"; perform("lf"); }
      else if (w21 == 'r') { s += "lDfd"; perform("lDfd"); }
      else if (w21 == 'o') { s += "ldfD"; perform("ldfD"); }
      else if (w21 == 'b') { s += "LB"; perform("LB"); }
    }
    if (r23 == 'w')
    {
      if (g21 == 'g') { s += "f"; perform("f"); }
      else if (g21 == 'r') { s += "Dfd"; perform("Dfd"); }
      else if (g21 == 'o') { s += "dfD"; perform("dfD"); }
      else if (g21 == 'b') { s += "ddfdd"; perform("ddfdd"); }
    }
    if (b12 == 'w')
    {
      if (y12 == 'g') { s += "UrFR"; perform("UrFR"); }
      else if (y12 == 'r') { s += "Blb"; perform("Blb"); }
      else if (y12 == 'o') { s += "bRB"; perform("bRB"); }
      else if (y12 == 'b') { s += "URbr"; perform("URbr"); }
    }
    if (b21 == 'w')
    {
      if (o23 == 'g') { s += "ddbdd"; perform("ddbdd"); }
      else if (o23 == 'r') { s += "dbD"; perform("dbD"); }
      else if (o23 == 'o') { s += "R"; perform("R"); }
      else if (o23 == 'b') { s += "dRD"; perform("dRD"); }
    }
    if (b32 == 'w')
    {
      if (w32 == 'g') { s += "bdlD"; perform("bdlD"); }
      else if (w32 == 'r') { s += "bl"; perform("bl"); }
      else if (w32 == 'o') { s += "BR"; perform("BR"); }
      else if (w32 == 'b') { s += "bDld"; perform("bDld"); }
    }
    if (b23 == 'w')
    {
      if (r21 == 'g') { s += "llfll"; perform("llfll"); }
      else if (r21 == 'r') { s += "l"; perform("l"); }
      else if (r21 == 'o') { s += "DBd"; perform("DBd"); }
      else if (r21 == 'b') { s += "Dld"; perform("Dld"); }
    }
    if (o12 == 'w')
    {
      if (y23 == 'g') { s += "rFR"; perform("rFR"); }
      else if (y23 == 'r') { s += "UfLF"; perform("UfLF"); }
      else if (y23 == 'o') { s += "UFrf"; perform("UFrf"); }
      else if (y23 == 'b') { s += "Rbr"; perform("Rbr"); }
    }
    if (o21 == 'w')
    {
      if (g23 == 'g') { s += "F"; perform("F"); }
      else if (g23 == 'r') { s += "DFd"; perform("DFd"); }
      else if (g23 == 'o') { s += "dFD"; perform("dFD"); }
      else if (g23 == 'b') { s += "ddFdd"; perform("ddFdd"); }
    }
    if (o32 == 'w')
    {
      if (w23 == 'g') { s += "RF"; perform("RF"); }
      else if (w23 == 'r') { s += "RDFd"; perform("RDFd"); }
      else if (w23 == 'o') { s += "RdFD"; perform("RdFD"); }
      else if (w23 == 'b') { s += "rb"; perform("rb"); }
    }
    if (o23 == 'w')
    {
      if (b21 == 'g') { s += "DRd"; perform("DRd"); }
      else if (b21 == 'r') { s += "dbD"; perform("dbD"); }
      else if (b21 == 'o') { s += "Dbd"; perform("Dbd"); }
      else if (b21 == 'b') { s += "b"; perform("b"); }
    }
  } while (n--);
}

void cube::solve_white_corners(String& s)
{
  while (g33 != 'g' || w13 != 'w' || g31 != 'g' || w11 != 'w' || b31 != 'b' || w33 != 'w' || b33 != 'b' || w31 != 'w')
  {
    if (g13 == 'w')
    {
      if (o11 == 'o') { s += "fuF"; perform("fuF"); }
      else if (o11 == 'b') { s += "Bub"; perform("Bub"); }
      else if (o11 == 'r') { s += "Luul"; perform("Luul"); }
      else if (o11 == 'g') { s += "UluL"; perform("UluL"); }
    }
    if (y33 == 'w')
    {
      if (o11 == 'o') { s += "uBUUbuBUb"; perform("uBUUbuBUb"); }
      else if (o11 == 'b') { s += "UlUULLUUl"; perform("UlUULLUUl"); }
      else if (o11 == 'r') { s += "UlUULUluL"; perform("UlUULUluL"); }
      else if (o11 == 'g') { s += "RUUruRUr"; perform("RUUruRUr"); }
    }
    if (o11 == 'w')
    {
      if (g13 == 'o') { s += "uBUb"; perform("uBUb"); }
      else if (g13 == 'b') { s += "UbUB"; perform("UbUB"); }
      else if (g13 == 'r') { s += "lUL"; perform("lUL"); }
      else if (g13 == 'g') { s += "RUr"; perform("RUr"); }
    }
    if (g13 == 'w' || y33 == 'w' || o11 == 'w' || o13 == 'w' || y13 == 'w' || b11 == 'w' ||
      b13 == 'w' || y11 == 'w' || r11 == 'w' || r13 == 'w' || y31 == 'w' || g11 == 'w')
    {
      if (g13 != 'w' && y33 != 'w' && o11 != 'w')
      {
        s += "U"; perform("U");
      }
    }
    else
    {
      if (g33 != 'g' || w13 != 'w') { s += "Rur"; perform("Rur"); continue; }
      if (g31 != 'g' || w11 != 'w') { s += "luL"; perform("luL"); continue; }
      if (b31 != 'b' || w33 != 'w') { s += "BUb"; perform("BUb"); continue; }
      if (b33 != 'b' || w31 != 'w') { s += "Luul"; perform("Luul"); continue; }
    }
  }
}

void cube::solve_middle_layer(String& s)
{
  while (g23 != 'g' || o21 != 'o' || o23 != 'o' || b21 != 'b' ||
    b23 != 'b' || r21 != 'r' || r23 != 'r' || g21 != 'g')
  {
    if (g12 == 'o' && y32 == 'g') { s += "UUrFRfRUr"; perform("UUrFRfRUr"); }
    if (g12 == 'o' && y32 == 'b') { s += "RbrBruR"; perform("RbrBruR"); }
    if (g12 == 'g' && y32 == 'r') { s += "ufLFlFUf"; perform("ufLFlFUf"); }
    if (g12 == 'g' && y32 == 'o') { s += "UFrfRfuF"; perform("UFrfRfuF"); }
    if (g12 == 'r' && y32 == 'b') { s += "lBLbLUl"; perform("lBLbLUl"); }
    if (g12 == 'r' && y32 == 'g') { s += "UULflFluL"; perform("UULflFluL"); }
    if (g12 == 'b' && y32 == 'o') { s += "UbRBrBUb"; perform("UbRBrBUb"); }
    if (g12 == 'b' && y32 == 'r') { s += "uBlbLbuB"; perform("uBlbLbuB"); }
    if (g12 == 'y' || y32 == 'y')
    {
      if (o12 != 'y' && y23 != 'y') { s += "U"; perform("U"); continue; }
      else if (b12 != 'y' && y12 != 'y') { s += "UU"; perform("UU"); continue; }
      else if (r12 != 'y' && y21 != 'y') { s += "u"; perform("u"); continue; }
    }
    else continue;
    if (g23 != 'g' || o21 != 'o' || o23 != 'o' || b21 != 'b' ||
      b23 != 'b' || r21 != 'r' || r23 != 'r' || g21 != 'g')
    {
      if (g23 != 'g' && o21 != 'o') { s += "RurFrfR"; perform("RurFrfR"); continue; }
      if (o23 != 'o' && b21 != 'b') { s += "BubRbrB"; perform("BubRbrB"); continue; }
      if (b23 != 'b' && r21 != 'r') { s += "LulBlbL"; perform("LulBlbL"); continue; }
      if (r23 != 'r' && g21 != 'g') { s += "FufLflF"; perform("FufLflF"); continue; }
    }
  }
}

void cube::OLL(String& s)
{
  while (!(y11 == y12 && y12 == y13 && y21 == y23 && y31 == y32))
  {

    if (y12 == 'y' && y21 == 'y' && y23 == 'y' && y32 == 'y') // cross
    {
      if (y11 == 'y' && y13 == 'y' && g13 == 'y') { s += "RRDruuRdruur"; perform("RRDruuRdruur"); break; }//23
      else if (y13 == 'y' && y33 == 'y' && g11 == 'y') { s += "LFrflFRf"; perform("LFrflFRf"); break; }//24
      else if (y11 == 'y' && y33 == 'y' && o13 == 'y') { s += "rFRbrfRB"; perform("rFRbrfRB"); break; }//25
      else if (y11 == 'y' && b11 == 'y' && g11 == 'y') { s += "ruRuruuR"; perform("ruRuruuR"); break; }//26
      else if (y11 == 'y' && o13 == 'y' && r13 == 'y' && g13 == 'y') { s += "luuLUlUL"; perform("luuLUlUL"); break; }//27
      else if (y11 != 'y' && y33 != 'y' && g13 == 'y' && b11 == 'y') { s += "RUURRuRRuRRUUR"; perform("RUURRuRRuRRUUR"); break; }//22
      else if (r11 == 'y' && r13 == 'y' && o11 == 'y' && o13 == 'y') { s += "RUrURurURUUr"; perform("RUrURurURUUr"); break; }//21
    }
    else if (y21 == 'y' && y23 == 'y') // line
    {
      if (y31 == 'y' && o13 == 'y' && g13 == 'y') { s += "FURUUruRUrf"; perform("FURUUruRUrf"); break; }//13
      else if (y33 == 'y' && g11 == 'y' && b11 == 'y' && r11 == 'y') { s += "rFRUrfRFuf"; perform("rFRUrfRFuf"); break; }//14
      else if (y33 == 'y' && b13 == 'y' && r13 == 'y') { s += "urUURUrFURurfR"; perform("urUURUrFURurfR");  break; }//15
      else if (y13 == 'y' && g11 == 'y' && o11 == 'y' && r11 == 'y') { s += "LFlRUruLfl"; perform("LFlRUruLfl"); break; }//16
      else if (y13 == 'y' && y33 == 'y' && g11 == 'y' && b13 == 'y') { s += "RUrurFRf"; perform("RUrurFRf"); break; }//33
      else if (y13 == 'y' && y33 == 'y') { s += "FRUruf"; perform("FRUruf"); break; }//45
      else if (y11 == 'y' && y13 == 'y' && g11 != 'y') { s += "UURUrubrFRfB"; perform("UURUrubrFRfB"); break; }//34
      else if (y11 == 'y' && y13 == 'y' && g11 == 'y') { s += "ururFRfUR"; perform("ururFRfUR"); break; }//46
      else if (y31 == 'y' && y13 == 'y' && r11 == 'y') { s += "UULfluLUFul"; perform("UULfluLUFul");  break; }//39
      else if (y11 == 'y' && y33 == 'y' && b11 == 'y' && b12 == 'y') { s += "rFRUrufUR"; perform("rFRUrufUR"); break; }//40
      else if (g11 == 'y' && g12 == 'y' && g13 == 'y' && b11 == 'y') { s += "URUURRuRurUUFRf"; perform("URUURRuRurUUFRf"); break; }//55
      else if (r11 == 'y' && r13 == 'y' && o11 == 'y' && o13 == 'y') { s += "FRUruRfLFrfl"; perform("FRUruRfLFrfl"); break; }//56
      else if (r11 == 'y' && r13 == 'y') { s += "UUFURurURurf"; perform("UUFURurURurf"); break; }//51
      else if (r13 == 'y' && o11 == 'y' && b11 == 'y' && b13 == 'y') { s += "UruRurUfUFR"; perform("UruRurUfUFR"); break; }//52
      else if (y11 == 'y' && y13 == 'y' && y31 == 'y' && y33 == 'y') { s += "RUruLrFRfl"; perform("RUruLrFRfl"); break; }//57
    }
    else if (y12 == 'y' && y21 == 'y') // L
    {
      if (y11 == 'y' && r13 == 'y' && g13 == 'y' && o13 == 'y') { s += "rffLFlFR"; perform("rffLFlFR"); break; }//5
      else if (y11 == 'y' && b11 == 'y' && g11 == 'y' && o11 == 'y') { s += "ULffrfRfl"; perform("ULffrfRfl"); break; }//6
      else if (y31 == 'y' && b13 == 'y' && g13 == 'y' && o13 == 'y') { s += "LFrFRffl"; perform("LFrFRffl"); break; }//7
      else if (r11 == 'y' && y13 == 'y' && o11 == 'y' && g11 == 'y') { s += "URUUrUUrFRf"; perform("URUUrUUrFRf"); break; }//8
      else if (r11 == 'y' && y33 == 'y' && g11 == 'y') { s += "RUrurFRRUruf"; perform("RUrurFRRUruf"); break; }//9
      else if (b13 == 'y' && y33 == 'y' && r13 == 'y') { s += "uRUrUrFRfRUUr"; perform("uRUrUrFRfRUUr"); break; }//10
      else if (y13 == 'y' && r13 == 'y' && g13 == 'y' && b13 == 'y') { s += "LFrFrDRdRffl"; perform("LFrFrDRdRffl"); break; }//11
      else if (y31 == 'y' && r11 == 'y' && o11 == 'y' && b11 == 'y') { s += "UUFRUrufUFRUruf"; perform("UUFRUrufUFRUruf"); break; }//12
      else if (y11 == 'y' && y13 == 'y' && y33 == 'y' && y31 == 'y') { s += "LFrflRURur"; perform("LFrflRURur"); break; }//28
      else if (y33 == 'y' && y13 == 'y' && g11 == 'y') { s += "UrFRfRUUrufuF"; perform("UrFRfRUUrufuF"); break; }//29
      else if (y31 == 'y' && y33 == 'y' && r11 == 'y' && o13 == 'y') { s += "FrFRRuruRUrff"; perform("FrFRRuruRUrff"); break; }//30
      else if (y11 == 'y' && y13 == 'y' && r13 == 'y') { s += "UruFURurfR"; perform("UruFURurfR"); break; }//31
      else if (y11 == 'y' && y31 == 'y' && g13 == 'y') { s += "LUfulULFl"; perform("LUfulULFl"); break; }//32
      else if (y33 == 'y' && r13 == 'y' && y11 == 'y') { s += "UURUURRFRfRUUr"; perform("UURUURRFRfRUUr"); break; }//35
      else if (y31 == 'y' && y13 == 'y' && g13 == 'y') { s += "UluLulULULflF"; perform("UluLulULULflF"); break; }//36
      else if (y11 == 'y' && y33 == 'y' && g11 == 'y') { s += "FrfRURur"; perform("FrfRURur"); break; }//37
      else if (y31 == 'y' && y13 == 'y' && b13 == 'y') { s += "RUrURururFRf"; perform("RUrURururFRf"); break; }//38
      else if (y31 == 'y' && y33 == 'y' && b13 == 'y' && b11 == 'y') { s += "RUrURUUrFRUruf"; perform("RUrURUUrFRUruf"); break; }//41
      else if (y13 == 'y' && y33 == 'y' && r11 == 'y') { s += "UrURUUrufUFUR"; perform("UrURUUrufUFUR"); break; }//42
      else if (y11 == 'y' && y13 == 'y' && g11 == 'y' && g13 == 'y') { s += "rufUFR"; perform("rufUFR"); break; }//43
      else if (y11 == 'y' && y31 == 'y' && o11 == 'y' && o13 == 'y') { s += "FURurf"; perform("FURurf"); break; }//44
      else if (b13 == 'y' && b11 == 'y' && r13 == 'y' && o11 == 'y') { s += "UfluLUluLUF"; perform("UfluLUluLUF"); break; }//47
      else if (r11 == 'y' && r13 == 'y' && g13 == 'y' && b11 == 'y') { s += "FRUruRUruf"; perform("FRUruRUruf"); break; }//48
      else if (r11 == 'y' && g11 == 'y' && g13 == 'y' && o13 == 'y') { s += "uRbRRFRRBrrfR"; perform("uRbRRFRRBrrfR"); break; }//49
      else if (b13 == 'y' && g11 == 'y' && o11 == 'y' && o13 == 'y') { s += "rFRRbRRfRRBr"; perform("rFRRbRRfRRBr"); break; }//50
      else if (r11 == 'y' && r13 == 'y' && o11 == 'y' && o13 == 'y') { s += "UUlbRbrBRbrBBL"; perform("UUlbRbrBRbrBBL"); break; }//53
      else if (b13 == 'y' && b11 == 'y' && g11 == 'y' && g13 == 'y') { s += "ULFrFRfrFRffl"; perform("ULFrFRfrFRffl"); break; }//54
    }
    else if (y12 != 'y' && y21 != 'y' && y23 != 'y' && y32 != 'y') // dot
    {
      if (r11 == 'y' && r12 == 'y' && o11 == 'y' && o13 == 'y') { s += "RUURRFRfUUrFRf"; perform("RUURRFRfUUrFRf"); break; }//1
      else if (r11 == 'y' && r13 == 'y' && g13 == 'y' && b11 == 'y') { s += "FRUrufBULulb"; perform("FRUrufBULulb"); break; }//2
      else if (y31 == 'y' && g13 == 'y' && b13 == 'y' && o13 == 'y') { s += "UFURurfUFRUruf"; perform("UFURurfUFRUruf"); break; }//3
      else if (r11 == 'y' && g11 == 'y' && y33 == 'y' && b11 == 'y') { s += "UFURurfuFRUruf"; perform("UFURurfuFRUruf"); break; }//4
      else if (y11 == 'y' && r13 == 'y' && y33 == 'y' && b11 == 'y') { s += "RUrUrFRfUUrFRf"; perform("RUrUrFRfUUrFRf"); break; }//17
      else if (y11 == 'y' && g11 == 'y' && g13 == 'y' && y13 == 'y') { s += "UUFRUrUfUUfLFl"; perform("UUFRUrUfUUfLFl"); break; }//18
      else if (y11 == 'y' && r13 == 'y' && o11 == 'y' && y13 == 'y') { s += "rUUFRUruffUUFR"; perform("rUUFRUruffUUFR"); break; }//19
      else if (y11 == 'y' && y13 == 'y' && y33 == 'y' && y31 == 'y') { s += "RlBRBrbRRllFRfl"; perform("RlBRBrbRRllFRfl"); break; }//20
    }
    s += "U"; perform("U");
  }
}

void cube::PLL(String& s)
{
  if (!(g11 == g12 && g12 == g13 && g13 == g[2][2] && r11 == r12 && r12 == r13 && r13 == r[2][2]))
    while (1)
    {

      if (g11 == g12 && g12 == g13 && r11 == r12 && r12 == r13)break;
      if (r11 == r13 && g11 == g13 && o11 == o13 && r12 == o11 && g11 == b12) { s += "RRUURUURRUURRUURUURR"; perform("RRUURUURRUURRUURUURR"); break; }// H perm
      if (r11 == r13 && b11 == b13 && o11 == o13 && b12 == r11 && r12 == o11) { s += "RRuruRURURuR"; perform("RRuruRURURuR"); break; }// UA perm
      if (r11 == r13 && b11 == b13 && o11 == o13 && b12 == o11 && o12 == r11) { s += "rUrururURURR"; perform("rUrururURURR"); break; }// Ub perm
      if (r11 == r13 && b11 == b13 && o11 == o13 && g11 == g13 && o12 == g11 && b11 == r11) { s += "ruRRURUruRURuRur"; perform("ruRRURUruRURuRur"); break; }// Z perm
      if (g11 == g12 && r13 == r12 && b11 == b13) { s += "rFrBBRfrBBRR"; perform("rFrBBRfrBBRR");   break; }// Aa perm
      if (r11 == r12 && b13 == b12 && g11 == g13) { s += "RbRFFrBRFFRR"; perform("RbRFFrBRFFRR"); break; }// Ab perm
      if (g11 == b13 && g13 == b11 && r11 == o13 && o11 == r13 && o12 == g13 && g12 == o13) { s += "RbrFRBrfRBrFRbrf"; perform("RbrFRBrfRBrFRbrf"); break; }// E perm
      if (g11 == g12 && g12 == g13 && r11 == o13 && r13 == o12) { s += "rURuRRfuFURFrfRRu"; perform("rURuRRfuFURFrfRRu"); break; } // F perm
      if (g11 == g13 && o13 == o12 && o12 == r11 && o11 == r12) { s += "UUFFDrUruRdFFlUL"; perform("UUFFDrUruRdFFlUL"); break; } // Ga perm
      if (r11 == r13 && b11 == b12 && b12 == g13 && r12 == o13) { s += "RRdFuFUfDRRBub"; perform("RRdFuFUfDRRBub"); break; } // Gc perm
      if (r11 == r13 && o11 == o12 && g13 == b11 && g11 == b12) { s += "RUrffdLulUlDff"; perform("RUrffdLulUlDff");  break; } // Gd perm
      if (r11 == r13 && o13 == o12 && b11 == g13 && g12 == o11) { s += "ruRUdRRUrURuRuRRD"; perform("ruRUdRRUrURuRuRRD");  break; } // Gb perm
      if (g11 == g12 && g12 == g13 && r11 == r12 && o11 == o12) { s += "rUlUURurUURL"; perform("rUlUURurUURL");   break; } // Ja perm
      if (r11 == r12 && r12 == r13 && g12 == g13 && b13 == b12) { s += "RUUruRUUlUruL"; perform("RUUruRUUlUruL"); break; } // Jb perm
      if (r13 == r12 && o13 == o12 && g12 == g13 && b13 == b12 && g11 == b13 && r13 == o11) { s += "LuRUUlUrLuRUUlUr"; perform("LuRUUlUrLuRUUlUr"); break; } // Na perm
      if (r11 == r12 && o11 == o12 && g11 == g12 && b11 == b12 && g13 == b11 && o13 == r11) { s += "rUlUURuLrUlUURuL"; perform("rUlUURuLrUlUURuL"); break; } // Nb perm
      if (g11 == g13 && o11 == o12 && o13 == r11 && g12 == r13) { s += "LUUlUULfluLULFll"; perform("LUUlUULfluLULFll");  break; } // Ra perm
      if (g11 == g13 && r13 == r12 && r11 == o13 && g12 == o11) { s += "rUURUUrFRUrurfRR"; perform("rUURUUrFRUrurfRR"); break; } // Rb perm
      if (r11 == r13 && g11 == g12 && b13 == b12) { s += "RUrurFRRuruRUrf"; perform("RUrurFRRuruRUrf");  break; } // T perm
      if (g11 == g12 && r13 == r12 && o11 != o13 && b11 != b13 && g13 == o12) { s += "RUUrDRuRuRURRDruRdd"; perform("RUUrDRuRuRURRDruRdd"); break; } // V perm
      if (g11 == g12 && r13 == o11 && o13 == o12) { s += "FRuruRUrfRUrurFRf"; perform("FRuruRUrfRUrurFRf");  break; }// Y perm
      s += "U"; perform("U");
    }
  while (!(g11 == g12 && g12 == g13 && g13 == g[2][2] && r11 == r12 && r12 == r13 && r13 == r[2][2])) { s += "U"; perform("U"); }
}

int counter(String s)
{
  int count = 0;
  for (int i = 0; i < s.length();)
  {
    if (s[i] == s[i + 1]) { count++; i += 2; }
    else { count++; i++; }
  }
  return count;
}
