#ifndef colors_hpp_20140803_1725_30
#define colors_hpp_20140803_1725_30

enum class Colors : int {
  Normal          = 0,
  Bold            = 1,
  Underline       = 4,

  fgBlack         = 30,
  fgRed           = 31,    
  fgGreen         = 32, 
  fgBrown         = 33, 
  fgBlue          = 34,          
  fgMagenta       = 35,           
  fgCyan          = 36,          
  fgWhite         = 37,         
  fgDefault       = 39,   

  bgBlack         = 40,
  bgRed           = 41,    
  bgGreen         = 42, 
  bgBrown         = 43, 
  bgBlue          = 44,          
  bgMagenta       = 45,           
  bgCyan          = 46,          
  bgWhite         = 47,         
  bgDefault       = 49,   
};

#endif//colors_hpp_20140803_1725_30
