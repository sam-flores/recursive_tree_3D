



void get_rgb(double u, double v, double ulo, double uhi,
              double vlo, double vhi){ // needs vlo,vhi,ulo,uhi for mapping

    /*




    */
      // double x;
      // double y;

      // x = textureWidth*(u - ulo)/(uhi - ulo);
      // y = textureHeight*(v - vlo)/(vhi - vlo);
      //
      // get_xwd_map_color(idA, x, y, inherent_rgb) ; // returns -1 on error, 1 if ok

      if((int)round(u) % 2 == 0){
        inherent_rgb[0] = 0;
        inherent_rgb[1] = 1;
        inherent_rgb[2] = 1;
      }else if((int)round(u) % 3 == 0){
        inherent_rgb[0] = 5;
        inherent_rgb[1] = 0;
        inherent_rgb[2] = .8;
      }else{
        inherent_rgb[0] = 0;
        inherent_rgb[1] = 0;
        inherent_rgb[2] = .8;
      }
}
