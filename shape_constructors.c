
double planeX(double u, double v){
  return u;
}
double planeY(double u, double v){
  return 0;
}
double planeZ(double u, double v){
  return v;
}



void top(double x, double y, double z, double A[4][4], double V[4][4]){

		double RES = 50;


		ulo = -1; uhi = 1;
		vlo = -1; vhi = 1;
		f = planeX;
		g = planeY;
		h = planeZ;

		Tn = 0;
		Ttypelist[Tn] = SX ; Tvlist[Tn] = .05 ; Tn++ ;
	  Ttypelist[Tn] = SY ; Tvlist[Tn] = .05 ; Tn++ ;
	  Ttypelist[Tn] = SZ ; Tvlist[Tn] = .05 ; Tn++ ;
		Ttypelist[Tn] = TX ; Tvlist[Tn] = 1 ; Tn++ ;
		Ttypelist[Tn] = TY ; Tvlist[Tn] = 0; Tn++ ;
		Ttypelist[Tn] = TZ ; Tvlist[Tn] = 1   ; Tn++ ;


	  plot(ulo, uhi, vlo, vhi, V, A);

}
