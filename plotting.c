


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

void plot(double ulo, double uhi, double vlo,
        double vhi, double T[4][4], double V[4][4]){

		// RES *= rFactor;
		double RES = 2;
		// printf("%lf\n", RES);
		double P[3],Q[3], R[3];

		double a,b,c ;

		double delta = 0;

		double H = Tan_half_angle;
		a = Half_window_size / H ;
		b = 0.5*width ;
		c = 0.5*height ;


    M3d_view (V, Vi,  eye,coi,up) ; //create view matrix

		for(double u = ulo; u < uhi; u += delta){
      for(double v = vlo; v < vhi; v += delta){

			/*

			this renderer uses adaptive delta modification
			depending on the relative stretch factor of each
			u,v cells which are being stretched into objects
			space and then screen space

			*/

			double origMag = 1;
			double mag = 1;
			double cross[3];
			double x, y, z;

      P[0] = f(u, v);
      P[1] = g(u, v);
      P[2] = h(u, v);

			Q[0] = f(u + 1/RES , v);
			Q[1] = g(u + 1/RES , v);
			Q[2] = h(u + 1/RES , v);
			R[0] = f(u, v + 1/RES);
			R[1] = g(u, v + 1/RES);
			R[2] = h(u, v + 1/RES);


			M3d_mat_mult_pt (P, T, P) ; // transformed by T matrix
			M3d_mat_mult_pt (Q, T, Q) ;
			M3d_mat_mult_pt (R, T, R) ;
      M3d_mat_mult_pt (P, V, P) ; //pass through view matrix
			M3d_mat_mult_pt (Q, V, Q) ; //pass through view matrix
			M3d_mat_mult_pt (R, V, R) ; //pass through view matrix

			x = P[0]; y = P[1]; z = P[2];

			M3d_x_product(cross, Q, R); // compute Q x R

			if(u == ulo && v == vlo){	//standard dA element
			origMag = sqrt(cross[0]*cross[0] +
			cross[1]*cross[1] + cross[2]*cross[2]);
				// magnitude of the cross product
		}else{
				mag = sqrt(cross[0]*cross[0] + //current dA element
				cross[1]*cross[1] + cross[2]*cross[2]);
			}

			delta = sqrt(mag/origMag)/RES;

			if(z > 0 && y/z < H && x/z < H && y/z > -H && x/z > -H){
		  double xp = a*(x/z) + b ; // screen transformation
		  double yp = a*(y/z) + c ;
		  // check if the point is allowed into zbuffer
		  if(xp < 600 && yp < 600 && xp >= 0 && yp >= 0){
		    if(z < zbuf[(int)(xp)][(int)(yp)]){
					zbuf[(int)(xp)][(int)(yp)] = z;
					inherent_rgb[0] = 0; inherent_rgb[1] = .8; inherent_rgb[2] = 1/47;
					// get_rgb(u, v, ulo, uhi, vlo, vhi); //color pixel based on u,v position
					light_model (inherent_rgb, P, Q, R, rgb) ; //apply light model
					G_rgb(rgb[0], rgb[1], rgb[2]) ;
					G_point(xp, yp);
		}
	}
}

		}
	}
}
