#include "FPToolkit.c"
#include "M3d_matrix_tools.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int width = 600, height = 600;
double len = 100;
double d_theta = M_PI/2;

double A[4][4], Ai[4][4];
int Tn, Ttypelist[100];
double Tvlist[100];
double V[4][4], Vi[4][4];

double Half_window_size = 300;
double Half_angle_degrees = 30;
double Tan_half_angle ;
double zbuf[600][600];


double eye[3], coi[3], up[3] ;

void initZbuf(){
	int i = 0;
	int j = 0;
	while(i < 600){
		j = 0 ;
		while(j < 600){
			zbuf[i][j] = 1e50;
			j++;
		}
		i++;
	}
}

void G_line3(double x1, double y1, double z1,
              double x2, double y2, double z2){// plot line in 3 space

          double H = tan(30*M_PI/180);
          double a,b,c ;

          a = 300 / H ;
          b = 0.5*width ;
          c = 0.5*height ;

          double P[3];

          M3d_view (V, Vi,  eye,coi,up) ; //create view matrix

          Tn = 0 ;
          Ttypelist[Tn] = RZ ; Tvlist[Tn] = 90; Tn++ ;
          Ttypelist[Tn] = RX ; Tvlist[Tn] = 90; Tn++ ;
          Ttypelist[Tn] = SX ; Tvlist[Tn] =  .01 ; Tn++;
          Ttypelist[Tn] = SY ; Tvlist[Tn] =  .01 ; Tn++;
          Ttypelist[Tn] = SZ ; Tvlist[Tn] =  .01 ; Tn++;
          Ttypelist[Tn] = TX ; Tvlist[Tn] = 1; Tn++ ;
          Ttypelist[Tn] = TY ; Tvlist[Tn] = 0 ; Tn++ ;
          Ttypelist[Tn] = TZ ; Tvlist[Tn] = 1 ; Tn++ ;

          M3d_make_movement_sequence_matrix(A, Ai, Tn,
            Ttypelist, Tvlist); //move object

          for(double t = 0; t < 1; t += .005){

            P[0] = x1 + (x2 - x1)*t; // line is a parametric equation of
            P[1] = y1 + (y2 - y1)*t;  //  one variable
            P[2] = z1 + (z2 - z1)*t;

          M3d_mat_mult_pt (P, A, P) ; // transformed by T matrix
          M3d_mat_mult_pt (P, V, P) ; //pass through view matrix

          double x = P[0], y = P[1], z = P[2];

          if(z > 0 && y/z < H && x/z < H && y/z > -H && x/z > -H){
    		  double xp = a*(x/z) + b ; // screen transformation
    		  double yp = a*(y/z) + c ;
    		  // check if the point is allowed into zbuffer
    		  if(xp < 600 && yp < 600 && xp >= 0 && yp >= 0){
    		    if(z < zbuf[(int)(xp)][(int)(yp)]){
    					zbuf[(int)(xp)][(int)(yp)] = z;
              G_rgb(1, .55, 1); // set color to pink
    					G_point(xp, yp);
							// G_display_image();

    		}
    	}
    }
  }

}


int branch(double len, double x, double y, double z,
            double theta, double sign){

  /*

    this program takes the previous x,y and
    creates the next pair by adding len and rotating the point
    either left or right depending on the branch of recursion

  */

  double x1 = x, y1 = y, z1 = z;
  double x2 = x1 + sign*len*cos(theta + M_PI/2),
          y2 = y1 + sign*len,
          z2 = z1 + sign*len*sin(theta + M_PI/2);
  // G_line(x1, y1, x2, y2);
  G_line3(x1, y1, z1, x2, y2, z2); // pass points to 3D line plotter

  len = len*.67; // shrink factor of the line
  theta += d_theta; // angle that line is drawn from last line

  if(len > 2){ // recurse case
    branch(len, x2, y2, z2, theta, 1); // left branch
    branch(len, x2, y2, z2, theta, -1); // right branch
  }else{ //else exit
    return 0;
  }
}

int main(){

  G_init_graphics(width, height); // init graphics
  G_rgb(0,0,0);
  G_clear(); // clear background in black
  int q = 0;

  Half_window_size = 0.5*width ; // 3D graphics set up
  Half_angle_degrees = 30 ;
  Tan_half_angle = tan(Half_angle_degrees*M_PI/180) ;

  eye[0] = 0; eye[1] = 0; eye[2] = 0; // start eye out at origin

  double t = 0;
  int fnum = 0;

  while(q != 'q'){
    t = 0.01*fnum;

    G_rgb(0,0,0) ;
    G_clear() ;

    initZbuf();

    eye[0] = 0;
    eye[1] = t;
    eye[2] = 0;

    coi[0] =  1;
    coi[1] =  0.0 ;
    coi[2] =  1 ;

    up[0]  = eye[0] ;
    up[1]  = eye[1] + 1 ;
    up[2]  = eye[2] ;

    branch(len, 0, 0, 0, 0, 1); // begin tree +
    branch(len, 0, 0, 0, 0, -1); // begin tree -

    q = G_wait_key(); // check wait key

    if(q == 65362){
      d_theta += M_PI/25; // increase angle of twist
    }else if(q== 65364){
      d_theta -= M_PI/25; // decrease angle of twist
    }else if(q == 65363){ // transform eye +
      fnum += 10;
    }else if(q == 65361){ // transform eye -
      fnum -= 10;

    }
}
}
