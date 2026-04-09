#include <am.h>
#include <klib-macros.h>
#include <assert.h>

#define N 32
static uint32_t color_buf[32*32];

void draw(uint32_t color) {
  // add code here
  //获取屏幕尺寸
  int w = io_read(AM_GPU_CONFIG).width/N;
  int h = io_read(AM_GPU_CONFIG).height/N;
    
  int block_size=w*h;
  assert(block_size<=sizeof(color_buf)/sizeof(color_buf[0]));

  int x=0;
  int y=0;

  for(x=0;x<N;x++){

      for(y=0;y<N;y++){
      for(int k=0;k<block_size;k++)
      {
      color_buf[k] = color;
      }

  io_write(AM_GPU_FBDRAW,x*w,y*h,color_buf,w,h,false);
    }
     
  }

  io_write(AM_GPU_FBDRAW,0,0,NULL,0,0,true);
}

int main() {
  ioe_init(); // initialization for GUI
  while (1) {
    draw(0x000000ff);
    
  }
  return 0;
}

