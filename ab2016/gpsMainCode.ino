  enum gps{DOLAR_BEKLE, G1_BEKLE, P_BEKLE, G2_BEKLE, L1_BEKLE,L2_BEKLE, VIRGUL_BEKLE, YIRMIALTI_KARAKTER_AL};

enum gps konumDurum = DOLAR_BEKLE;

char konumVeri[27] = {0};
char konumVeriCounter = 0 ;

void gpsKutuphane(unsigned char karakter){
  switch(konumDurum){
    case DOLAR_BEKLE:
    if( karakter == '$') konumDurum = G1_BEKLE;
    break;
    case G1_BEKLE:
    if(karakter == 'G') konumDurum = P_BEKLE;
    else konumDurum = DOLAR_BEKLE;
    break;
    case P_BEKLE:
    if(karakter == 'P') konumDurum = G2_BEKLE;
    else konumDurum = DOLAR_BEKLE;
    break;
    case G2_BEKLE:
    if(karakter == 'G') konumDurum = L1_BEKLE;
    else konumDurum = DOLAR_BEKLE;
    break;
    case L1_BEKLE:
    if(karakter == 'L') konumDurum = L2_BEKLE;
    else konumDurum = DOLAR_BEKLE;
    break;
    case L2_BEKLE:
    if(karakter == 'L') konumDurum = VIRGUL_BEKLE;
    else konumDurum = DOLAR_BEKLE;
    break;
    case VIRGUL_BEKLE:
    if(karakter == ',') konumDurum = YIRMIALTI_KARAKTER_AL;
    else konumDurum = DOLAR_BEKLE;
    break;
    case YIRMIALTI_KARAKTER_AL:
    if(konumVeriCounter < 26) konumVeri[konumVeriCounter++] = karakter ;
    else {
      konumVeriCounter = 0;
      konumDurum = DOLAR_BEKLE;
    }
    break;
    default :
    konumDurum = DOLAR_BEKLE;
    break;
  }
    
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
  delay(3000);
  Serial.println(konumVeri);
}

